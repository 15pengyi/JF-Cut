/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    *.cl
 * @brief   * functions definition.
 * 
 * This file defines *.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/03/24
 */

constant float3 lightPosition  = (float3)(1.0f);
constant float4 LightAmbient   = (float4)(0.75f, 0.75f, 0.75f, 1.0f);
constant float4 LightDiffuse   = (float4)(0.35f, 0.35f, 0.35f, 0.0f);
constant float4 LightSpecular  = (float4)(0.15f, 0.15f, 0.15f, 0.0f);
constant float  LightShininess = 4.0f;

constant sampler_t transferFunctionSampler = CLK_NORMALIZED_COORDS_TRUE | CLK_ADDRESS_CLAMP_TO_EDGE | CLK_FILTER_LINEAR;
constant sampler_t cutSampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP_TO_EDGE | CLK_FILTER_LINEAR;
constant sampler_t volumeSampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP_TO_EDGE | CLK_FILTER_LINEAR;

// intersect ray with a box
// http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter3.htm

int intersectRay(float4 r_o, float4 r_d, float4 box, float *tnear, float *tfar)
{
    // compute intersection of ray with all six bbox planes
    const float4 invR = (float4)(1.0f) / r_d;
    const float4 tbot = invR * (-box - r_o);
    const float4 ttop = invR * (box - r_o);

    // re-order intersections to find smallest and largest on each axis
    const float4 tmin = min(ttop, tbot);
    const float4 tmax = max(ttop, tbot);

    // find the largest tmin and the smallest tmax
    const float largest_tmin  = max(max(tmin.x, tmin.y), tmin.z);
    const float smallest_tmax = min(min(tmax.x, tmax.y), tmax.z);

    *tnear = largest_tmin;
    *tfar = smallest_tmax;

    return *tnear < *tfar;
}

float4 backProject(float* m, float4 v)
{
    return (float4)(
        dot(v, (float4)(m[0], m[4], m[ 8], m[12])),
        dot(v, (float4)(m[1], m[5], m[ 9], m[13])),
        dot(v, (float4)(m[2], m[6], m[10], m[14])),
        dot(v, (float4)(m[3], m[7], m[11], m[15]))
        );
}

// graphcut_render_volume

uint float4ToInt(float4 c)
{
    const uint4 color = convert_uint4_rtn(clamp(c, (float4)(0.0f), (float4)(1.0f)) * 255.0f);
    return (color.w << 24) | (color.z << 16) | (color.y << 8) | (color.x);
}

