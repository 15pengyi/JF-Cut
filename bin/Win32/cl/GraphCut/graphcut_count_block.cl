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
 * @date    2013/05/29
 */

#ifdef cl_image_2d

__kernel void graphcut_count_node(
    __global int* nodeExcessFlow, __global int* nodeHeight,
    const uint4 volumeSize, const uint4 groupSize,
    __global int* activeTile, __global int* activeTileOdd
    )
{
    const int2 tid = (int2)(get_global_id(2) % groupSize.x, get_global_id(2) / groupSize.x);
    const int2 lid = (int2)(get_global_id(0), get_global_id(1));
    const int2 gid = lid + (int2)(cl_block_2d_x, cl_block_2d_y) * tid;
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y) return;

    const int lid1D = lid.x + cl_block_2d_x * lid.y;
	const int gid1D = gid.x + volumeSize.x  * gid.y;

    __local int localDone;
    if (lid1D == 0) localDone = 0;
    barrier(CLK_LOCAL_MEM_FENCE);
    
    if (nodeExcessFlow[gid1D] >= 0 && nodeHeight[gid1D] < cl_max_height) localDone = 1;
    barrier(CLK_LOCAL_MEM_FENCE);

    if (lid1D == 0)
    {
        const int parity = (tid.x + tid.y) & 1;
        const int done = localDone;
        activeTile[get_global_id(2)] = (1 - parity) * done;
        activeTileOdd[get_global_id(2)] = parity * done;
    }
}

__kernel void graphcut_scatter_node(
    const uint listOffset, __global int4* listData,
    const uint4 groupSize, __global int* activeTile, __global int* activeTileOdd
    )
{
    const int2 id = (int2)(get_global_id(0), get_global_id(1));
    if (id.x >= groupSize.x || id.y >= groupSize.y) return;

    const int index = id.x + groupSize.x * id.y;
    const int previous = activeTile[index];
    const int current = activeTile[index + 1];
    if (current > previous) listData[previous].xy = id;

    const int previousOdd = activeTileOdd[index];
    const int currentOdd = activeTileOdd[index + 1];
    if (currentOdd > previousOdd) listData[listOffset + previousOdd].xy = id;
}

__kernel void graphcut_count_cut(
    const uint4 volumeSize, __global cl_cut *cutData,
    const uint4 groupSize, __global int* activeTile,
    const uint textureOffset
    )
{
    const int2 tid = (int2)(get_global_id(2) % groupSize.x, get_global_id(2) / groupSize.x);
    const int2 lid = (int2)(get_global_id(0), get_global_id(1));
    const int2 gid = lid + (int2)(cl_block_2d_x, cl_block_2d_y) * tid;
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y) return;
    
    const int lid1D = lid.x + cl_block_2d_x * lid.y;
	const int gid1D = gid.x + volumeSize.x  * gid.y;

    __local int localDone;
    if (lid1D == 0) localDone = 0;
    barrier(CLK_LOCAL_MEM_FENCE);
    
    __global char* cut = (__global char*)(cutData + gid1D);
    if (cut[textureOffset] == CHAR_MAX) localDone = 1;
    barrier(CLK_LOCAL_MEM_FENCE);

    if (lid1D == 0) activeTile[get_global_id(2)] = localDone;
}

__kernel void graphcut_scatter_cut(
    const uint listOffset, __global int4* listData,
    const uint4 groupSize, __global int* activeTile
    )
{
    const int2 id = (int2)(get_global_id(0), get_global_id(1));
    if (id.x >= groupSize.x || id.y >= groupSize.y) return;

    const int index = id.x + groupSize.x * id.y;
    const int previous = activeTile[index];
    const int current = activeTile[index + 1];
    if (current > previous) listData[previous].xy = id;
}

#else

__kernel void graphcut_count_node(
    __global int* nodeExcessFlow, __global int* nodeHeight,
    const uint4 volumeSize, const uint4 groupSize,
    __global int* activeTile, __global int* activeTileOdd
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
    
    if (nodeExcessFlow[gid1D] >= 0 && nodeHeight[gid1D] < cl_max_height) localDone = 1;
    barrier(CLK_LOCAL_MEM_FENCE);

    if (lid1D == 0)
    {
        const int parity = (tid.x + tid.y + tid.z) & 1;
        const int done = localDone;
        activeTile[get_global_id(2)] = (1 - parity) * done;
        activeTileOdd[get_global_id(2)] = parity * done;
    }
}

__kernel void graphcut_scatter_node(
    const uint listOffset, __global int4* listData,
    const uint4 groupSize, __global int* activeTile, __global int* activeTileOdd
    )
{
    const int3 id = (int3)(get_global_id(0), get_global_id(1), get_global_id(2));
    if (id.x >= groupSize.x || id.y >= groupSize.y || id.z >= groupSize.z) return;

    const int index = id.x + groupSize.x * (id.y + groupSize.y * id.z);
    const int previous = activeTile[index];
    const int current = activeTile[index + 1];
    if (current > previous) listData[previous].xyz = id;

    const int previousOdd = activeTileOdd[index];
    const int currentOdd = activeTileOdd[index + 1];
    if (currentOdd > previousOdd) listData[listOffset + previousOdd].xyz = id;
}

__kernel void graphcut_count_cut(
    const uint4 volumeSize, __global cl_cut *cutData,
    const uint4 groupSize, __global int* activeTile,
    const uint textureOffset
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
    
    __global char* cut = (__global char*)(cutData + gid1D);
    if (cut[textureOffset] == CHAR_MAX) localDone = 1;
    barrier(CLK_LOCAL_MEM_FENCE);

    if (lid1D == 0) activeTile[get_global_id(2)] = localDone;
}

__kernel void graphcut_scatter_cut(
    const uint listOffset, __global int4* listData,
    const uint4 groupSize, __global int* activeTile
    )
{
    const int3 id = (int3)(get_global_id(0), get_global_id(1), get_global_id(2));
    if (id.x >= groupSize.x || id.y >= groupSize.y || id.z >= groupSize.z) return;

    const int index = id.x + groupSize.x * (id.y + groupSize.y * id.z);
    const int previous = activeTile[index];
    const int current = activeTile[index + 1];
    if (current > previous) listData[previous].xyz = id;
}

#endif
