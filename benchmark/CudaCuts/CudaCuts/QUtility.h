/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QUtility.h
 * @brief   QUtility class definition.
 * 
 * This file defines a utility class which contains serveral commonly used methods.
 * These methods can be devided into three groups:
 *     a group for checking errors, 
 *     a group for printing debug information,
 *     and a group for data preprocessing.
 * 
 * @version 1.0
 * @author  Jackie Pang, Wen-Shan Zhou
 * @e-mail  15pengyi@gmail.com
 * @date    2012/02/07
 */

#ifndef QUTILITY_H
#define QUTILITY_H

#include <cl/cl.h>

#include <vector>
#include <iostream>

#if defined(__APPLE__) || defined(MACOSX)
    #define GL_SHARING_EXTENSION "cl_APPLE_gl_sharing"
#else
    #define GL_SHARING_EXTENSION "cl_khr_gl_sharing"
#endif

#if defined(max)
    #undef max
#endif

#if defined(min)
    #undef min
#endif

class QUtility
{
public:
    QUtility();
    ~QUtility();
    
    static void trim(std::string &s);
    static ::size_t ceil(::size_t local_size, ::size_t global_size);
};

#endif  //QUTILITY_H