/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QUtilityGL.h
 * @brief   QUtilityGL class definition.
 * 
 * This file defines a utility class which contains serveral commonly used methods.
 * These methods can be devided into three groups:
 *     a group for checking errors, 
 *     a group for printing debug information,
 *     and a group for data preprocessing.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/07/25
 */

#ifndef QUTILITYGL_H
#define QUTILITYGL_H

#include <gl/glew.h>

class QUtilityGL
{
public:
    QUtilityGL();
    ~QUtilityGL();
    
    static bool checkSupport();
    static bool checkGlewSupport();
    static bool checkOpenGLSupport();
    static bool checkGLStatus(char *file, int line, char *name);
    static bool checkShaderStatus(char *file, int line, unsigned int shader, GLenum name);
    static bool checkProgramStatus(char *file, int line, unsigned int program, GLenum name);
    static bool checkBufferStatus(int number);
    static bool checkFramebufferStatus(unsigned int target);
    static bool checkShaderSupport();
    static bool checkArguments(int argc, char *argv[]);

    static unsigned int getSize(unsigned int target);
};

#endif  // QUTILITYGL_H