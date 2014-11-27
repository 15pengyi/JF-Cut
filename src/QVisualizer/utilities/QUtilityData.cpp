/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QUtilityData.cpp
 * @brief   QUtilityData class declaration.
 * 
 * This file declares the most commonly used methods defined in QUtilityData.h.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2012/02/07, 2013/07/25
 */

#include <limits>

#include "../infrastructures/QHoverPoints.h"
#include "../Graph Cut/QGCSetting.h"
#include "QIO.h"
#include "QUtilityMath.h"
#include "QUtilityData.h"

QUtilityData::QUtilityData()
{}

QUtilityData::~QUtilityData()
{}

void QUtilityData::preprocess(void* volumeData, const ::size_t& volumeSize, const QDataFormat& format,
    const QEndianness& endian, const ::size_t& histogramSize, float* histogramData,
    float& volumeMin, float& volumeMax, float& histogramMin, float& histogramMax)
{
    switch (format)
    {
    case FORMAT_CHAR:
        QUtilityDataTemplate<char>::normalize(volumeData, volumeSize, endian, volumeMin, volumeMax);
        break;
    case FORMAT_UCHAR:
        QUtilityDataTemplate<unsigned char>::normalize(volumeData, volumeSize, endian, volumeMin, volumeMax);
        break;
    case FORMAT_SHORT:
        QUtilityDataTemplate<short>::normalize(volumeData, volumeSize, endian, volumeMin, volumeMax);
        break;
    case FORMAT_USHORT:
        QUtilityDataTemplate<unsigned short>::normalize(volumeData, volumeSize, endian, volumeMin, volumeMax);
        break;
    case FORMAT_INT:
        QUtilityDataTemplate<int>::normalize(volumeData, volumeSize, endian, volumeMin, volumeMax);
        break;
    case FORMAT_UINT:
        QUtilityDataTemplate<unsigned int>::normalize(volumeData, volumeSize, endian, volumeMin, volumeMax);
        break;
    case FORMAT_FLOAT:
        QUtilityDataTemplate<float>::normalize(volumeData, volumeSize, endian, volumeMin, volumeMax);
        break;
    default:
        break;
    }

    if (histogramSize > 0)
    {
        float level = histogramSize - QUtilityMath::epsilon;
        float* volumeBegin = (float*)volumeData;
        float* volumeEnd = volumeBegin + volumeSize;
        for (float *i = volumeBegin; i != volumeEnd; i++)
            histogramData[(int)(*i * level)]++;

        QUtilityDataTemplate<float>::log(histogramSize, histogramData, histogramMin, histogramMax);
    }
}

void  QUtilityData::simplify(void* source, void* destination, cl_uint4&  volumeSize, const QDataFormat& format,
    const QEndianness& endian, const cl_uint4& volumeScale, float &volumeMax, float &volumeMin)
{
    switch (format)
    {
    case FORMAT_CHAR:
        QUtilityDataTemplate<char>::simplify(source, destination, volumeSize, endian, volumeScale, volumeMax, volumeMin);
        break;
    case FORMAT_UCHAR:
        QUtilityDataTemplate<unsigned char>::simplify(source, destination, volumeSize, endian, volumeScale, volumeMax, volumeMin);
        break;
    case FORMAT_SHORT:
        QUtilityDataTemplate<short>::simplify(source, destination, volumeSize, endian, volumeScale, volumeMax, volumeMin);
        break;
    case FORMAT_USHORT:
        QUtilityDataTemplate<unsigned short>::simplify(source, destination,volumeSize, endian, volumeScale, volumeMax, volumeMin);
        break;
    case FORMAT_INT:
        QUtilityDataTemplate<int>::simplify(source, destination, volumeSize, endian, volumeScale, volumeMax, volumeMin);
        break;
    case FORMAT_UINT:
        QUtilityDataTemplate<unsigned int>::simplify(source, destination, volumeSize, endian, volumeScale, volumeMax, volumeMin);
        break;
    case FORMAT_FLOAT:
        QUtilityDataTemplate<float>::simplify(source, destination, volumeSize, endian, volumeScale, volumeMax, volumeMin);
        break;
    default:
        break;
    }
}

