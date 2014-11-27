/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QUtilityUI.h
 * @brief   QUtilityUI class definition.
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

#ifndef QUTILITYUI_H
#define QUTILITYUI_H

#include <glm.hpp>

#include <QLinearGradient>

class QHoverPoints;

class QUtilityUI
{
public:
    QUtilityUI();
    ~QUtilityUI();
    
    static glm::vec4 getColor(const QString& rgb, unsigned char alpha = 255);
    
    static void generateLinearGradient(QLinearGradient &linearGradient, int width, QHoverPoints* hoverPoints, float alpha);
    static void generateCubicGradient(QLinearGradient &linearGradient, int width, QHoverPoints* hoverPoints, int gradientSize, const std::vector<float>& positions, float alpha);

    static void loadWidget(const std::string& filePath, QWidget* widget);
    static void saveWidget(const std::string& filePath, QWidget* widget);
};

template <typename T>
class QUtilityUITemplate
{
public:
    QUtilityUITemplate();
    ~QUtilityUITemplate();

    // http://en.wikipedia.org/wiki/Cubic_function
    // http://www.moshplant.com/direct-or/bezier/math.html
    static T cubicTo(float ratio, T endPoint1, T endPoint2)
    {
        float p = 0.5f * ratio - 0.25f;
        float q = std::sqrt(p * p + 0.015625f);
        float t = 0.5f + (p >= q ? std::pow(p - q, 0.3333333f) : -std::pow(q - p, 0.3333333f)) + std::pow(p + q, 0.3333333f);
        return endPoint1 + (endPoint2 - endPoint1) * (3 * ratio - 2 * t);
    }
};

#endif // QUTILITYUI_H