__kernel void graphcut_render_volume_object(
    float16 inverseMVPMatrix,
    __global uint *pixelBuffer,
#ifdef cl_image_2d
    __read_only image2d_t cutTexture,
    __read_only image2d_t volumeTexture, const uint4 volumeSize,
#else
    __read_only image3d_t cutTexture,
    __read_only image3d_t volumeTexture, const uint4 volumeSize,
#endif
    __read_only image2d_t integrationTable,
    __read_only image2d_t transferFunctionTable,
    const uint imageWidth, const uint imageHeight,
    const uint sampleNumber, const float sampleRatio, const float sampleStepScale, const float4 volumeBoundingBox,
    const float windowWidth, const float windowLevel,
    const uint textureOffset
    )
{
    const uint x = get_global_id(0);
    const uint y = get_global_id(1);
    if (x >= imageWidth || y >= imageHeight) return;

    const float2 imageCoords = (float2)((x + 0.5f) / imageWidth  * 2.0f - 1.0f, (y + 0.5f) / imageHeight * 2.0f - 1.0f);
    const float4 worldOrigin = backProject((float*)&inverseMVPMatrix, (float4)(imageCoords, -1.0f, 1.0f));
    const float4 worldEnd    = backProject((float*)&inverseMVPMatrix, (float4)(imageCoords, 0.0f, 1.0f));
    const float4 origin = (float4)(worldOrigin.xyz / worldOrigin.w, 0.0f);
    const float4 direction = normalize(worldEnd / worldEnd.w - worldOrigin / worldOrigin.w);
    
    const int tileSize = 16;
    const int tileIndex = (x / tileSize + y / tileSize) & 1;
    const float4 tileColor[2] = { (float4)(0.9375f, 0.9375f, 0.9375f, 1.0f), (float4)(0.75f, 0.75f, 0.75f, 1.0f) };

    // find intersection with box
    float tnear = 0.0f;
    float tfar  = 0.0f;
    if (!intersectRay(origin, direction, volumeBoundingBox, &tnear, &tfar))
    {
        pixelBuffer[x + y * imageWidth] = float4ToInt(tileColor[tileIndex]);
        return;
    }
    tnear = max(tnear, 0.0f);  // clamp to near plane
    
    // march along ray from back to front, accumulating color
    const float4 sampleOffset = convert_float4(volumeSize - 1) * 0.5f;
    const float4 sampleScale = sampleOffset / volumeBoundingBox;
    const float4 sampleOrigin = origin * sampleScale + sampleOffset;
    const float4 sampleDirection = direction * sampleScale;
    const float windowMin = windowLevel - windowWidth / 2;
    const float windowMax = windowLevel + windowWidth / 2;

    float4 pixelColor = (float4)(0.0f);
    float4 sampleCut = (float4)(0.0f);
    float4 samplePosition = sampleOrigin + sampleDirection * tnear;
    float volumeStepSize  =  (tfar - tnear) / (sampleNumber - 1) * sampleRatio;
    float volumeStepDelta = ((tfar - tnear) / (sampleNumber - 1) - volumeStepSize) / (sampleNumber - 2);
    float* cut = (float*)&sampleCut + textureOffset - 1;

    // march along ray from back to front, accumulating color
    for(int i = 0; i < sampleNumber; i++)
    {
        // read from 3D texture
#ifdef cl_image_2d
        const float4 sampleValue = read_imagef(volumeTexture, volumeSampler, samplePosition.xy);
        sampleCut = read_imagef(cutTexture, cutSampler, samplePosition.xy);
        const float4 color = read_imagef(transferFunctionTable, transferFunctionSampler, (float2)(clamp(sampleValue.w, windowMin, windowMax), 0.5f));
#else
        const float4 sampleValue = read_imagef(volumeTexture, volumeSampler, samplePosition);
        sampleCut = read_imagef(cutTexture, cutSampler, samplePosition);
        const float3 light  = normalize(lightPosition.xyz);
        const float3 normal = normalize((float3)(
            read_imagef(volumeTexture, volumeSampler, samplePosition + (float4)(1.0f, 0.0f, 0.0f, 0.0f)).w - read_imagef(volumeTexture, volumeSampler, samplePosition - (float4)(1.0f, 0.0f, 0.0f, 0.0f)).w,
            read_imagef(volumeTexture, volumeSampler, samplePosition + (float4)(0.0f, 1.0f, 0.0f, 0.0f)).w - read_imagef(volumeTexture, volumeSampler, samplePosition - (float4)(0.0f, 1.0f, 0.0f, 0.0f)).w,
            read_imagef(volumeTexture, volumeSampler, samplePosition + (float4)(0.0f, 0.0f, 1.0f, 0.0f)).w - read_imagef(volumeTexture, volumeSampler, samplePosition - (float4)(0.0f, 0.0f, 1.0f, 0.0f)).w
            ));
        const float4 color  = 
            LightAmbient  * read_imagef(transferFunctionTable, transferFunctionSampler, (float2)(clamp(sampleValue.w, windowMin, windowMax), 0.5f))
          + LightDiffuse  * max(dot(normal, light), 0.0f)
          + LightSpecular * pow(max(dot(normalize(2.0f * normal * dot(normal, light) - light), normalize(direction.xyz)), 0.0f), LightShininess);
#endif
        if (*cut > 0.0f) pixelColor += (float4)(color.xyz, 1.0) * color.w * sampleStepScale * volumeStepSize * exp(-pixelColor.w);

        // early ray termination
        if (pixelColor.w >= 1.0f) break;
        
        // non-uniform sampling
        samplePosition += sampleDirection * volumeStepSize;
        volumeStepSize += volumeStepDelta;
    }
    
    pixelColor = (float4)(mix(tileColor[tileIndex].xyz, pixelColor.xyz, min(pixelColor.w, 1.0f)), 1.0f);
    pixelBuffer[x + y * imageWidth] = float4ToInt(pixelColor);
}

