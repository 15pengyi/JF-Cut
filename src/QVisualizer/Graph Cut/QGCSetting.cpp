/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QGCSetting.cpp
 * @brief   QGCSetting class declaration.
 * 
 * This file declares the often used settings defined in QGCSetting.h.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/01/09
 */

#include "QGCSetting.h"

cl_uint QGCSetting::sizeTexture = 4;
cl_uint QGCSetting::sizeCutHistogram  = 256;
cl_uint QGCSetting::sizeDistHistogram = 1024;
cl_uint QGCSetting::sizeFilter = 5;

cl_uint QGCSetting::cl_local_size = 64;
cl_uint QGCSetting::cl_group_size_n = 1024;
cl_uint QGCSetting::cl_group_size_a = 256;

cl_uint4 QGCSetting::cl_block_2d = { 16, 16,  1,  1 };
cl_uint4 QGCSetting::cl_block_3d = {  8,  8,  4,  1 };

float QGCSetting::filterGaussian0[5] = { 0.16151f, 0.21802f, 0.24095f,  0.21802f,  0.16151f };
float QGCSetting::filterGaussian1[5] = { 0.14446f, 0.09750f, 0.00000f, -0.09750f, -0.14446f };
float QGCSetting::filterGaussian2[5] = { 0.03230f, 0.17441f, 0.24095f,  0.17441f,  0.03230f };

cl_int QGCSetting::cl_max_height = std::numeric_limits<short>::max();
cl_int QGCSetting::cl_max_flow = std::numeric_limits<short>::max();

std::string QGCSetting::defCut = "\n\
typedef struct\n\
{\n\
    char     foreground;\n\
    char     background;\n\
    char     object;\n\
    char     tag;\n\
} cl_cut;\n\
";

std::string QGCSetting::extDat = ".dat";
std::string QGCSetting::extCut = ".cut";
std::string QGCSetting::extCapacity1 = ".c1";
std::string QGCSetting::extCapacity2 = ".c2";
std::string QGCSetting::extExcessFlow = ".ef";
std::string QGCSetting::extMFI = ".mfi";
std::string QGCSetting::extNode = ".node";
std::string QGCSetting::extGradient = ".gradient";
std::string QGCSetting::extCurvature = ".curvature";
std::string QGCSetting::extGray = ".gray";
std::string QGCSetting::extColor = ".color";

glm::ivec4 QGCSetting::cl_shift_2d = glm::ivec4(0, 15,  0, (1 << 15) - 1);
glm::ivec4 QGCSetting::cl_shift_3d = glm::ivec4(0, 10, 20, (1 << 10) - 1);
glm::ivec2 QGCSetting::cl_delta_2d[4] = 
{
    glm::ivec2( 1,  0), // left -> right
    glm::ivec2( 0,  1), // top -> bottom
    glm::ivec2( 0, -1), // bottom -> top
    glm::ivec2(-1,  0)  // right -> left
};

glm::ivec3 QGCSetting::cl_delta_3d[6] = 
{
    glm::ivec3( 1,  0,  0), // left -> right
    glm::ivec3( 0,  1,  0), // top -> bottom
    glm::ivec3( 0,  0,  1), // front -> back
    glm::ivec3( 0,  0, -1), // back -> front
    glm::ivec3( 0, -1,  0), // bottom -> top
    glm::ivec3(-1,  0,  0)  // right -> left
};

QGCSetting::QGCSetting() : QSetting(),
    inverseMVPMatrix(1.0f)
{
    bufferSizeVolume = 512 * 1024 * 1024;
}

QGCSetting::~QGCSetting()
{}