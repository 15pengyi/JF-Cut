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
 * @date    2013/03/20
 */

__kernel void clear(
    __global uchar *textureData,
    const uint textureEnd,  const uint textureStride,
    const uint clearOffset, const uint clearSize
    )
{
    const int id = get_global_id(0);
    if (id >= textureEnd) return;

    __global uchar *start = textureData + id * textureStride + clearOffset;
    __global uchar *end = start + clearSize;
    for (__global uchar *i = start; i != end; i++)
        *i = 0;
}