__kernel void graphcut_render_volume(
    float16 inverseMVPMatrix,
    __global uint *pixelBuffer,
#ifdef cl_image_2d
    __read_only image2d_t cutTexture,
    __read_only image2d_t volumeTexture, const uint4 volumeSize,
#else
    __read_only image3d_t cutTexture,
    __read_only image3d_t volumeTexture, const uint4 volumeSize,
#endif
    __read_only image2d_t integrationTable,
    __read_only image2d_t transferFunctionTable,
    const uint imageWidth, const uint imageHeight,
    const uint sampleNumber, const float sampleRatio, const float sampleStepScale, const float4 volumeBoundingBox,
    const float windowWidth, const float windowLevel,
    const float4 colorFore, const float4 colorBack, const float4 colorCut, const float4 colorTag
    )
{
    const uint x = get_global_id(0);
    const uint y = get_global_id(1);
    if (x >= imageWidth || y >= imageHeight) return;

    const float2 imageCoords = (float2)((x + 0.5f) / imageWidth  * 2.0f - 1.0f, (y + 0.5f) / imageHeight * 2.0f - 1.0f);
    const float4 worldOrigin = backProject((float*)&inverseMVPMatrix, (float4)(imageCoords, -1.0f, 1.0f));
    const float4 worldEnd    = backProject((float*)&inverseMVPMatrix, (float4)(imageCoords, 0.0f, 1.0f));
    const float4 origin = (float4)(worldOrigin.xyz / worldOrigin.w, 0.0f);
    const float4 direction = normalize(worldEnd / worldEnd.w - worldOrigin / worldOrigin.w);
    
    const int tileSize = 16;
    const int tileIndex = (x / tileSize + y / tileSize) & 1;
    const float4 tileColor[2] = { (float4)(0.9375f, 0.9375f, 0.9375f, 1.0f), (float4)(0.75f, 0.75f, 0.75f, 1.0f) };

    // find intersection with box
    float tnear = 0.0f;
    float tfar  = 0.0f;
    if (!intersectRay(origin, direction, volumeBoundingBox, &tnear, &tfar))
    {
        pixelBuffer[x + y * imageWidth] = float4ToInt(tileColor[tileIndex]);
        return;
    }
    tnear = max(tnear, 0.0f);  // clamp to near plane
    
    // march along ray from back to front, accumulating color
    const float4 sampleOffset = convert_float4(volumeSize - 1) * 0.5f;
    const float4 sampleScale = sampleOffset / volumeBoundingBox;
    const float4 sampleOrigin = origin * sampleScale + sampleOffset;
    const float4 sampleDirection = direction * sampleScale;
    const float windowMin = windowLevel - windowWidth / 2;
    const float windowMax = windowLevel + windowWidth / 2;

    float4 pixelColor = (float4)(0.0f);
    float4 samplePosition = sampleOrigin + sampleDirection * tnear;
    float volumeStepSize  =  (tfar - tnear) / (sampleNumber - 1) * sampleRatio;
    float volumeStepDelta = ((tfar - tnear) / (sampleNumber - 1) - volumeStepSize) / (sampleNumber - 2);

    // march along ray from back to front, accumulating color
    for(int i = 0; i < sampleNumber; i++)
    {
        // read from 3D texture
#ifdef cl_image_2d
        const float4 sampleValue = read_imagef(volumeTexture, volumeSampler, samplePosition.xy);
        const float4 cut = read_imagef(cutTexture, cutSampler, samplePosition.xy);
        const float4 color = read_imagef(transferFunctionTable, transferFunctionSampler, (float2)(clamp(sampleValue.w, windowMin, windowMax), 0.5f));
#else
        const float4 sampleValue = read_imagef(volumeTexture, volumeSampler, samplePosition);
        const float4 cut = read_imagef(cutTexture, cutSampler, samplePosition);
        const float3 light  = normalize(lightPosition.xyz);
        const float3 normal = normalize((float3)(
            read_imagef(volumeTexture, volumeSampler, samplePosition + (float4)(1.0f, 0.0f, 0.0f, 0.0f)).w - read_imagef(volumeTexture, volumeSampler, samplePosition - (float4)(1.0f, 0.0f, 0.0f, 0.0f)).w,
            read_imagef(volumeTexture, volumeSampler, samplePosition + (float4)(0.0f, 1.0f, 0.0f, 0.0f)).w - read_imagef(volumeTexture, volumeSampler, samplePosition - (float4)(0.0f, 1.0f, 0.0f, 0.0f)).w,
            read_imagef(volumeTexture, volumeSampler, samplePosition + (float4)(0.0f, 0.0f, 1.0f, 0.0f)).w - read_imagef(volumeTexture, volumeSampler, samplePosition - (float4)(0.0f, 0.0f, 1.0f, 0.0f)).w
            ));
        const float4 color  = 
            LightAmbient  * read_imagef(transferFunctionTable, transferFunctionSampler, (float2)(clamp(sampleValue.w, windowMin, windowMax), 0.5f))
          + LightDiffuse  * max(dot(normal, light), 0.0f)
          + LightSpecular * pow(max(dot(normalize(2.0f * normal * dot(normal, light) - light), normalize(direction.xyz)), 0.0f), LightShininess);
#endif
        pixelColor += colorFore * cut.x * exp(-pixelColor.w);
        pixelColor += colorBack * cut.y * exp(-pixelColor.w);
        pixelColor += colorCut  * cut.z * exp(-pixelColor.w);
        pixelColor += colorTag  * cut.w * exp(-pixelColor.w);
        pixelColor += (float4)(color.xyz, 1.0) * color.w * sampleStepScale * volumeStepSize * exp(-pixelColor.w);
        
        // early ray termination
        if (pixelColor.w >= 1.0f) break;

        // non-uniform sampling
        samplePosition += sampleDirection * volumeStepSize;
        volumeStepSize += volumeStepDelta;
    }
    
    pixelColor = (float4)(mix(tileColor[tileIndex].xyz, pixelColor.xyz, min(pixelColor.w, 1.0f)), 1.0f);
    pixelBuffer[x + y * imageWidth] = float4ToInt(pixelColor);
}

