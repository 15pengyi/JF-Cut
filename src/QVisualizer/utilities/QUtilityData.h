/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QUtilityData.h
 * @brief   QUtilityData class definition.
 * 
 * This file defines a utility class which contains serveral commonly used methods.
 * These methods can be devided into three groups:
 *     a group for checking errors, 
 *     a group for printing debug information,
 *     and a group for data preprocessing.
 * 
 * @version 1.1
 * @author  Jackie Pang, Wen-Shan Zhou
 * @e-mail  15pengyi@gmail.com
 * @date    2012/02/07, 2013/07/25
 */

#ifndef QUTILITY_H
#define QUTILITY_H

#include <glm.hpp>

#include "../3rdParty/cl/cl_stacktrace.hpp"
#include "../infrastructures/QStructure.h"

#ifdef max
	#undef max
#endif

#ifdef min
	#undef min
#endif

class QHoverPoints;

class QUtilityData
{
public:
    QUtilityData();
    ~QUtilityData();
    
    static void preprocess(void* volumeData, const ::size_t& volumeSize, const QDataFormat& format,
        const QEndianness& endian, const ::size_t& histogramSize, float* histogramData,
        float& volumeMin, float& volumeMax, float& histogramMin, float& histogramMax);
    static void simplify(void* source, void* destination, cl_uint4&  volumeSize, const QDataFormat& format,
        const QEndianness& endian, const cl_uint4& volumeScale, float &volumeMax, float &volumeMin);
    static void clamp(void* volumeData, const cl_uint4& volumeSize, const QDataFormat& format,
        const double &volumeMin, const double &volumeMax);
    
    static void computePartitionPositions(QHoverPoints* hoverPoints, int width, std::vector<float>& positions, ::size_t partitionSize, float* partitionData);
    static void computeHistogramPositions(int histogramSize, int width, std::vector<float>& positions, ::size_t partitionSize, float* partitionData);

    static void saveGrayImage(const std::string& fileName, const glm::uvec2& scale = glm::uvec2(1, 1));
    static void saveColorImage(const std::string& fileName, const glm::uvec2& scale = glm::uvec2(1, 1));
    static void saveImageLabels(const std::string& fileName);
};

template <typename T>
class QUtilityDataTemplate
{
public:
    QUtilityDataTemplate();
    ~QUtilityDataTemplate();
    
    static void read(const std::string &content, int &count, void* start, const ::size_t& size)
    {
        char* buffer((char*)content.data() + count);
        T* end = (T*)start + size;
        if (TypeIsSame<T, char>::result::value || TypeIsSame<T, short>::result::value || TypeIsSame<T, int>::result::value || TypeIsSame<T, long>::result::value)
        {
            for (T* i = (T*)start; i != end; i++)
                *i = strtol(buffer, &buffer, 10);
        }
        else if (TypeIsSame<T, unsigned char>::result::value || TypeIsSame<T, unsigned short>::result::value || TypeIsSame<T, unsigned int>::result::value || TypeIsSame<T, unsigned long>::result::value)
        {
            for (T* i = (T*)start; i != end; i++)
                *i = strtoul(buffer, &buffer, 10);
        }
        else if (TypeIsSame<T, float>::result::value || TypeIsSame<T, double>::result::value)
        {
            for (T* i = (T*)start; i != end; i++)
                *i = strtod(buffer, &buffer);
        }
        count = buffer - (char*)content.data();
    }
    
    static void read(std::istream& stream, void* start, const ::size_t& size)
    {
        T* end = (T*)start + size;
        for (T* i = (T*)start; i != end; i++)
            stream >> *i;
    }
    
    static void convert(void* source, float* destination, const ::size_t& size, const ::size_t& stride)
    {
        T* end = (T*)source + size * 3;
        for (T* i = (T*)source; i != end; i += 3)
        {
            destination[0] = (float)i[0];
            destination[1] = (float)i[1];
            destination[2] = (float)i[2];
            destination += stride;
        }
    }

    static void log(const ::size_t& histogramSize, T* histogramData)
    {
        T histogramMin(0.0f), histogramMax(0.0f);
        log(histogramSize, histogramData, histogramMin, histogramMax);
    }

    static void log(const ::size_t& histogramSize, T* histogramData, T& histogramMin, T& histogramMax)
    {
        histogramMin = std::numeric_limits<float>::max();
        histogramMax = 0.0f;
        T* histogramBegin = histogramData;
        T* histogramEnd = histogramBegin + histogramSize;
        const T logScale = 1.0f / std::log(2.0f);
        for (T *i = histogramBegin; i != histogramEnd; i++)
        {
            T t = *i = std::log(*i + 1.0f) * logScale;
            if (t < histogramMin) histogramMin = t;
            if (t > histogramMax) histogramMax = t;
        }

        T histogramScale = histogramMax - histogramMin < QUtilityMath::epsilon ? 1.0f : 1.0f / (histogramMax - histogramMin);
        for (T *i = histogramBegin; i != histogramEnd; i++)
            *i = (*i - histogramMin) * histogramScale;
    }
    