void QUtilityData::clamp(void* volumeData, const cl_uint4& volumeSize, const QDataFormat& format,
    const double &volumeMin, const double &volumeMax)
{
    switch (format)
    {
    case FORMAT_CHAR:
        QUtilityDataTemplate<char>::clamp(volumeData,volumeSize, volumeMin, volumeMax);
        break;
    case FORMAT_UCHAR:
        QUtilityDataTemplate<unsigned char>::clamp(volumeData, volumeSize, volumeMin, volumeMax);
        break;
    case FORMAT_SHORT:
        QUtilityDataTemplate<short>::clamp(volumeData, volumeSize, volumeMin, volumeMax);
        break;
    case FORMAT_USHORT:
        QUtilityDataTemplate<unsigned short>::clamp(volumeData,volumeSize, volumeMin, volumeMax);
        break;
    case FORMAT_INT:
        QUtilityDataTemplate<int>::clamp(volumeData,volumeSize, volumeMin, volumeMax);
        break;
    case FORMAT_UINT:
        QUtilityDataTemplate<unsigned int>::clamp(volumeData, volumeSize, volumeMin, volumeMax);
        break;
    case FORMAT_FLOAT:
        QUtilityDataTemplate<float>::clamp(volumeData, volumeSize, volumeMin, volumeMax);
        break;
    default:
        break;
    }
}

void QUtilityData::computePartitionPositions(QHoverPoints* hoverPoints, int width, std::vector<float>& positions, ::size_t partitionSize, float* partitionData)
{
    const QPolygonF& points = hoverPoints->points();
    if (!partitionData)
    {
        for (QVector<QPointF>::const_iterator i = points.begin(); i != points.end(); i++)
            positions.push_back(i->x() / width);
    }
    else
    {
        for (QVector<QPointF>::const_iterator i = points.begin(); i != points.end(); i++)
        {
            float position = i->x() * (partitionSize - 1) / width;
            int index = (int)position;
            float ratio = position - index;
            positions.push_back(index == partitionSize - 1 ? partitionData[index] : partitionData[index] * (1.0f - ratio) + ratio * partitionData[index + 1]);
        }
    }
}

void QUtilityData::computeHistogramPositions(int histogramSize, int width, std::vector<float>& positions, ::size_t partitionSize, float* partitionData)
{
    if (partitionData)
    {
        int index(0);
        for(int i = 0; i < histogramSize; i++)
        {
            float x = (float)i / (histogramSize - 1);
            while (partitionData[index + 1] < x) index++;
            qreal ratio = partitionData[index + 1] == partitionData[index] ? 0.0f : (x - partitionData[index]) / (partitionData[index + 1] - partitionData[index]);
            positions.push_back(width * (index + ratio) / partitionSize);
        }
    }
    else
    {
        for(int i = 0; i < histogramSize; i++)
        {
            float x = (float)i / (histogramSize - 1);
            positions.push_back(width * x);
        }
    }
}

void QUtilityData::saveGrayImage(const std::string& fileName, const glm::uvec2& scale)
{
    QImage source(fileName.c_str());
    source = source.scaled(source.width() / scale.x, source.height() / scale.y);
    int width = source.width();
    int height = source.height();

    std::vector<cl_uchar> destination(width * height);
    cl_uchar* ptrDestination = destination.data();
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            *(ptrDestination++) = qGray(source.pixel(x, y));

    QIO::saveFileData(fileName + QGCSetting::extGray, destination.data(), destination.size() * sizeof(cl_uchar));
}

void QUtilityData::saveColorImage(const std::string& fileName, const glm::uvec2& scale)
{
    QImage source(fileName.c_str());
    source = source.scaled(source.width() / scale.x, source.height() / scale.y);
    int width = source.width();
    int height = source.height();

    std::vector<cl_uchar4> destination(width * height);
    cl_uchar4* ptrDestination = destination.data();
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            QRgb label = source.pixel(x, y);
            ptrDestination->s[0] = qRed(label);
            ptrDestination->s[1] = qGreen(label);
            ptrDestination->s[2] = qBlue(label);
            ptrDestination->s[3] = qAlpha(label);
            ptrDestination++;
        };

    QIO::saveFileData(fileName + QGCSetting::extColor, destination.data(), destination.size() * sizeof(cl_uchar4));
}

void QUtilityData::saveImageLabels(const std::string& fileName)
{
    typedef struct
    {
        char     foreground;
        char     background;
        char     object;
        char     tag;
    } cl_cut;
    
    QRgb foreground = QColor(Qt::red).rgba();
    QRgb background = QColor(Qt::blue).rgba();
    QImage source(fileName.c_str());
    int width = source.width();
    int height = source.height();

    std::vector<cl_cut> destination(width * height);
    cl_cut* ptrDestination = destination.data();
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            QRgb label = source.pixel(x, y);
            if (label == foreground)
                ptrDestination->foreground = std::numeric_limits<char>::max();
            else if (label == background)
                ptrDestination->background = std::numeric_limits<char>::max();
            ptrDestination++;
        };

    QIO::saveFileData(fileName + ".cut", destination.data(), destination.size() * sizeof(cl_cut));
}