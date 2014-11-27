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
 * @date    2013/10/23
 */
 
#ifdef cl_image_2d

void push_fast_t(
                int *ef,              int *eft,
    __global ushort *cap, __global ushort *capt
    )
{
    int c, f, t = min(c = *cap, f = *ef);
    if (t > 0)
    {
        *cap   = c - t;
        *ef    = f - t;
        *capt += t;
        *eft  += t;
    }
}

void push_fast_tt(
             int    *ef,  __global int    *eft,
             int    *h,   __global int    *ht,
    __global ushort *cap, __global ushort *capt
    )
{
    int c, f, t = min(c = *cap, f = *ef);
    if (t > 0 && *h - *ht == 1) // t > 0
    {
        *cap   = c - t;
        *ef    = f - t;
        *capt += t;
        *eft  += t;
    }
}

__kernel void graphcut_fast_relabel(
    const uint4 volumeSize,  __global int* nodeExcessFlow, __global int* nodeHeight, __global ushort2* nodeCapacity1, __global ushort2* nodeCapacity2,
    __global int4* listData, const uint parity
    )
{
    const int2 tid = listData[get_global_id(2)].xy;
    const int y = tid.y * cl_block_2d_y + ((get_global_id(1)));
    const int x = tid.x * cl_block_2d_x + ((get_global_id(0) << 1) + ((y + parity) & 1));
    if (x >= volumeSize.x || y >= volumeSize.y) return;
    
    __global int* height;
    const int id = x + volumeSize.x * y;
    int oh;
    if (nodeExcessFlow[id] < 0 || cl_max_height == (oh = *(height = nodeHeight + id))) return;
    
    const ushort2 c1 = nodeCapacity1[id];
    const ushort2 c2 = nodeCapacity2[id];
	int h = cl_max_height;
	if (c1.s0 > 0) h = min(h, *(height + 1) + 1);
	if (c2.s1 > 0) h = min(h, *(height - 1) + 1);
	if (c1.s1 > 0) h = min(h, *(height + volumeSize.x) + 1);
	if (c2.s0 > 0) h = min(h, *(height - volumeSize.x) + 1);
	if (h != oh) *height = h;
}

#define siz (cl_block_2d_x * cl_block_2d_y / (cl_local_size << 1))

__kernel void graphcut_fast_push_x(
    const uint4 volumeSize,  __global int* nodeExcessFlow, __global int* nodeHeight, __global ushort2* nodeCapacity1, __global ushort2* nodeCapacity2,
    __global int4* listData, const uint parity
    )
{
    const int2 tid = listData[get_global_id(2)].xy;
    const int y = tid.y * cl_block_2d_y + ((get_global_id(1)));
    const int x = tid.x * cl_block_2d_x + ((get_global_id(0) << 1) + ((y + parity) & 1)) * siz;
    if (x >= volumeSize.x || y >= volumeSize.y) return;

    const int id = x + volumeSize.x * y;
    const int lsiz = min(siz, (int)volumeSize.x - x);
    const int offset = 1;
    const int offc = offset << 1;
    const int offb = id - offset;
    const int offe = id + offset * lsiz;
    
    int height[siz], excessFlow[siz], oldExcessFlow[siz];
    int *ont, *ht, *nt, *ns = excessFlow + siz - 1;
    __global ushort *c1 = (__global ushort*)(nodeCapacity1 + id) + 0;
    __global ushort *c2 = (__global ushort*)(nodeCapacity2 + id + offset) + 1;
    __global int *n = nodeExcessFlow + id;
    __global int *h = nodeHeight + id;
    for (ont = oldExcessFlow, nt = excessFlow, ht = height; nt <= ns; ont++, nt++, ht++, n += offset, h += offset)
    {
        *nt = *ont = *n;
        *ht = *h;
    }
    
    // left -> right
    for (nt = excessFlow, ht = height; nt < ns; nt++, ht++, c1 += offc, c2 += offc)
        if (*ht - *(ht + 1) == 1)
            push_fast_t(nt, nt + 1, c1, c2);
    push_fast_tt(nt, nodeExcessFlow + offe, ht, nodeHeight + offe, c1, c2);
    
    // right -> left
    c2 -= offc; c1 -= offc;
    for ( ; nt > excessFlow; nt--, ht--, c1 -= offc, c2 -= offc)
        if (*ht - *(ht - 1) == 1)
            push_fast_t(nt, nt - 1, c2, c1);
    push_fast_tt(nt, nodeExcessFlow + offb, ht, nodeHeight + offb, c2, c1);

    n = nodeExcessFlow + id;
    ont = oldExcessFlow;
    for ( ; nt <= ns; ont++, nt++, n += offset)
        if (*nt != *ont) *n = *nt;
}

