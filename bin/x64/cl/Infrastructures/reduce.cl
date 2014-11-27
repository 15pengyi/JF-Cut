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
 * @date    2013/10/24
 */

__kernel void reduce_flow(__global int *out, __global const int *in, int len, int siz)
{
    __local int sums[cl_group_size];
    const int tid = get_group_id(0);
    const int lid = get_local_id(0);
    const int offset = tid * len;
    const int size = min(len, siz - offset);

    /* Sum up corresponding elements from each chunk */
    int accum = 0;
    for (int i = lid; i < size; i += cl_group_size)
         accum += max(in[offset + i], 0);
    sums[lid] = accum;
    
    /* Upsweep */
    for (int scale = cl_group_size / 2; scale >= 1; scale >>= 1)
    {
        barrier(CLK_LOCAL_MEM_FENCE);
        if (lid < scale)
            sums[lid] += sums[lid + scale];
    }

    /* No barrier needed here, because sums[0] is computed by thread 0 */
    if (lid == 0)
        out[tid] = sums[0];
}

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

__kernel void reduce_histogram(
    __global int *out, __global const int *in,
    const int len, const int4 siz
    )
{
    __local int maximums[cl_group_size];
    const int tid = get_group_id(0);
    const int lid = get_local_id(0);
    const int offset = tid * len;
    const int size = min(len, siz.x * siz.y - offset);

    /* Sum up corresponding elements from each chunk */
    int accum = 0;
    for (int i = lid; i < size; i += cl_group_size)
    {
        const int gid = offset + i;
        const int2 id = (int2)(gid % siz.x, gid / siz.x);
        accum = max(accum, getDistance(id, in[gid]));
    }
    maximums[lid] = accum;
    
    /* Upsweep */
    for (int scale = cl_group_size / 2; scale >= 1; scale >>= 1)
    {
        barrier(CLK_LOCAL_MEM_FENCE);
        if (lid < scale)
            maximums[lid] = max(maximums[lid], maximums[lid + scale]);
    }

    /* No barrier needed here, because maximums[0] is computed by thread 0 */
    if (lid == 0)
        out[tid] = maximums[0];
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


__kernel void reduce_histogram(
    __global int *out, __global int *in,
    const int len, const int4 siz
    )
{
    __local int maximums[cl_group_size];
    const int tid = get_group_id(0);
    const int lid = get_local_id(0);
    const int offset = tid * len;
    const int size = min(len, siz.x * siz.y * siz.z - offset);

    /* Sum up corresponding elements from each chunk */
    int accum = 0;
    for (int i = lid; i < size; i += cl_group_size)
    {
        int gid, index = gid = offset + i;
        int3 id;
        id.x = index % siz.x;
        index /= siz.x;
        id.y = index % siz.y;
        index /= siz.y;
        id.z = index;
        int v = in[gid];
        accum = max(accum, getDistance(id, v));
    }
    maximums[lid] = accum;
    
    /* Upsweep */
    for (int scale = cl_group_size / 2; scale >= 1; scale >>= 1)
    {
        barrier(CLK_LOCAL_MEM_FENCE);
        if (lid < scale)
            maximums[lid] = max(maximums[lid], maximums[lid + scale]);
    }

    /* No barrier needed here, because maximums[0] is computed by thread 0 */
    if (lid == 0)
        out[tid] = maximums[0];
}

#endif
