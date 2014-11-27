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
 * @date    2013/04/23
 */

#ifdef cl_image_2d

__kernel void graphcut_compute_flow(
    const uint4 volumeSize, __global int* nodeExcessFlow,
    const uint histogramSize, __global int* histogramData
    )
{
    const int2 id = (int2)(get_global_id(0), get_global_id(1));
    if (id.x >= volumeSize.x || id.y >= volumeSize.y) return;
    
    const int index = id.x + volumeSize.x * id.y;
    const int level = index % histogramSize;
    const int flow = nodeExcessFlow[index];
    if (flow > 0) atomic_add(histogramData + level, flow);
}

#else

__kernel void graphcut_compute_flow(
    const uint4 volumeSize, __global int* nodeExcessFlow,
    const uint histogramSize, __global int* histogramData
    )
{
    const int3 id = (int3)(get_global_id(0), get_global_id(1), get_global_id(2));
    if (id.x >= volumeSize.x || id.y >= volumeSize.y || id.z >= volumeSize.z) return;

    const int index = id.x + volumeSize.x * (id.y + volumeSize.y * id.z);
    const int level = index % histogramSize;
    const int flow = nodeExcessFlow[index];
    if (flow > 0) atomic_add(histogramData + level, flow);
}

#endif