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
 * @date    2013/03/26
 */

 #ifdef cl_image_2d

__kernel void graphcut_compute_excessflow_bk(
    const uint4 volumeSize, __read_only image2d_t volumeTexture, __global cl_cut *cutData,
    __global int* nodeExcessFlow, __global int* nodeHeight,
    const uint histogramSize, __global uint *histogramData,
    const float lambda, const uint2 sum,
    const float4 weight
    )
{
    const int2 gid = (int2)(get_global_id(0), get_global_id(1));
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y) return;

    const float data = dot(read_imagef(volumeTexture, volumeSampler, gid), weight);
    const int level = (int)(data * (histogramSize - 1) + 0.5f);

    __global uint *histFore = histogramData;
    __global uint *histBack = histogramData + histogramSize;
    float2 d = (float2)(-log((float)histFore[level] / sum.x), -log((float)histBack[level] / sum.y));

    const int gid1D = gid.x + volumeSize.x * gid.y;
    const cl_cut cut = cutData[gid.x + volumeSize.x * gid.y];
    if (cut.foreground > 0)
        nodeExcessFlow[gid1D] =  cl_max_flow;
    else if (cut.background > 0)
        nodeExcessFlow[gid1D] = -cl_max_flow;
    else
        nodeExcessFlow[gid1D] = round((cl_max_flow >> 2) * lambda * (d.y - d.x));
}

__kernel void graphcut_compute_excessflow_lazy(
    const uint4 volumeSize, __read_only image2d_t volumeTexture, __global cl_cut *cutData,
    __global int* nodeExcessFlow, __global int* nodeHeight,
    __global float4 *centroidData,
    const float lambda, const int k,
    const float4 weight
    )
{
    const int2 gid = (int2)(get_global_id(0), get_global_id(1));
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y) return;
    
    const float4 data = read_imagef(volumeTexture, volumeSampler, gid) * weight;
    float2 d = (float2)(FLT_MAX);
    
    __global float4 *centroidFore = centroidData;
    __global float4 *centroidBack = centroidData + k;
    for (int i = 0; i < k; i++)
    {
        d.x = min(d.x, distance(centroidFore[i], data));
        d.y = min(d.y, distance(centroidBack[i], data));
    }
    
    const int gid1D = gid.x + volumeSize.x * gid.y;
    const cl_cut cut = cutData[gid1D];
    if (cut.foreground > 0)
        nodeExcessFlow[gid1D] =  cl_max_flow;
    else if (cut.background > 0)
        nodeExcessFlow[gid1D] = -cl_max_flow;
    else
        nodeExcessFlow[gid1D] = round((cl_max_flow >> 2) * lambda * (d.x + d.y == 0.0f ? 0.0f : (d.y - d.x) / (d.x + d.y)));
}

#else

__kernel void graphcut_compute_excessflow_bk(
    const uint4 volumeSize, __read_only image3d_t volumeTexture, __global cl_cut *cutData,
    __global int* nodeExcessFlow, __global int* nodeHeight,
    const uint histogramSize, __global uint *histogramData,
    const float lambda, const uint2 sum,
    const float4 weight
    )
{
    const int3 gid = (int3)(get_global_id(0), get_global_id(1), get_global_id(2));
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y || gid.z >= volumeSize.z) return;
    
    const float data = dot(read_imagef(volumeTexture, volumeSampler, (int4)(gid, 0)), weight);
    const int level = (int)(data * (histogramSize - 1) + 0.5f);

    __global uint *histFore = histogramData;
    __global uint *histBack = histogramData + histogramSize;
    float2 d = (float2)(-log((float)histFore[level] / sum.x), -log((float)histBack[level] / sum.y));
    
    const int gid1D = gid.x + volumeSize.x * (gid.y + volumeSize.y * gid.z);
    const cl_cut cut = cutData[gid1D];
        if (cut.foreground > 0)
        nodeExcessFlow[gid1D] =  cl_max_flow;
    else if (cut.background > 0)
        nodeExcessFlow[gid1D] = -cl_max_flow;
    else
        nodeExcessFlow[gid1D] = round((cl_max_flow >> 3) * lambda * (d.y - d.x));
}

__kernel void graphcut_compute_excessflow_lazy(
    const uint4 volumeSize, __read_only image3d_t volumeTexture, __global cl_cut *cutData,
    __global int* nodeExcessFlow, __global int* nodeHeight,
    __global float4 *centroidData,
    const float lambda, const int k,
    const float4 weight
    )
{
    const int3 gid = (int3)(get_global_id(0), get_global_id(1), get_global_id(2));
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y || gid.z >= volumeSize.z) return;
    
    const float4 data = read_imagef(volumeTexture, volumeSampler, (int4)(gid, 0)) * weight;
    float2 d = (float2)(FLT_MAX);
    
    __global float4 *centroidFore = centroidData;
    __global float4 *centroidBack = centroidData + k;
    for (int i = 0; i < k; i++)
    {
        d.x = min(d.x, distance(centroidFore[i], data));
        d.y = min(d.y, distance(centroidBack[i], data));
    }
    
    const int gid1D = gid.x + volumeSize.x * (gid.y + volumeSize.y * gid.z);
    const cl_cut cut = cutData[gid1D];
    if (cut.foreground > 0)
        nodeExcessFlow[gid1D] =  cl_max_flow;
    else if (cut.background > 0)
        nodeExcessFlow[gid1D] = -cl_max_flow;
    else
        nodeExcessFlow[gid1D] = round((cl_max_flow >> 3) * lambda * (d.x + d.y == 0.0f ? 0.0f : (d.y - d.x) / (d.x + d.y)));
}

#endif