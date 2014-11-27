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
 * @date    2013/05/12
 */
 
#ifdef cl_image_2d

#define D0  ( 1)
#define D3  (-1)
#define D1  ( (cl_block_2d_x + 2))
#define D2  (-(cl_block_2d_x + 2))
#define T2D   (cl_block_2d_x + 2) * (cl_block_2d_y + 2)

__kernel void graphcut_relabel_push(
    __global int* nodeExcessFlow, __global int* nodeHeight, __global ushort2* nodeCapacity1, __global ushort2* nodeCapacity2,
    const uint4 volumeSize, __global int4* listData, __global int* activeTile
    )
{
    const int2 tid = listData[get_global_id(2)].xy;
    const int2 lid = (int2)(get_global_id(0), get_global_id(1));
    const int2 gid = lid + (int2)(cl_block_2d_x, cl_block_2d_y) * tid;
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y) return;
    
    const int lid1D = (lid.x + 1) + (cl_block_2d_x + 2) * (lid.y + 1);
    const int gid1D = (gid.x    ) + (volumeSize.x     ) * (gid.y    );
    
    __local char    localDone;
    __local int     nodeExcessFlowL[T2D];
    __local int     nodeHeightL    [T2D];
    __local ushort2 nodeCapacity1L [T2D];
    __local ushort2 nodeCapacity2L [T2D];
    __local int     *excessFlowL = nodeExcessFlowL + lid1D;
    __local int     *heightL     = nodeHeightL     + lid1D;
    __local ushort2 *capacity1L  = nodeCapacity1L  + lid1D;
    __local ushort2 *capacity2L  = nodeCapacity2L  + lid1D;
    
    __global int *heightG, *excessFlowG;
    __global ushort2 *capacity1G, *capacity2G;
    __private int height, oldHeight;
    __private int excessFlow, oldExcessFlow;
    __private ushort2 oldCapacity1, oldCapacity2;
    __private char act, actt, parity = (gid.x + gid.y) & 1;
    if (act = (height = oldHeight = *(heightG = nodeHeight + gid1D)) < cl_max_height)
    {
        *heightL     = height;
        *excessFlowL = excessFlow = oldExcessFlow = *(excessFlowG = nodeExcessFlow + gid1D);
        *capacity1L  = oldCapacity1 = *(capacity1G = nodeCapacity1  + gid1D);
        *capacity2L  = oldCapacity2 = *(capacity2G = nodeCapacity2  + gid1D);

        if (gid.x == min(cl_block_2d_x * (tid.x + 1), (int)volumeSize.x) - 1)
            { excessFlowL[D0] = 0; heightL[D0] = select(0, heightG[ 1],            gid.x < volumeSize.x - 1); }
        if (lid.x == 0)
            { excessFlowL[D3] = 0; heightL[D3] = select(0, heightG[-1],            gid.x > 0); }
        if (gid.y == min(cl_block_2d_y * (tid.y + 1), (int)volumeSize.y) - 1)
            { excessFlowL[D1] = 0; heightL[D1] = select(0, heightG[ volumeSize.x], gid.y < volumeSize.y - 1); }
        if (lid.y == 0)
            { excessFlowL[D2] = 0; heightL[D2] = select(0, heightG[-volumeSize.x], gid.y > 0); }
    }
    else
    {
        *heightL = cl_max_height;
    }
    if (lid1D == cl_index_2d) localDone = 0;
    barrier(CLK_LOCAL_MEM_FENCE);

    while(!localDone)
    {
        actt = ((excessFlow = *excessFlowL) >= 0) & (height < cl_max_height);
        if (actt & ~parity)
        {
            const ushort4 c = (ushort4)(*capacity1L, *capacity2L);
            height = select(cl_max_height, min(cl_max_height, heightL[D0] + 1), (int)c.s0);
            height = select(       height, min(       height, heightL[D3] + 1), (int)c.s3);
            height = select(       height, min(       height, heightL[D1] + 1), (int)c.s1);
            height = select(       height, min(       height, heightL[D2] + 1), (int)c.s2);
	        *heightL = height;
        }
        barrier(CLK_LOCAL_MEM_FENCE);

        if (actt & parity)
        {
            const ushort4 c = (ushort4)(*capacity1L, *capacity2L);
            height = select(cl_max_height, min(cl_max_height, heightL[D0] + 1), (int)c.s0);
            height = select(       height, min(       height, heightL[D3] + 1), (int)c.s3);
            height = select(       height, min(       height, heightL[D1] + 1), (int)c.s1);
            height = select(       height, min(       height, heightL[D2] + 1), (int)c.s2);
	        *heightL = height;
        }
        localDone = 1;
        barrier(CLK_LOCAL_MEM_FENCE);
        
        actt &= height < cl_max_height;
        if (actt & ~parity)
        {
            int t;
            const ushort4 c = (ushort4)(*capacity1L, *capacity2L);
            if (((t = min((int)c.s0, excessFlow)) > 0) & (height - heightL[D0] == 1))
            {
                *((__local ushort*)(capacity1L     ) + 0)  = c.s0 - t;
                *((__local ushort*)(capacity2L + D0) + 1) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D0, t);
                localDone = 0;
            }
            if (((t = min((int)c.s3, excessFlow)) > 0) & (height - heightL[D3] == 1))
            {
                *((__local ushort*)(capacity2L     ) + 1)  = c.s3 - t;
                *((__local ushort*)(capacity1L + D3) + 0) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D3, t);
                localDone = 0;
            }
            if (((t = min((int)c.s1, excessFlow)) > 0) & (height - heightL[D1] == 1))
            {
                *((__local ushort*)(capacity1L     ) + 1)  = c.s1 - t;
                *((__local ushort*)(capacity2L + D1) + 0) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D1, t);
                localDone = 0;
            }
            if (((t = min((int)c.s2, excessFlow)) > 0) & (height - heightL[D2] == 1))
            {
                *((__local ushort*)(capacity2L     ) + 0)  = c.s2 - t;
                *((__local ushort*)(capacity1L + D2) + 1) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D2, t);
                localDone = 0;
            }
        }
        barrier(CLK_LOCAL_MEM_FENCE);

        if (actt & parity)
        {
            excessFlow = *excessFlowL;
            int t;
            const ushort4 c = (ushort4)(*capacity1L, *capacity2L);
            if (((t = min((int)c.s0, excessFlow)) > 0) & (height - heightL[D0] == 1))
            {
                *((__local ushort*)(capacity1L     ) + 0)  = c.s0 - t;
                *((__local ushort*)(capacity2L + D0) + 1) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D0, t);
                localDone = 0;
            }
            if (((t = min((int)c.s3, excessFlow)) > 0) & (height - heightL[D3] == 1))
            {
                *((__local ushort*)(capacity2L     ) + 1)  = c.s3 - t;
                *((__local ushort*)(capacity1L + D3) + 0) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D3, t);
                localDone = 0;
            }
            if (((t = min((int)c.s1, excessFlow)) > 0) & (height - heightL[D1] == 1))
            {
                *((__local ushort*)(capacity1L     ) + 1)  = c.s1 - t;
                *((__local ushort*)(capacity2L + D1) + 0) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D1, t);
                localDone = 0;
            }
            if (((t = min((int)c.s2, excessFlow)) > 0) & (height - heightL[D2] == 1))
            {
                *((__local ushort*)(capacity2L     ) + 0)  = c.s2 - t;
                *((__local ushort*)(capacity1L + D2) + 1) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D2, t);
                localDone = 0;
            }
        }
        barrier(CLK_LOCAL_MEM_FENCE);
    }
    
    if (act)
    {
        int f;
        if ((lid.x == cl_block_2d_x - 1) & ((f = excessFlowL[D0]) > 0))
            { atomic_add(excessFlowG + 1, f);            *((__global ushort*)(capacity2G + 1) + 1) += f; }
        if ((lid.x == 0                ) & ((f = excessFlowL[D3]) > 0))
            { atomic_add(excessFlowG - 1, f);            *((__global ushort*)(capacity1G - 1) + 0) += f; }
        if ((lid.y == cl_block_2d_y - 1) & ((f = excessFlowL[D1]) > 0))
            { atomic_add(excessFlowG + volumeSize.x, f); *((__global ushort*)(capacity2G + volumeSize.x) + 0) += f; }
        if ((lid.y == 0                ) & ((f = excessFlowL[D2]) > 0))
            { atomic_add(excessFlowG - volumeSize.x, f); *((__global ushort*)(capacity1G - volumeSize.x) + 1) += f; }

        const ushort2 c1 = *capacity1L;
        const ushort2 c2 = *capacity2L;
        if ((excessFlow = *excessFlowL) != oldExcessFlow) *excessFlowG = excessFlow;
        if (height != oldHeight) *heightG = height;
        if (*((uint*)&c1) != *((uint*)&oldCapacity1)) *capacity1G  = c1;
        if (*((uint*)&c2) != *((uint*)&oldCapacity2)) *capacity2G  = c2;
    }
}