// graphcut_compute_visibility

void saveMask(__global char *cutData,
    float4 indexf, float4 maxIndex, uint4 offset)
{
    const float4 indexFloorf = floor(indexf);
    const uint4 indexFloor = convert_uint4(clamp(indexFloorf,        (float4)(0.0f), maxIndex)) * offset;
    const uint4 indexCeil  = convert_uint4(clamp(indexFloorf + 1.0f, (float4)(0.0f), maxIndex)) * offset;
    cutData[indexFloor.x + indexFloor.y + indexFloor.z] = CHAR_MAX;
    cutData[indexFloor.x + indexFloor.y +  indexCeil.z] = CHAR_MAX;
    cutData[indexFloor.x +  indexCeil.y + indexFloor.z] = CHAR_MAX;
    cutData[indexFloor.x +  indexCeil.y +  indexCeil.z] = CHAR_MAX;
    cutData[ indexCeil.x + indexFloor.y + indexFloor.z] = CHAR_MAX;
    cutData[ indexCeil.x + indexFloor.y +  indexCeil.z] = CHAR_MAX;
    cutData[ indexCeil.x +  indexCeil.y + indexFloor.z] = CHAR_MAX;
    cutData[ indexCeil.x +  indexCeil.y +  indexCeil.z] = CHAR_MAX;
}

