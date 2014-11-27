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

constant sampler_t volumeSampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP_TO_EDGE | CLK_FILTER_NEAREST;

#ifdef cl_image_2d

__kernel void graphcut_compute_capacity_bk(
    const uint4 volumeSize, __read_only image2d_t volumeTexture, __global cl_cut *cutData,
    __global ushort2* nodeCapacity1, __global ushort2* nodeCapacity2,
    const float4 weight, const float sigma
    )
{
    const int2 gid = (int2)(get_global_id(0), get_global_id(1));
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y) return;
    
    const float scale = 1.0f / (SHRT_MAX * sigma);
    const int4 data = convert_int4(read_imagef(volumeTexture, volumeSampler, gid) * weight * SHRT_MAX);
    ushort2 capacity1 = (ushort2)(0);
    ushort2 capacity2 = (ushort2)(0);
    if (gid.x < volumeSize.x - 1)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int2)(gid.x + 1, gid.y)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float t = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity1.s0 = (ushort)(SHRT_MAX * exp(-0.5f * t * t) + 0.5f);
    }

    if (gid.y < volumeSize.y - 1)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int2)(gid.x, gid.y + 1)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float t = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity1.s1 = (ushort)(SHRT_MAX * exp(-0.5f * t * t) + 0.5f);
    }

    if (gid.y > 0)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int2)(gid.x, gid.y - 1)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float t = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity2.s0 = (ushort)(SHRT_MAX * exp(-0.5f * t * t) + 0.5f);
    }

    if (gid.x > 0)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int2)(gid.x - 1, gid.y)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float t = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity2.s1 = (ushort)(SHRT_MAX * exp(-0.5f * t * t) + 0.5f);
    }

    const int gid1D = gid.x + volumeSize.x * gid.y;
    nodeCapacity1[gid1D] = capacity1;
    nodeCapacity2[gid1D] = capacity2;
}

__kernel void graphcut_compute_capacity_lazy(
    const uint4 volumeSize, __read_only image2d_t volumeTexture, __global cl_cut *cutData,
    __global ushort2* nodeCapacity1, __global ushort2* nodeCapacity2,
    const float4 weight, const float lambda
    )
{
    const int2 gid = (int2)(get_global_id(0), get_global_id(1));
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y) return;
    
    const float scale = lambda / SHRT_MAX;
    const int4 data = convert_int4(read_imagef(volumeTexture, volumeSampler, gid) * weight * SHRT_MAX);
    ushort2 capacity1 = (ushort2)(0);
    ushort2 capacity2 = (ushort2)(0);
    
    if (gid.x < volumeSize.x - 1)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int2)(gid.x + 1, gid.y)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float dist = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity1.s0 = (ushort)(SHRT_MAX / (1.0f + dist) + 0.5f);
    }

    if (gid.y < volumeSize.y - 1)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int2)(gid.x, gid.y + 1)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float dist = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity1.s1 = (ushort)(SHRT_MAX / (1.0f + dist) + 0.5f);
    }
    
    if (gid.y > 0)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int2)(gid.x, gid.y - 1)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float dist = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity2.s0 = (ushort)(SHRT_MAX / (1.0f + dist) + 0.5f);
    }

    if (gid.x > 0)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int2)(gid.x - 1, gid.y)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float dist = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity2.s1 = (ushort)(SHRT_MAX / (1.0f + dist) + 0.5f);
    }
    
    const int gid1D = gid.x + volumeSize.x * gid.y;
    nodeCapacity1[gid1D] = capacity1;
    nodeCapacity2[gid1D] = capacity2;
}

#else