    static void log(const ::size_t& histogramSize, T* histogramData, T& histogramMin, T& histogramMax, int timeStep)
    {
        histogramMin = std::numeric_limits<float>::max();
        histogramMax = 0.0f; 
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < timeStep; j++)
            {
                T* histogramBegin = histogramData + histogramSize * j + histogramSize * timeStep * i;
                T* histogramEnd = histogramBegin + histogramSize;
                const T logScale = 1.0f / std::log(2.0f);
                for (T *i = histogramBegin; i != histogramEnd; i++)
                {
                    T t = *i = std::log(*i + 1.0f) * logScale;
                    if (t < histogramMin) histogramMin = t;
                    if (t > histogramMax) histogramMax = t;
                }
            }
        }

        T histogramScale = histogramMax - histogramMin < QUtilityMath::epsilon ? 1.0f : 1.0f / (histogramMax - histogramMin);
        for (int i = 0; i < 4 ;i++)
        {
            for (int j = 0; j < timeStep; j++)
            {
                T* histogramBegin = histogramData + histogramSize * j + histogramSize * timeStep * i;
                T* histogramEnd = histogramBegin + histogramSize;
                for (T *i = histogramBegin; i != histogramEnd; i++)
                    *i = (*i - histogramMin) * histogramScale;
            }
        }
    }
    
    static void normalize(void* volumeData, const ::size_t& volumeSize, const QEndianness& endian, float& volumeMin, float& volumeMax)
    {
        T* begin = (T*)volumeData;
        T* end = begin + volumeSize;

        if (endian == ENDIAN_BIG)
        {
            for (T* i = begin; i != end; i++)
            {
                unsigned char* head = (unsigned char*)i;
                unsigned char* tail = head + sizeof(T) - 1;
                while (head < tail)
                {
                    unsigned char t = *head;
                    *(head++) = *tail;
                    *(tail--) = t;
                }
            }
        }

        volumeMin = std::numeric_limits<float>::max(), volumeMax = std::numeric_limits<float>::lowest();
        for (T* i = begin; i != end; i++)
        {
            float t = *i;
            if (t < volumeMin) volumeMin = t;
            if (t > volumeMax) volumeMax = t;
        }

        float scale = volumeMax - volumeMin < QUtilityMath::epsilon ? 1.0f : 1.0f / (volumeMax - volumeMin);
        float *destination = (float *)volumeData + volumeSize;
        for (T *source = end; source != begin; )
            *(--destination) = (*(--source) - volumeMin) * scale;
    }

    static void gather(void* volumeData, const ::size_t& volumeSize, const QEndianness& endian, const int dimension)
    {
        T* begin = (T*)volumeData;
        T* end = begin + volumeSize * dimension;

        if (endian == ENDIAN_BIG)
        {
            for (T* i = begin; i != end; i++)
            {
                unsigned char* head = (unsigned char*)i;
                unsigned char* tail = head + sizeof(T) - 1;
                while (head < tail)
                {
                    unsigned char t = *head;
                    *(head++) = *tail;
                    *(tail--) = t;
                }
            }
        }

        T* i = begin;
        for (T* j = begin; j != end; j += dimension, i++)
        {
            T* jEnd = j + dimension;
            for (T* k = j; k != jEnd; k++)
            {
                T v = *k;
                *k = 0;
                *i += v * v;
            }
            *i = ::sqrtf(*i);
        }
    }

    static void simplify(void* source, void* destination, const cl_uint4& volumeSize, const QEndianness& endian, const cl_uint4& volumeScale, float &volumeMax, float &volumeMin)
    {
        T* begin = (T*)source;
        T* end = begin + volumeSize.s[0] * volumeSize.s[1] * volumeSize.s[2];

        if (endian == ENDIAN_BIG)
        {
            for (T* i = begin; i != end; i++)
            {
                unsigned char* head = (unsigned char*)i;
                unsigned char* tail = head + sizeof(T) - 1;
                while (head < tail)
                {
                    unsigned char t = *head;
                    *(head++) = *tail;
                    *(tail--) = t;
                }
            }
        }

        double scale = 1.0f / (volumeScale.s[0] * volumeScale.s[1] * volumeScale.s[2]);
        cl_uint4 volumeOffset = { 1, volumeSize.s[0], volumeSize.s[0] * volumeSize.s[1], 0 };

        float* dst = (float*)destination;
        T* src = (T*)source;
        for(int z = 0; z < volumeSize.s[2]; z += volumeScale.s[2])
            for(int y = 0; y < volumeSize.s[1]; y += volumeScale.s[1])
                for (int x = 0; x < volumeSize.s[0]; x += volumeScale.s[0])
                {
                    double v = 0.0f;
                    for (int dz = 0; dz < volumeScale.s[2]; ++dz)
                        for (int dy = 0; dy < volumeScale.s[1]; ++dy)
                            for (int dx = 0; dx < volumeScale.s[0]; ++dx)
                            {
                                float d = *(src
                                    + std::min<int>(x + dx, volumeSize.s[0] - 1)
                                    + std::min<int>(y + dy, volumeSize.s[1] - 1) * volumeOffset.s[1]
                                    + std::min<int>(z + dz, volumeSize.s[2] - 1) * volumeOffset.s[2]);
                                volumeMin = std::min<float>(volumeMin, d);
                                volumeMax = std::max<float>(volumeMax, d);
                                v += d;
                            };
                    *(dst++) = v * scale;
                };
    }
    
    static void clamp(void* volumeData, const cl_uint4& volumeSize, const T &volumeMin, const T &volumeMax)
    {
        unsigned int x, y, z;
        x = volumeSize.s[0];
        y = volumeSize.s[1];
        z = volumeSize.s[2];
        
        T* begin = (T*)volumeData;
        T* end = begin + x * y * z;
        for (T* i = begin; i != end; i++)
            *i = std::min<T>(std::max<T>(*i, volumeMin), volumeMax);
    }
};

#endif  // QUTILITY_H