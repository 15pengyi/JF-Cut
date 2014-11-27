/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QGCSetting.h
 * @brief   QGCSetting class definition.
 * 
 * This file defines the most often used settings such as
 *     volume offset and volume scale(also known as window width and window level),
 *     geometry(translation and rotation),
 *     illumination parameters,
 *     and transfer functions.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/01/09
 */

#ifndef QGCSETTING_H
#define QGCSETTING_H

#include <gl/glew.h>

#include <gtc/matrix_transform.hpp>

#include "../3rdParty/cl/cl_stacktrace.hpp"
#include "../infrastructures/QSetting.h"

typedef struct
{
    cl_int      height;
    cl_int      excessFlow;
    cl_ushort   capacity[4];
} cl_node_2d;

typedef struct
{
    cl_int      height;
    cl_int      excessFlow;
    cl_uchar    capacity[8];
} cl_node_3d;

typedef struct
{
    cl_char         foreground;
    cl_char         background;
    cl_char         object;
    cl_char         tag;
} cl_cut;

class QGCSetting : public QSetting
{
public:
    QGCSetting();
    ~QGCSetting();
    
    glm::mat4 inverseMVPMatrix;

    static cl_uint sizeTexture, sizeCutHistogram, sizeDistHistogram, sizeFilter;

    static cl_uint4 cl_block_2d, cl_block_3d;
    static cl_uint  cl_local_size, cl_group_size_n, cl_group_size_a;
    static cl_int   cl_max_flow;
    static cl_int   cl_max_height;

    static glm::ivec4 cl_shift_2d;
    static glm::ivec4 cl_shift_3d;
    static glm::ivec2 cl_delta_2d[4];
    static glm::ivec3 cl_delta_3d[6];
    
    static std::string defCut;
    static std::string extDat, extNode, extCut;
    static std::string extExcessFlow, extCapacity1, extCapacity2;
    static std::string extMFI;
    static std::string extGradient, extCurvature;
    static std::string extColor;

    static float filterGaussian0[5];
    static float filterGaussian1[5];
    static float filterGaussian2[5];
};

#endif  // QFEATURESETTING
