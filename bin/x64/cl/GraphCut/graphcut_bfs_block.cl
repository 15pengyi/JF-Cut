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
 * @e-mail: 15pengyi@gmail.com
 * @date    2013/10/30
 */

#ifdef cl_image_2d

int getDistance(
    const int2 gid,
    const int value
    )
{
    int2 nearest = (int2)(value >> cl_shift_2d_x, value >> cl_shift_2d_y) & cl_shift_max;
    uint2 d = abs(nearest - gid);
    return d.x + d.y;
}

void compareDistance(
    int2* pair,
    const int h,
    const int2 gid
    )
{
    int d = getDistance(gid, h);
    if (d < (*pair).y)
    {
        (*pair).x = h;
        (*pair).y = d;
    }
}

__kernel void graphcut_bfs_jump_flooding(
    const uint4 groupSize, __global int* depthData,
    const int jumpSize
    )
{
    const int2 gid = (int2)(get_global_id(0), get_global_id(1));
    if (gid.x >= groupSize.x || gid.y >= groupSize.y) return;

    const int gid1D = gid.x + groupSize.x * gid.y;
    __global int* depth = depthData + gid1D;
    int value = *depth;
    int2 pair = (int2)(value, getDistance(gid, value));
    const int2 jumpOffset = (int2)(1, groupSize.x) * jumpSize;

    if (gid.x + jumpSize <  groupSize.x) compareDistance(&pair, depth[ jumpOffset.x], gid);
    if (gid.x - jumpSize >= 0          ) compareDistance(&pair, depth[-jumpOffset.x], gid);
    if (gid.y + jumpSize <  groupSize.y) compareDistance(&pair, depth[ jumpOffset.y], gid);
    if (gid.y - jumpSize >= 0          ) compareDistance(&pair, depth[-jumpOffset.y], gid);

    if (pair.x != value) *depth = value = pair.x;
}

__kernel void graphcut_bfs_histogram(
    const uint4 groupSize, __global int* depthData,
    const uint histogramSize, __global int* histogramData, __global int4* listData
    )
{
    const int2 gid = (int2)(get_global_id(0), get_global_id(1));
    if (gid.x >= groupSize.x || gid.y >= groupSize.y) return;
    
    const int gid1D = gid.x + groupSize.x * gid.y;
    const uint value = getDistance(gid, depthData[gid1D]);
    depthData[gid1D] = value;
    listData[gid1D].w = atomic_inc(histogramData + value);
}

__kernel void graphcut_bfs_mapping(
    const uint4 groupSize, __global int* histogramData,
    __global int* depthData, __global int4* listData
    )
{
    const int2 gid = (int2)(get_global_id(0), get_global_id(1));
    if (gid.x >= groupSize.x || gid.y >= groupSize.y) return;
    
    const int gid1D = gid.x + groupSize.x * gid.y;
    const uint value = depthData[gid1D];
    const int position = histogramData[value] + listData[gid1D].w;
    listData[position].xy = gid;
}

#else

int getDistance(
    const int3 gid,
    const int value
    )
{
    int3 nearest = (int3)(value >> cl_shift_3d_x, value >> cl_shift_3d_y, value >> cl_shift_3d_z) & cl_shift_max;
    uint3 d = abs(nearest - gid);
    return d.x + d.y + d.z;
}

void compareDistance(
    int2* pair,
    const int h,
    const int3 gid
    )
{
    int d = getDistance(gid, h);
    if (d < (*pair).y)
    {
        (*pair).x = h;
        (*pair).y = d;
    }
}

__kernel void graphcut_bfs_jump_flooding(
    const uint4 groupSize, __global int* depthData, const int jumpSize
    )
{
    const int3 gid = (int3)(get_global_id(0), get_global_id(1), get_global_id(2));
    if (gid.x >= groupSize.x || gid.y >= groupSize.y || gid.z >= groupSize.z) return;

    const int gid1D = gid.x + groupSize.x * (gid.y + groupSize.y * gid.z);
    __global int* depth = depthData + gid1D;
    int value = *depth;
    int2 pair = (int2)(value, getDistance(gid, value));
    const int3 jumpOffset = (int3)(1, groupSize.x, groupSize.x * groupSize.y) * jumpSize;

    if (gid.x + jumpSize <  groupSize.x) compareDistance(&pair, depth[ jumpOffset.x], gid);
    if (gid.x - jumpSize >= 0          ) compareDistance(&pair, depth[-jumpOffset.x], gid);
    if (gid.y + jumpSize <  groupSize.y) compareDistance(&pair, depth[ jumpOffset.y], gid);
    if (gid.y - jumpSize >= 0          ) compareDistance(&pair, depth[-jumpOffset.y], gid);
    if (gid.z + jumpSize <  groupSize.z) compareDistance(&pair, depth[ jumpOffset.z], gid);
    if (gid.z - jumpSize >= 0          ) compareDistance(&pair, depth[-jumpOffset.z], gid);

    if (pair.x != value) *depth = value = pair.x;
}

__kernel void graphcut_bfs_histogram(
    const uint4 groupSize, __global int* depthData,
    const uint histogramSize, __global int* histogramData, __global int4* listData
    )
{
    const int3 gid = (int3)(get_global_id(0), get_global_id(1), get_global_id(2));
    if (gid.x >= groupSize.x || gid.y >= groupSize.y || gid.z >= groupSize.z) return;
    
    const int gid1D = gid.x + groupSize.x * (gid.y + groupSize.y * gid.z);
    const uint value = getDistance(gid, depthData[gid1D]);
    depthData[gid1D] = value;
    listData[gid1D].w = atomic_inc(histogramData + value);
}

__kernel void graphcut_bfs_mapping(
    const uint4 groupSize, __global int* histogramData,
    __global int* depthData, __global int4* listData
    )
{
    const int3 gid = (int3)(get_global_id(0), get_global_id(1), get_global_id(2));
    if (gid.x >= groupSize.x || gid.y >= groupSize.y || gid.z >= groupSize.z) return;
    
    const int gid1D = gid.x + groupSize.x * (gid.y + groupSize.y * gid.z);
    const uint value = depthData[gid1D];
    const int position = histogramData[value] + listData[gid1D].w;
    listData[position].xyz = gid;
}

#endif