#else

#define D0  ( 1)
#define D5  (-1)
#define D1  ( (cl_block_3d_x + 2))
#define D4  (-(cl_block_3d_x + 2))
#define D2  ( (cl_block_3d_x + 2) * (cl_block_3d_y + 2))
#define D3  (-(cl_block_3d_x + 2) * (cl_block_3d_y + 2))
#define T3D   (cl_block_3d_x + 2) * (cl_block_3d_y + 2) * (cl_block_3d_z + 2)

__kernel void graphcut_relabel_push(
    __global int* nodeExcessFlow, __global int* nodeHeight, __global uchar4* nodeCapacity1, __global uchar4* nodeCapacity2,
    const uint4 volumeSize, __global int4* listData, __global int* activeTile
    )
{
    const int3 tid = listData[get_global_id(2)].xyz;
    const int3 lid = (int3)(get_global_id(0), get_global_id(1) % cl_block_3d_y, get_global_id(1) / cl_block_3d_y);
    const int3 gid = lid + (int3)(cl_block_3d_x, cl_block_3d_y, cl_block_3d_z) * tid;
    if (gid.x >= volumeSize.x || gid.y >= volumeSize.y || gid.z >= volumeSize.z) return;

    const int lid1D = (lid.x + 1) + (cl_block_3d_x + 2) * ((lid.y + 1) + (cl_block_3d_y + 2) * (lid.z + 1));
    const int gid1D = (gid.x    ) + (volumeSize.x     ) * ((gid.y    ) + (volumeSize.y     ) * (gid.z    ));

    __local char   localDone;
    __local int    nodeExcessFlowL[T3D];
    __local int    nodeHeightL    [T3D];
    __local uchar4 nodeCapacity1L [T3D];
    __local uchar4 nodeCapacity2L [T3D];
    __local int    *excessFlowL = nodeExcessFlowL + lid1D;
    __local int    *heightL     = nodeHeightL     + lid1D;
    __local uchar4 *capacity1L  = nodeCapacity1L  + lid1D;
    __local uchar4 *capacity2L  = nodeCapacity2L  + lid1D;
    
    __global int *heightG, *excessFlowG;
    __global uchar4 *capacity1G, *capacity2G;
    __private int height, oldHeight;
    __private int excessFlow, oldExcessFlow;
    __private int offset;
    __private uchar4 oldCapacity1, oldCapacity2;
    __private char act, actt, parity = (gid.x + gid.y + gid.z) & 1;
    if (act = (height = oldHeight = *(heightG = nodeHeight + gid1D)) < cl_max_height)
    {
        *heightL     = height;
        *excessFlowL = excessFlow = oldExcessFlow = *(excessFlowG = nodeExcessFlow + gid1D);
        *capacity1L  = oldCapacity1 = *(capacity1G = nodeCapacity1  + gid1D);
        *capacity2L  = oldCapacity2 = *(capacity2G = nodeCapacity2  + gid1D);
        
        offset = volumeSize.x * volumeSize.y;
        if (gid.x == min(cl_block_3d_x * (tid.x + 1), (int)volumeSize.x) - 1)
            { excessFlowL[D0] = 0; heightL[D0] = select(0, heightG[ 1],            gid.x < volumeSize.x - 1); }
        if (lid.x == 0)
            { excessFlowL[D5] = 0; heightL[D5] = select(0, heightG[-1],            gid.x > 0); }
        if (gid.y == min(cl_block_3d_y * (tid.y + 1), (int)volumeSize.y) - 1)
            { excessFlowL[D1] = 0; heightL[D1] = select(0, heightG[ volumeSize.x], gid.y < volumeSize.y - 1); }
        if (lid.y == 0)
            { excessFlowL[D4] = 0; heightL[D4] = select(0, heightG[-volumeSize.x], gid.y > 0); }
        if (gid.z == min(cl_block_3d_z * (tid.z + 1), (int)volumeSize.z) - 1)
            { excessFlowL[D2] = 0; heightL[D2] = select(0, heightG[ offset],       gid.z < volumeSize.z - 1); }
        if (lid.z == 0)
            { excessFlowL[D3] = 0; heightL[D3] = select(0, heightG[-offset],       gid.z > 0); }
    }
    else
    {
        *heightL = cl_max_height;
    }
    if (lid1D == cl_index_3d) localDone = 0;
    barrier(CLK_LOCAL_MEM_FENCE);

    while(!localDone)
    {
        actt = ((excessFlow = *excessFlowL) >= 0) & (height < cl_max_height);
        if (actt & ~parity)
        {
            const uchar8 c = (uchar8)(*capacity1L, *capacity2L);
            height = select(cl_max_height, min(cl_max_height, heightL[D0] + 1), (int)c.s0);
            height = select(       height, min(       height, heightL[D5] + 1), (int)c.s6);
            height = select(       height, min(       height, heightL[D1] + 1), (int)c.s1);
            height = select(       height, min(       height, heightL[D4] + 1), (int)c.s5);
            height = select(       height, min(       height, heightL[D2] + 1), (int)c.s2);
            height = select(       height, min(       height, heightL[D3] + 1), (int)c.s4);
	        *heightL = height;
        }
        barrier(CLK_LOCAL_MEM_FENCE);

        if (actt & parity)
        {
            const uchar8 c = (uchar8)(*capacity1L, *capacity2L);
            height = select(cl_max_height, min(cl_max_height, heightL[D0] + 1), (int)c.s0);
            height = select(       height, min(       height, heightL[D5] + 1), (int)c.s6);
            height = select(       height, min(       height, heightL[D1] + 1), (int)c.s1);
            height = select(       height, min(       height, heightL[D4] + 1), (int)c.s5);
            height = select(       height, min(       height, heightL[D2] + 1), (int)c.s2);
            height = select(       height, min(       height, heightL[D3] + 1), (int)c.s4);
	        *heightL = height;
        }
        localDone = 1;
        barrier(CLK_LOCAL_MEM_FENCE);
        
        actt &= height < cl_max_height;
        if (actt & ~parity)
        {
            int t;
            const uchar8 c = (uchar8)(*capacity1L, *capacity2L);
            if (((t = min((int)c.s0, excessFlow)) > 0) & (height - heightL[D0] == 1))
            {
                *((__local uchar*)(capacity1L     ) + 0)  = c.s0 - t;
                *((__local uchar*)(capacity2L + D0) + 2) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D0, t);
                localDone = 0;
            }
            if (((t = min((int)c.s6, excessFlow)) > 0) & (height - heightL[D5] == 1))
            {
                *((__local uchar*)(capacity2L     ) + 2)  = c.s6 - t;
                *((__local uchar*)(capacity1L + D5) + 0) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D5, t);
                localDone = 0;
            }
            if (((t = min((int)c.s1, excessFlow)) > 0) & (height - heightL[D1] == 1))
            {
                *((__local uchar*)(capacity1L     ) + 1)  = c.s1 - t;
                *((__local uchar*)(capacity2L + D1) + 1) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D1, t);
                localDone = 0;
            }
            if (((t = min((int)c.s5, excessFlow)) > 0) & (height - heightL[D4] == 1))
            {
                *((__local uchar*)(capacity2L     ) + 1)  = c.s5 - t;
                *((__local uchar*)(capacity1L + D4) + 1) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D4, t);
                localDone = 0;
            }
            if (((t = min((int)c.s2, excessFlow)) > 0) & (height - heightL[D2] == 1))
            {
                *((__local uchar*)(capacity1L     ) + 2)  = c.s2 - t;
                *((__local uchar*)(capacity2L + D2) + 0) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D2, t);
                localDone = 0;
            }
            if (((t = min((int)c.s4, excessFlow)) > 0) & (height - heightL[D3] == 1))
            {
                *((__local uchar*)(capacity2L     ) + 0)  = c.s4 - t;
                *((__local uchar*)(capacity1L + D3) + 2) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D3, t);
                localDone = 0;
            }
        }
        barrier(CLK_LOCAL_MEM_FENCE);

        if (actt & parity)
        {
            excessFlow = *excessFlowL;
            int t;
            const uchar8 c = (uchar8)(*capacity1L, *capacity2L);
            if (((t = min((int)c.s0, excessFlow)) > 0) & (height - heightL[D0] == 1))
            {
                *((__local uchar*)(capacity1L     ) + 0)  = c.s0 - t;
                *((__local uchar*)(capacity2L + D0) + 2) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D0, t);
                localDone = 0;
            }
            if (((t = min((int)c.s6, excessFlow)) > 0) & (height - heightL[D5] == 1))
            {
                *((__local uchar*)(capacity2L     ) + 2)  = c.s6 - t;
                *((__local uchar*)(capacity1L + D5) + 0) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D5, t);
                localDone = 0;
            }
            if (((t = min((int)c.s1, excessFlow)) > 0) & (height - heightL[D1] == 1))
            {
                *((__local uchar*)(capacity1L     ) + 1)  = c.s1 - t;
                *((__local uchar*)(capacity2L + D1) + 1) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D1, t);
                localDone = 0;
            }
            if (((t = min((int)c.s5, excessFlow)) > 0) & (height - heightL[D4] == 1))
            {
                *((__local uchar*)(capacity2L     ) + 1)  = c.s5 - t;
                *((__local uchar*)(capacity1L + D4) + 1) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D4, t);
                localDone = 0;
            }
            if (((t = min((int)c.s2, excessFlow)) > 0) & (height - heightL[D2] == 1))
            {
                *((__local uchar*)(capacity1L     ) + 2)  = c.s2 - t;
                *((__local uchar*)(capacity2L + D2) + 0) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D2, t);
                localDone = 0;
            }
            if (((t = min((int)c.s4, excessFlow)) > 0) & (height - heightL[D3] == 1))
            {
                *((__local uchar*)(capacity2L     ) + 0)  = c.s4 - t;
                *((__local uchar*)(capacity1L + D3) + 2) += t;
                *excessFlowL = excessFlow = excessFlow - t;
                atomic_add(excessFlowL + D3, t);
                localDone = 0;
            }
        }
        barrier(CLK_LOCAL_MEM_FENCE);
    }
    
    if (act)
    {
        int f;
        if ((lid.x == cl_block_3d_x - 1) & ((f = excessFlowL[D0]) > 0))
            { atomic_add(excessFlowG + 1, f);            *((__global uchar*)(capacity2G + 1) + 2) += f; }
        if ((lid.x == 0                ) & ((f = excessFlowL[D5]) > 0))
            { atomic_add(excessFlowG - 1, f);            *((__global uchar*)(capacity1G - 1) + 0) += f; }
        if ((lid.y == cl_block_3d_y - 1) & ((f = excessFlowL[D1]) > 0))
            { atomic_add(excessFlowG + volumeSize.x, f); *((__global uchar*)(capacity2G + volumeSize.x) + 1) += f; }
        if ((lid.y == 0                ) & ((f = excessFlowL[D4]) > 0))
            { atomic_add(excessFlowG - volumeSize.x, f); *((__global uchar*)(capacity1G - volumeSize.x) + 1) += f; }
        if ((lid.z == cl_block_3d_z - 1) & ((f = excessFlowL[D2]) > 0))
            { atomic_add(excessFlowG + offset, f);       *((__global uchar*)(capacity2G + offset) + 0) += f; }
        if ((lid.z == 0                ) & ((f = excessFlowL[D3]) > 0))
            { atomic_add(excessFlowG - offset, f);       *((__global uchar*)(capacity1G - offset) + 2) += f; }
        
        const uchar4 c1 = *capacity1L;
        const uchar4 c2 = *capacity2L;
        if ((excessFlow = *excessFlowL) != oldExcessFlow) *excessFlowG = excessFlow;
        if (height != oldHeight) *heightG = height;
        if (*((uint*)&c1) != *((uint*)&oldCapacity1)) *capacity1G  = c1;
        if (*((uint*)&c2) != *((uint*)&oldCapacity2)) *capacity2G  = c2;
    }
}

#endif
