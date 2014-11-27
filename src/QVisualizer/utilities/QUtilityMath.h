/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QUtilityMath.h
 * @brief   QUtilityMath class definition.
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
 * @date    2013/07/25
 */

#ifndef QUTILITYMATH_H
#define QUTILITYMATH_H

#include <glm.hpp>
#include <gtc/quaternion.hpp>

class QUtilityMath
{
public:
    QUtilityMath();
    ~QUtilityMath();
    
    static float epsilon;

    static void trim(std::string &s);

    static double smooth(int edge0, int edge1, int x);

    static glm::vec4 getAxisAngle(const glm::quat &q);
    
    static unsigned short dilate_tab2[256];
    static unsigned char  dilate_tab3[256];

    static unsigned int dilate_2(unsigned short x);
    static unsigned int dilate_3(unsigned short x);
    static unsigned int morton_ordering_2(const glm::uvec2 id);
    static unsigned int morton_ordering_3(const glm::uvec3 id);

    static void convolution_x(float *h_Dst, float *h_Src, float *h_Kernel, int imageW, int imageH, int imageD, int kernelR);
    static void convolution_y(float *h_Dst, float *h_Src, float *h_Kernel, int imageW, int imageH, int imageD, int kernelR);
    static void convolution_z(float *h_Dst, float *h_Src, float *h_Kernel, int imageW, int imageH, int imageD, int kernelR);
    static void convolution_3(float *h_Dst, float *h_Src, float *h_Kernel, int imageW, int imageH, int imageD, int kernelR);
};

#endif  // QUTILITYMATH_H