__kernel void graphcut_fast_push_y(
    const uint4 volumeSize,  __global int* nodeExcessFlow, __global int* nodeHeight, __global ushort2* nodeCapacity1, __global ushort2* nodeCapacity2,
    __global int4* listData, const uint parity
    )
{
    const int2 tid = listData[get_global_id(2)].xy;
    const int x = tid.x * cl_block_2d_x + ((get_global_id(1)));
    const int y = tid.y * cl_block_2d_y + ((get_global_id(0) << 1) + ((x + parity) & 1)) * siz;
    if (x >= volumeSize.x || y >= volumeSize.y) return;

    const int id = x + volumeSize.x * y;
    const int lsiz = min(siz, (int)volumeSize.y - y);
    const int offset = volumeSize.x;
    const int offc = offset << 1;
    const int offb = id - offset;
    const int offe = id + offset * lsiz;
    
    int height[siz], excessFlow[siz], oldExcessFlow[siz];
    int *ont, *ht, *nt, *ns = excessFlow + siz - 1;
    __global ushort *c1 = (__global ushort*)(nodeCapacity1 + id) + 1;
    __global ushort *c2 = (__global ushort*)(nodeCapacity2 + id + offset) + 0;
    __global int *n = nodeExcessFlow + id;
    __global int *h = nodeHeight + id;
    for (ont = oldExcessFlow, nt = excessFlow, ht = height; nt <= ns; ont++, nt++, ht++, n += offset, h += offset)
    {
        *nt = *ont = *n;
        *ht = *h;
    }
    
    // top -> bottom
    for (nt = excessFlow, ht = height; nt < ns; nt++, ht++, c1 += offc, c2 += offc)
        if (*ht - *(ht + 1) == 1)
            push_fast_t(nt, nt + 1, c1, c2);
    push_fast_tt(nt, nodeExcessFlow + offe, ht, nodeHeight + offe, c1, c2);
    
    // bottom -> top
    c2 -= offc; c1 -= offc;
    for ( ; nt > excessFlow; nt--, ht--, c1 -= offc, c2 -= offc)
        if (*ht - *(ht - 1) == 1)
            push_fast_t(nt, nt - 1, c2, c1);
    push_fast_tt(nt, nodeExcessFlow + offb, ht, nodeHeight + offb, c2, c1);

    n = nodeExcessFlow + id;
    ont = oldExcessFlow;
    for ( ; nt <= ns; ont++, nt++, n += offset)
        if (*nt != *ont) *n = *nt;
}

#else

void push_fast_t(
             int   *ef,           int   *eft,
    __global uchar *cap, __global uchar *capt
    )
{
    int c, f, t = min(c = *cap, f = *ef);
    if (t > 0)
    {
        *cap   = c - t;
        *ef    = f - t;
        *capt += t;
        *eft  += t;
    }
}

void push_fast_tt(
             int   *ef,  __global int   *eft,
             int   *h,   __global int   *ht,
    __global uchar *cap, __global uchar *capt
    )
{
    int c, f, t = min(c = *cap, f = *ef);
    if (t > 0 && *h - *ht == 1) // t > 0 ensures that nodet won't be accessed even though it is out of bounds 
    {
        *cap   = c - t;
        *ef    = f - t;
        *capt += t;
        *eft  += t;
    }
}

__kernel void graphcut_fast_relabel(
    const uint4 volumeSize,  __global int* nodeExcessFlow, __global int* nodeHeight, __global uchar4* nodeCapacity1, __global uchar4* nodeCapacity2,
    __global int4* listData, const uint parity
    )
{
    const int3 tid = listData[get_global_id(2)].xyz;
    const int siz = (cl_block_3d_x >> 1) / get_global_size(0);
    const int z = tid.z * cl_block_3d_z + ((get_global_id(1) / cl_block_3d_y));
    const int y = tid.y * cl_block_3d_y + ((get_global_id(1) % cl_block_3d_y));
    const int x = tid.x * cl_block_3d_x + ((get_global_id(0) << 1) + ((z + y + parity) & 1)) * siz;
    if (x >= volumeSize.x || y >= volumeSize.y || z >= volumeSize.z) return;

    __global int* height;
    const int id = x + volumeSize.x * (y + volumeSize.y * z);
    int oh;
    if (nodeExcessFlow[id] < 0 || cl_max_height == (oh = *(height = nodeHeight + id))) return;
    
    const int offset = volumeSize.x * volumeSize.y;
    const uchar4 c1 = nodeCapacity1[id];
    const uchar4 c2 = nodeCapacity2[id];
	int h = cl_max_height;
	if (c1.s0 > 0) h = min(h, *(height + 1) + 1);
	if (c2.s2 > 0) h = min(h, *(height - 1) + 1);
	if (c1.s1 > 0) h = min(h, *(height + volumeSize.x) + 1);
	if (c2.s1 > 0) h = min(h, *(height - volumeSize.x) + 1);
	if (c1.s2 > 0) h = min(h, *(height + offset) + 1);
	if (c2.s0 > 0) h = min(h, *(height - offset) + 1);
	if (h != oh) *height = h;
}

