/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    Qsettings.cpp
 * @brief   QSetting class declaration.
 * 
 * This file declares the often used settings defined in QSetting.h.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2012/03/19
 */

#include <limits>

#include "QSetting.h"

GLuint QSetting::sizeTransferFunction1D = 256;
GLuint QSetting::sizePreIntegration = 256;
GLuint QSetting::sizeHistogram = 256;
GLuint QSetting::sizeMapping = 64;

QSetting::QSetting() :
    bufferTransferFunction1D(QSetting::sizeTransferFunction1D),
    lightDirection(1.0f),
    lightAmbient(1.0f, 1.0f, 1.0f, 1.0f), lightDiffuse(1.0f, 1.0f, 1.0f, 1.0f), lightSpecular(1.0f, 1.0f, 1.0f, 1.0f),
    materialAmbient(1.0f, 1.0f, 1.0f, 0.0f), materialDiffuse(1.0f, 1.0f, 1.0f, 0.0f), materialSpecular(1.0f, 1.0f, 1.0f, 0.0f),
    materialShininess(0.0f),
    enableLoggingFPS(true), enableLoggingTimeCost(true),
    bufferSizeVolume(0), bufferSizeFeature(0), bufferSizeVertex(0), bufferSizeDebug(0),
    currentStep(0)
{}

QSetting::~QSetting()
{}