__kernel void graphcut_compute_visibility(
    float16 inverseMVPMatrix,
    __global uchar *maskData, __global cl_cut *cutData,
#ifdef cl_image_2d
    __read_only image2d_t volumeTexture, const uint4 volumeSize,
#else
    __read_only image3d_t volumeTexture, const uint4 volumeSize,
#endif
    __read_only image2d_t integrationTable,
    __read_only image2d_t transferFunctionTable,
    const uint imageWidth, const uint imageHeight,
    const uint sampleNumber, const float sampleRatio, const float sampleStepScale, const float4 volumeBoundingBox,
    const float windowWidth, const float windowLevel,
    const uint textureOffset, const float alpha
    )
{
    const uint x = get_global_id(0);
    const uint y = get_global_id(1);
    if (x >= imageWidth || y >= imageHeight) return;

    const float2 imageCoords = (float2)((x + 0.5f) / imageWidth  * 2.0f - 1.0f, (y + 0.5f) / imageHeight * 2.0f - 1.0f);
    const float4 worldOrigin = backProject((float*)&inverseMVPMatrix, (float4)(imageCoords, -1.0f, 1.0f));
    const float4 worldEnd    = backProject((float*)&inverseMVPMatrix, (float4)(imageCoords, 0.0f, 1.0f));
    const float4 origin = (float4)(worldOrigin.xyz / worldOrigin.w, 0.0f);
    const float4 direction = normalize(worldEnd / worldEnd.w - worldOrigin / worldOrigin.w);
    
    // find intersection with box
    float tnear = 0.0f;
    float tfar  = 0.0f;
    if (!intersectRay(origin, direction, volumeBoundingBox, &tnear, &tfar) || !maskData[x + y * imageWidth])
    {
        return;
    }
    tnear = max(tnear, 0.0f);  // clamp to near plane
    
    // march along ray from back to front, accumulating color
    const uint4 cutOffset = (uint4)(1, volumeSize.x, volumeSize.x * volumeSize.y, 0) * sizeof(cl_cut);
    const float4 sampleMaxIndex = convert_float4(volumeSize - 1);
    const float4 sampleOffset = sampleMaxIndex * 0.5f;
    const float4 sampleScale = sampleOffset / volumeBoundingBox;
    const float4 sampleOrigin = origin * sampleScale + sampleOffset;
    const float4 sampleDirection = direction * sampleScale;
    const float windowMin = windowLevel - windowWidth / 2;
    const float windowMax = windowLevel + windowWidth / 2;

    float4 pixelColor = (float4)(0.0f);
    float4 samplePosition = sampleOrigin + sampleDirection * tnear;
    float volumeStepSize  =  (tfar - tnear) / (sampleNumber - 1) * sampleRatio;
    float volumeStepDelta = ((tfar - tnear) / (sampleNumber - 1) - volumeStepSize) / (sampleNumber - 2);

    // march along ray from back to front, accumulating color
    for(int i = 0; i < sampleNumber; i++)
    {
        // read from 3D texture
#ifdef cl_image_2d
        const float4 sampleValue = read_imagef(volumeTexture, volumeSampler, samplePosition.xy);
#else
        const float4 sampleValue = read_imagef(volumeTexture, volumeSampler, samplePosition);
#endif
        const float4 color = read_imagef(transferFunctionTable, transferFunctionSampler, (float2)(clamp(sampleValue.w, windowMin, windowMax), 0.5f));
        pixelColor += (float4)(color.xyz, 1.0) * color.w * sampleStepScale * volumeStepSize * exp(-pixelColor.w);
        
        // early ray termination
        if (pixelColor.w >= 1.0f) break;
        
        // save mask
        if (color.w > alpha) saveMask((__global char*)cutData + textureOffset, samplePosition, sampleMaxIndex, cutOffset);
        
        // non-uniform sampling
        samplePosition += sampleDirection * volumeStepSize;
        volumeStepSize += volumeStepDelta;
    }
}