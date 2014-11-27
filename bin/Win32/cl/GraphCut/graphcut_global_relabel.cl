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
 * @date    2013/06/11
 */

#ifdef cl_image_2d

__kernel void graphcut_init_global_relabel(
    const uint4 volumeSize, __global int* nodeExcessFlow, __global int* nodeHeight,
    const uint4 groupSize, __global int* depthData
    )
{
    const int2 tid = (int2)(get_global_id(2) % groupSize.x, get_global_id(2) / groupSize.x);
    const int2 lid = (int2)(get_global_id(0), get_global_id(1));
    const int2 gid = lid + (int2)(cl_block_2d_x, cl_block_2d_y) * tid;
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y) return;

    const int gid1D = gid.x + volumeSize.x  * gid.y;
    const int lid1D = lid.x + cl_block_2d_x * lid.y;

    __local int localDone;
    if (lid1D == 0) localDone = 0;
    barrier(CLK_LOCAL_MEM_FENCE);
    
    if (nodeExcessFlow[gid1D] < 0)
    {
        localDone = 1;
        nodeHeight[gid1D] = 0;
    }
    else
    {
        nodeHeight[gid1D] = cl_max_height;
    }
    barrier(CLK_LOCAL_MEM_FENCE);

    if (lid1D == 0) depthData[get_global_id(2)] = localDone ? (tid.x << cl_shift_2d_x) + (tid.y << cl_shift_2d_y) : (1 << 30) - 1;
}

__kernel void graphcut_global_relabel(
    const uint4 volumeSize, __global int* nodeHeight, __global ushort2* nodeCapacity1, __global ushort2* nodeCapacity2,
    const uint4 groupSize, __global int4* listData,
    __global int* done
    )
{
    const int2 tid = listData[get_global_id(2)].xy;
    const int2 lid = (int2)(get_global_id(0), get_global_id(1));
    const int2 gid = lid + (int2)(cl_block_2d_x, cl_block_2d_y) * tid;
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y) return;

    const int lid1D = (lid.x + 1) + (cl_block_2d_x + 2) * (lid.y + 1);
    const int gid1D = (gid.x    ) + (volumeSize.x     ) * (gid.y    );

    __local char localDone;
    __local int heightDatat[(cl_block_2d_x + 2) * (cl_block_2d_y + 2)];
    __local int *heightt = heightDatat + lid1D;
    __local int *ht0, *ht1, *ht2, *ht3;

    __global int* height = nodeHeight + gid1D;
    __private ushort4 c = (ushort4)(nodeCapacity1[gid1D], nodeCapacity2[gid1D]);
    __private int oh, h = oh = *height;

    *heightt = h;

    if (h > 0)
    {
        ht0 = heightt + 1,                   ht3 = heightt - 1;
        ht1 = heightt + (cl_block_2d_x + 2), ht2 = heightt - (cl_block_2d_x + 2);
    
        if (gid.x == min(cl_block_2d_x * (tid.x + 1), (int)volumeSize.x) - 1)
            *ht0 = gid.x < volumeSize.x - 1 ? *(height + 1) : 0;
        if (lid.x == 0)
            *ht3 = gid.x > 0                ? *(height - 1) : 0;
        if (gid.y == min(cl_block_2d_y * (tid.y + 1), (int)volumeSize.y) - 1)
            *ht1 = gid.y < volumeSize.y - 1 ? *(height + volumeSize.x) : 0;
        if (lid.y == 0)
            *ht2 = gid.y > 0                ? *(height - volumeSize.x) : 0;
    }

    if (lid1D == cl_index_2d) localDone = 0;
    barrier(CLK_LOCAL_MEM_FENCE);
    
    char globalDone = 1;
    while(!localDone)
    {
        barrier(CLK_LOCAL_MEM_FENCE);

        // if (lid1D == cl_index_2d) localDone = 1;
		localDone = 1;
        barrier(CLK_LOCAL_MEM_FENCE);
        
        if (h > 0)
        {
            int t = h;
	        if (c.s0) h = min(h, *ht0 + 1);
	        if (c.s3) h = min(h, *ht3 + 1);
	        if (c.s1) h = min(h, *ht1 + 1);
	        if (c.s2) h = min(h, *ht2 + 1);
            if (t != h)
            {
                *heightt = h;
                localDone = globalDone = 0;
            }
        }
        barrier(CLK_LOCAL_MEM_FENCE);
    }
    
    if (!globalDone) localDone = 0;
    barrier(CLK_LOCAL_MEM_FENCE);

    if (lid1D == cl_index_2d) if (!localDone) *done = 0;

    if (h != oh) *height = h;
}

#else