#define sizx (cl_block_3d_x >> 1)
#define sizy (cl_block_3d_y >> 1)
#define sizz (cl_block_3d_z >> 1)

__kernel void graphcut_fast_push_x(
    const uint4 volumeSize,  __global int* nodeExcessFlow, __global int* nodeHeight, __global uchar4* nodeCapacity1, __global uchar4* nodeCapacity2,
    __global int4* listData, const uint parity
    )
{
    const int3 tid = listData[get_global_id(2)].xyz;
    const int z = tid.z * cl_block_3d_z + ((get_global_id(1) / cl_block_3d_y));
    const int y = tid.y * cl_block_3d_y + ((get_global_id(1) % cl_block_3d_y));
    const int x = tid.x * cl_block_3d_x + ((get_global_id(0) << 1) + ((z + y + parity) & 1)) * sizx;
    if (x >= volumeSize.x || y >= volumeSize.y || z >= volumeSize.z) return;

    const int id = x + volumeSize.x * (y + volumeSize.y * z);
    const int lsiz = min(sizx, (int)volumeSize.x - x);
    const int offset = 1;
    const int offc = offset << 2;
    const int offb = id - offset;
    const int offe = id + offset * lsiz;
    
    int height[sizx], excessFlow[sizx], oldExcessFlow[sizx];
    int *ont, *ht, *nt, *ns = excessFlow + sizx - 1;
    __global uchar *c1 = (__global uchar*)(nodeCapacity1 + id) + 0;
    __global uchar *c2 = (__global uchar*)(nodeCapacity2 + id + offset) + 2;
    __global int *n = nodeExcessFlow + id;
    __global int *h = nodeHeight + id;
    for (ont = oldExcessFlow, nt = excessFlow, ht = height; nt <= ns; ont++, nt++, ht++, n += offset, h += offset)
    {
        *nt = *ont = *n;
        *ht = *h;
    }
    
    // left -> right
    for (nt = excessFlow, ht = height; nt < ns; nt++, ht++, c1 += offc, c2 += offc)
        if (*ht - *(ht + 1) == 1)
            push_fast_t(nt, nt + 1, c1, c2);
    push_fast_tt(nt, nodeExcessFlow + offe, ht, nodeHeight + offe, c1, c2);
    
    // right -> left
    c2 -= offc; c1 -= offc;
    for ( ; nt > excessFlow; nt--, ht--, c1 -= offc, c2 -= offc)
        if (*ht - *(ht - 1) == 1)
            push_fast_t(nt, nt - 1, c2, c1);
    push_fast_tt(nt, nodeExcessFlow + offb, ht, nodeHeight + offb, c2, c1);

    n = nodeExcessFlow + id;
    ont = oldExcessFlow;
    for ( ; nt <= ns; ont++, nt++, n += offset)
        if (*nt != *ont) *n = *nt;
}

