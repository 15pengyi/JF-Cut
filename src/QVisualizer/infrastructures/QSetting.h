/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QSetting.h
 * @brief   QSetting class definition.
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
 * @date    2012/03/19
 */

#ifndef QSETTING_H
#define QSETTING_H

#include <vector>

#include <gl/glew.h>

#include <glm.hpp>

#include "QStructure.h"

class QSetting
{
public:
    QSetting();
    ~QSetting();
    
    static GLuint sizeTransferFunction1D;
    static GLuint sizePreIntegration, sizeHistogram, sizeMapping;

    std::vector<glm::vec4> bufferTransferFunction1D;

    glm::vec3 lightDirection;
    glm::vec4 lightAmbient, lightDiffuse, lightSpecular;
    glm::vec4 materialAmbient, materialDiffuse, materialSpecular;
    GLfloat   materialShininess;

    bool enableLoggingFPS, enableLoggingTimeCost;

    GLuint bufferSizeVolume, bufferSizeFeature, bufferSizeVertex, bufferSizeDebug;
    GLuint currentStep;
};

#endif  // QSETTING_H