__kernel void graphcut_init_global_relabel(
    const uint4 volumeSize, __global int* nodeExcessFlow, __global int* nodeHeight,
    const uint4 groupSize, __global int* depthData
    )
{
    int index = get_global_id(2);
    int3 tid = (int3)(0);
    tid.x = index % groupSize.x;
    index /= groupSize.x;
    tid.y = index % groupSize.y;
    index /= groupSize.y;
    tid.z = index;

    const int3 lid = (int3)(get_global_id(0), get_global_id(1) % cl_block_3d_y, get_global_id(1) / cl_block_3d_y);
    const int3 gid = lid + (int3)(cl_block_3d_x, cl_block_3d_y, cl_block_3d_z) * tid;
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y || gid.z >= volumeSize.z) return;

    const int lid1D = lid.x + cl_block_3d_x * (lid.y + cl_block_3d_y * lid.z);
    const int gid1D = gid.x + volumeSize.x  * (gid.y + volumeSize.y  * gid.z);

    __local int localDone;
    if (lid1D == 0) localDone = 0;
    barrier(CLK_LOCAL_MEM_FENCE);

    if (nodeExcessFlow[gid1D] < 0)
    {
        localDone = 1;
        nodeHeight[gid1D] = 0;
    }
    else
    {
        nodeHeight[gid1D] = cl_max_height;
    }
    barrier(CLK_LOCAL_MEM_FENCE);

    if (lid1D == 0) depthData[get_global_id(2)] = localDone ? (tid.x << cl_shift_3d_x) + (tid.y << cl_shift_3d_y) + (tid.z << cl_shift_3d_z) : (1 << 30) - 1;
}

__kernel void graphcut_global_relabel(
    const uint4 volumeSize, __global int* nodeHeight, __global uchar4* nodeCapacity1, __global uchar4* nodeCapacity2,
    const uint4 groupSize, __global int4* listData,
    __global int* done
    )
{
    const int3 tid = listData[get_global_id(2)].xyz;
    const int3 lid = (int3)(get_global_id(0), get_global_id(1) % cl_block_3d_y, get_global_id(1) / cl_block_3d_y);
    const int3 gid = lid + (int3)(cl_block_3d_x, cl_block_3d_y, cl_block_3d_z) * tid;
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y || gid.z >= volumeSize.z) return;
    
    const int lid1D = (lid.x + 1) + (cl_block_3d_x + 2) * ((lid.y + 1) + (cl_block_3d_y + 2) * (lid.z + 1));
    const int gid1D = (gid.x    ) + (volumeSize.x     ) * ((gid.y    ) + (volumeSize.y     ) * (gid.z    ));

    __local char localDone;
    __local int heightDatat[(cl_block_3d_x + 2) * (cl_block_3d_y + 2) * (cl_block_3d_z + 2)];
    __local int *heightt = heightDatat + lid1D;
    __local int *ht0, *ht1, *ht2, *ht3, *ht4, *ht5;

    __global int* height = nodeHeight + gid1D;
    __private uchar8 c = (uchar8)(nodeCapacity1[gid1D].s012, nodeCapacity2[gid1D].s012, 0, 0);
    __private int oh, h = oh = *height;
    
    *heightt = h;

    if (h > 0)
    {
        ht0 = heightt + 1,                   ht5 = heightt - 1;
        ht1 = heightt + (cl_block_3d_x + 2), ht4 = heightt - (cl_block_3d_x + 2);
        ht2 = heightt + (cl_block_3d_x + 2) * (cl_block_3d_y + 2);
        ht3 = heightt - (cl_block_3d_x + 2) * (cl_block_3d_y + 2);
        
        const int volumeOffset = volumeSize.x * volumeSize.y;
        if (gid.x == min(cl_block_3d_x * (tid.x + 1), (int)volumeSize.x) - 1)
            *ht0 = gid.x < volumeSize.x - 1 ? *(height + 1) : 0;
        if (lid.x == 0)
            *ht5 = gid.x > 0                ? *(height - 1) : 0;
        if (gid.y == min(cl_block_3d_y * (tid.y + 1), (int)volumeSize.y) - 1)
            *ht1 = gid.y < volumeSize.y - 1 ? *(height + volumeSize.x) : 0;
        if (lid.y == 0)
            *ht4 = gid.y > 0                ? *(height - volumeSize.x) : 0;
        if (gid.z == min(cl_block_3d_z * (tid.z + 1), (int)volumeSize.z) - 1)
            *ht2 = gid.z < volumeSize.z - 1 ? *(height + volumeOffset) : 0;
        if (lid.z == 0)
            *ht3 = gid.z > 0                ? *(height - volumeOffset) : 0;
    }

    if (lid1D == cl_index_3d) localDone = 0;
    barrier(CLK_LOCAL_MEM_FENCE);
    
    char globalDone = 1;
    while(!localDone)
    {
        barrier(CLK_LOCAL_MEM_FENCE);

        // if (lid1D == cl_index_3d) localDone = 1;
		localDone = 1;
        barrier(CLK_LOCAL_MEM_FENCE);
        
        if (h > 0)
        {
            int t = h;
	        if (c.s0) h = min(h, *ht0 + 1);
	        if (c.s5) h = min(h, *ht5 + 1);
	        if (c.s1) h = min(h, *ht1 + 1);
	        if (c.s4) h = min(h, *ht4 + 1);
	        if (c.s2) h = min(h, *ht2 + 1);
	        if (c.s3) h = min(h, *ht3 + 1);
            if (t != h)
            {
                *heightt = h;
                localDone = globalDone = 0;
            }
        }
        barrier(CLK_LOCAL_MEM_FENCE);
    }

    if (!globalDone) localDone = 0;
    barrier(CLK_LOCAL_MEM_FENCE);

    if (lid1D == cl_index_3d) if (!localDone) *done = 0;

    if (h != oh) *height = h;
}

#endif