__kernel void graphcut_fast_push_y(
    const uint4 volumeSize,  __global int* nodeExcessFlow, __global int* nodeHeight, __global uchar4* nodeCapacity1, __global uchar4* nodeCapacity2,
    __global int4* listData, const uint parity
    )
{
    const int3 tid = listData[get_global_id(2)].xyz;
    const int z = tid.z * cl_block_3d_z + ((get_global_id(1) / cl_block_3d_x));
    const int x = tid.x * cl_block_3d_x + ((get_global_id(1) % cl_block_3d_x));
    const int y = tid.y * cl_block_3d_y + ((get_global_id(0) << 1) + ((z + x + parity) & 1)) * sizy;
    if (x >= volumeSize.x || y >= volumeSize.y || z >= volumeSize.z) return;

    const int id = x + volumeSize.x * (y + volumeSize.y * z);
    const int lsiz = min(sizy, (int)volumeSize.y - y);
    const int offset = volumeSize.x;
    const int offc = offset << 2;
    const int offb = id - offset;
    const int offe = id + offset * lsiz;
    
    int height[sizy], excessFlow[sizy], oldExcessFlow[sizy];
    int *ont, *ht, *nt, *ns = excessFlow + sizy - 1;
    __global uchar *c1 = (__global uchar*)(nodeCapacity1 + id) + 1;
    __global uchar *c2 = (__global uchar*)(nodeCapacity2 + id + offset) + 1;
    __global int *n = nodeExcessFlow + id;
    __global int *h = nodeHeight + id;
    for (ont = oldExcessFlow, nt = excessFlow, ht = height; nt <= ns; ont++, nt++, ht++, n += offset, h += offset)
    {
        *nt = *ont = *n;
        *ht = *h;
    }
    
    // top -> bottom
    for (nt = excessFlow, ht = height; nt < ns; nt++, ht++, c1 += offc, c2 += offc)
        if (*ht - *(ht + 1) == 1)
            push_fast_t(nt, nt + 1, c1, c2);
    push_fast_tt(nt, nodeExcessFlow + offe, ht, nodeHeight + offe, c1, c2);
    
    // bottom -> top
    c2 -= offc; c1 -= offc;
    for ( ; nt > excessFlow; nt--, ht--, c1 -= offc, c2 -= offc)
        if (*ht - *(ht - 1) == 1)
            push_fast_t(nt, nt - 1, c2, c1);
    push_fast_tt(nt, nodeExcessFlow + offb, ht, nodeHeight + offb, c2, c1);

    n = nodeExcessFlow + id;
    ont = oldExcessFlow;
    for ( ; nt <= ns; ont++, nt++, n += offset)
        if (*nt != *ont) *n = *nt;
}

__kernel void graphcut_fast_push_z(
    const uint4 volumeSize,  __global int* nodeExcessFlow, __global int* nodeHeight, __global uchar4* nodeCapacity1, __global uchar4* nodeCapacity2,
    __global int4* listData, const uint parity
    )
{
    const int3 tid = listData[get_global_id(2)].xyz;
    // const int siz = (cl_block_3d_z >> 1) / get_global_size(0);
    const int y = tid.y * cl_block_3d_y + ((get_global_id(1) / cl_block_3d_x));
    const int x = tid.x * cl_block_3d_x + ((get_global_id(1) % cl_block_3d_x));
    const int z = tid.z * cl_block_3d_z + ((get_global_id(0) << 1) + ((y + x + parity) & 1)) * sizz;
    if (x >= volumeSize.x || y >= volumeSize.y || z >= volumeSize.z) return;

    const int id = x + volumeSize.x * (y + volumeSize.y * z);
    const int lsiz = min(sizz, (int)volumeSize.z - z);
    const int offset = volumeSize.x * volumeSize.y;
    const int offc = offset << 2;
    const int offb = id - offset;
    const int offe = id + offset * lsiz;
    
    int height[sizz], excessFlow[sizz], oldExcessFlow[sizz];
    int *ont, *ht, *nt, *ns = excessFlow + sizz - 1;
    __global uchar *c1 = (__global uchar*)(nodeCapacity1 + id) + 2;
    __global uchar *c2 = (__global uchar*)(nodeCapacity2 + id + offset) + 0;
    __global int *n = nodeExcessFlow + id;
    __global int *h = nodeHeight + id;
    for (ont = oldExcessFlow, nt = excessFlow, ht = height; nt <= ns; ont++, nt++, ht++, n += offset, h += offset)
    {
        *nt = *ont = *n;
        *ht = *h;
    }
    
    // front -> back
    for (nt = excessFlow, ht = height; nt < ns; nt++, ht++, c1 += offc, c2 += offc)
        if (*ht - *(ht + 1) == 1)
            push_fast_t(nt, nt + 1, c1, c2);
    push_fast_tt(nt, nodeExcessFlow + offe, ht, nodeHeight + offe, c1, c2);
    
    // back -> front
    c2 -= offc; c1 -= offc;
    for ( ; nt > excessFlow; nt--, ht--, c1 -= offc, c2 -= offc)
        if (*ht - *(ht - 1) == 1)
            push_fast_t(nt, nt - 1, c2, c1);
    push_fast_tt(nt, nodeExcessFlow + offb, ht, nodeHeight + offb, c2, c1);

    n = nodeExcessFlow + id;
    ont = oldExcessFlow;
    for ( ; nt <= ns; ont++, nt++, n += offset)
        if (*nt != *ont) *n = *nt;
}

#endif
