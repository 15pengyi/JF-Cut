/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QStructure.h
 * @brief   glm::vec3 class, glm::vec4 class definition.
 * 
 * This file defines the data strctures commonly used in geometry processing.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2012/02/07
 */

#ifndef QSTRUCTURE_H
#define QSTRUCTURE_H

#ifndef M_PI
    #define M_PI       3.14159265358979323846
    #define M_PI_2     1.57079632679489661923
#endif

enum QMouseMode
{
    MOUSE_UNKNOW    = 0,
    MOUSE_ROTATE    = 1,
    MOUSE_TRANSLATE = 2,
    MOUSE_DOLLY     = 3
};

enum QDataFormat
{
    FORMAT_UNKNOWN  = 0,
    FORMAT_CHAR     = 1,
    FORMAT_UCHAR    = 2,
    FORMAT_SHORT    = 3,
    FORMAT_USHORT   = 4,
    FORMAT_INT      = 5,
    FORMAT_UINT     = 6,
    FORMAT_FLOAT    = 7,
    FORMAT_DOUBLE   = 8
};

enum QDataType
{
    TYPE_UNKNOWN    = 0,
    TYPE_SCALAR     = 1,
    TYPE_VECTOR     = 2,
    TYPE_TENSOR     = 3
};

enum QEndianness
{
    ENDIAN_BIG      = 0,
    ENDIAN_LITTLE   = 1
};

#endif  // QSTRUCTURE_H