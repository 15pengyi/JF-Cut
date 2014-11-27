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
 * @date    2013/03/22
 */

#ifdef cl_image_2d

__kernel void graphcut_cut_histogram(
    const uint4 volumeSize, __read_only image2d_t volumeTexture, const uint textureOffset,
    const uint histogramSize, __global uint *histogramData,
    __global cl_cut *cutData,
    const float4 weight
    )
{
    const int2 id = (int2)(get_global_id(0), get_global_id(1));
    if (id.x >= volumeSize.x || id.y >= volumeSize.y) return;
    
    const int index = id.x + volumeSize.x * id.y;
    __global char* cut = (__global char*)(cutData + index);
    __global uint* histogram = histogramData;
    if (cut[textureOffset] == CHAR_MAX)
    {
        const float sum = weight.x + weight.y + weight.z + weight.w;
        const float data = clamp(dot(read_imagef(volumeTexture, volumeSampler, id), weight), 0.0f, 1.0f);
        const int level = (int)(data * (histogramSize - 1) + 0.5f);
        atomic_inc(histogram + level);
    }
}

__kernel void graphcut_cut_distribution(
    const uint4 volumeSize, __read_only image2d_t volumeTexture, const uint textureOffset,
    const uint distributionSize, __global uint *distributionData,
    __global cl_cut *cutData,
    const float4 weight
    )
{
    const int2 id = (int2)(get_global_id(0), get_global_id(1));
    if (id.x >= volumeSize.x || id.y >= volumeSize.y) return;
    
    const int index = id.x + volumeSize.x * id.y;
    __global char* cut = (__global char*)(cutData + index);
    __global uint* distribution = distributionData;
    if (cut[textureOffset] == CHAR_MAX)
    {
        const float data = clamp(dot(read_imagef(volumeTexture, volumeSampler, id), weight), 0.0f, 1.0f);
        const int level = (int)(data * (distributionSize - 1) + 0.5f);
        distribution[level] = index + 1;
    }
}

#else

__kernel void graphcut_cut_histogram(
    const uint4 volumeSize, __read_only image3d_t volumeTexture, const uint textureOffset,
    const uint histogramSize, __global uint *histogramData,
    __global cl_cut *cutData,
    const float4 weight
    )
{
    const int3 id = (int3)(get_global_id(0), get_global_id(1), get_global_id(2));
    if (id.x >= volumeSize.x || id.y >= volumeSize.y || id.z >= volumeSize.z) return;
    
    const int index = id.x + volumeSize.x * (id.y + volumeSize.y * id.z);
    __global char* cut = (__global char*)(cutData + index);
    __global uint* histogram = histogramData;
    if (cut[textureOffset] == CHAR_MAX)
    {
        const float data = clamp(dot(read_imagef(volumeTexture, volumeSampler, (int4)(id, 0)), weight), 0.0f, 1.0f);
        const int level = (int)(data * (histogramSize - 1) + 0.5f);
        atomic_inc(histogram + level);
    }
}

__kernel void graphcut_cut_distribution(
    const uint4 volumeSize, __read_only image3d_t volumeTexture, const uint textureOffset,
    const uint distributionSize, __global uint *distributionData,
    __global cl_cut *cutData,
    const float4 weight
    )
{
    const int3 id = (int3)(get_global_id(0), get_global_id(1), get_global_id(2));
    if (id.x >= volumeSize.x || id.y >= volumeSize.y || id.z >= volumeSize.z) return;
    
    const int index = id.x + volumeSize.x * (id.y + volumeSize.y * id.z);
    __global char* cut = (__global char*)(cutData + index);
    __global uint* distribution = distributionData;
    if (cut[textureOffset] == CHAR_MAX)
    {
        const float data = clamp(dot(read_imagef(volumeTexture, volumeSampler, (int4)(id, 0)), weight), 0.0f, 1.0f);
        const int level = (int)(data * (distributionSize - 1) + 0.5f);
        distribution[level] = index + 1;
    }
}

#endif