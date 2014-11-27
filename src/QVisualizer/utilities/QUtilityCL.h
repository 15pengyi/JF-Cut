/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QUtilityCL.h
 * @brief   QUtilityCL class definition.
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

#ifndef QUTILITYCL_H
#define QUTILITYCL_H

#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "../3rdParty/cl/cl_stacktrace.hpp"

#if defined(__APPLE__) || defined(MACOSX)
    #define GL_SHARING_EXTENSION "cl_APPLE_gl_sharing"
#else
    #define GL_SHARING_EXTENSION "cl_khr_gl_sharing"
#endif

class QUtilityCL
{
public:
    QUtilityCL();
    ~QUtilityCL();
    
    static ::size_t ceil(::cl_uint localSize, ::cl_uint globalSize);
    static std::vector<::size_t> ceil(const std::vector<::size_t>& localSize, const cl_uint& textureSize);
    static std::vector<::size_t> ceil(const std::vector<::size_t>& localSize, const cl_uint2& textureSize);
    static std::vector<::size_t> ceil(const std::vector<::size_t>& localSize, const cl_uint4& textureSize);
    static cl::NDRange ceil(const cl::NDRange& localSize, cl_uint textureSize);
    static cl::NDRange ceil(const cl::NDRange& localSize, const cl_uint4& textureSize);
    
    static bool checkCLStatus(const char *file, int line, cl_int status, const char *name);
    
    static void getCachedProgram(const cl::Context &context, const cl::Device &device, cl::Program& program,
        const std::string& path, const std::list<std::string>& files,
        const std::string& options = std::string(), const std::string& header = std::string());

    static cl_ulong getElapsedTime(std::vector<cl::Event>& events, const cl::CommandQueue& queue);
    
    static std::vector<::size_t> getLocalSize(const cl_uint4& localSize);
    static std::vector<::size_t> getGlobalSize(std::vector<::size_t>& localSize, const cl_uint4& textureSize);
    static cl::NDRange getGlobalSize(const cl::NDRange& localSize, const cl_uint4& textureSize);
};

#endif  // QUTILITYCL_H