__kernel void graphcut_compute_capacity_bk(
    const uint4 volumeSize, __read_only image3d_t volumeTexture, __global cl_cut *cutData,
    __global uchar4* nodeCapacity1, __global uchar4* nodeCapacity2,
    const float4 weight, const float sigma
    )
{
    const int3 gid = (int3)(get_global_id(0), get_global_id(1), get_global_id(2));
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y || gid.z >= volumeSize.z) return;
    
    const float scale = 1.0f / (SHRT_MAX * sigma);
    const int4 data = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid, 0)) * weight * SHRT_MAX);
    uchar4 capacity1 = (uchar4)(0);
    uchar4 capacity2 = (uchar4)(0);
    if (gid.x < volumeSize.x - 1)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid.x + 1, gid.y, gid.z, 0)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float t = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity1.s0 = (uchar)(CHAR_MAX * exp(-0.5f * t * t) + 0.5f);
    }

    if (gid.y < volumeSize.y - 1)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid.x, gid.y + 1, gid.z, 0)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float t = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity1.s1 = (uchar)(CHAR_MAX * exp(-0.5f * t * t) + 0.5f);
    }

    if (gid.z < volumeSize.z - 1)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid.x, gid.y, gid.z + 1, 0)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float t = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity1.s2 = (uchar)(CHAR_MAX * exp(-0.5f * t * t) + 0.5f);
    }

    if (gid.z > 0)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid.x, gid.y, gid.z - 1, 0)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float t = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity2.s0 = (uchar)(CHAR_MAX * exp(-0.5f * t * t) + 0.5f);
    }

    if (gid.y > 0)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid.x, gid.y - 1, gid.z, 0)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float t = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity2.s1 = (uchar)(CHAR_MAX * exp(-0.5f * t * t) + 0.5f);
    }

    if (gid.x > 0)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid.x - 1, gid.y, gid.z, 0)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float t = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity2.s2 = (uchar)(CHAR_MAX * exp(-0.5f * t * t) + 0.5f);
    }
    
    const int gid1D = gid.x + volumeSize.x * (gid.y + volumeSize.y * gid.z);
    nodeCapacity1[gid1D] = capacity1;
    nodeCapacity2[gid1D] = capacity2;
}

__kernel void graphcut_compute_capacity_lazy(
    const uint4 volumeSize, __read_only image3d_t volumeTexture, __global cl_cut *cutData,
    __global uchar4* nodeCapacity1, __global uchar4* nodeCapacity2,
    const float4 weight, const float lambda
    )
{
    const int3 gid = (int3)(get_global_id(0), get_global_id(1), get_global_id(2));
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y || gid.z >= volumeSize.z) return;
    
    const float scale = lambda / SHRT_MAX;
    const int4 data = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid, 0)) * weight * SHRT_MAX);
    uchar4 capacity1 = (uchar4)(0);
    uchar4 capacity2 = (uchar4)(0);
    if (gid.x < volumeSize.x - 1)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid.x + 1, gid.y, gid.z, 0)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float dist = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity1.s0 = (uchar)(CHAR_MAX / (1.0f + dist) + 0.5f);
    }

    if (gid.y < volumeSize.y - 1)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid.x, gid.y + 1, gid.z, 0)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float dist = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity1.s1 = (uchar)(CHAR_MAX / (1.0f + dist) + 0.5f);
    }

    if (gid.z < volumeSize.z - 1)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid.x, gid.y, gid.z + 1, 0)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float dist = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity1.s2 = (uchar)(CHAR_MAX / (1.0f + dist) + 0.5f);
    }

    if (gid.z > 0)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid.x, gid.y, gid.z - 1, 0)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float dist = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity2.s0 = (uchar)(CHAR_MAX / (1.0f + dist) + 0.5f);
    }

    if (gid.y > 0)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid.x, gid.y - 1, gid.z, 0)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float dist = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity2.s1 = (uchar)(CHAR_MAX / (1.0f + dist) + 0.5f);
    }

    if (gid.x > 0)
    {
        const int4 datat = convert_int4(read_imagef(volumeTexture, volumeSampler, (int4)(gid.x - 1, gid.y, gid.z, 0)) * weight * SHRT_MAX);
        const uint4 diff = abs_diff(data, datat);
        const float dist = sqrt((float)(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + diff.w * diff.w)) * scale;
        capacity2.s2 = (uchar)(CHAR_MAX / (1.0f + dist) + 0.5f);
    }

    const int gid1D = gid.x + volumeSize.x * (gid.y + volumeSize.y * gid.z);
    nodeCapacity1[gid1D] = capacity1;
    nodeCapacity2[gid1D] = capacity2;
}

#endif