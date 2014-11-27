/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QUtilityCL.cpp
 * @brief   QUtilityCL class declaration.
 * 
 * This file declares the most commonly used methods defined in QUtilityCL.h.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/07/25
 */

#include <sstream>

#include "../infrastructures/QError.h"
#include "QUtilityCL.h"
#include "QIO.h"

QUtilityCL::QUtilityCL()
{}

QUtilityCL::~QUtilityCL()
{}

::size_t QUtilityCL::ceil(cl_uint localSize, cl_uint globalSize) 
{
    cl_uint r = globalSize % localSize;
    return r == 0 ? globalSize : globalSize + localSize - r;
}

std::vector<::size_t> QUtilityCL::ceil(const std::vector<::size_t>& localSize, const cl_uint& textureSize)
{
    std::vector<::size_t> globalSize(localSize.size());
    for (int i = 0; i < localSize.size(); i++)
        globalSize[i] = ceil(localSize[i], textureSize);
    return globalSize;
}

std::vector<::size_t> QUtilityCL::ceil(const std::vector<::size_t>& localSize, const cl_uint2& textureSize)
{
    cl_uint4 size = { textureSize.s[0], textureSize.s[1], 0, 0 };
    return ceil(localSize, size);
}

std::vector<::size_t> QUtilityCL::ceil(const std::vector<::size_t>& localSize, const cl_uint4& textureSize)
{
    std::vector<::size_t> globalSize(localSize.size());
    for (int i = 0; i < localSize.size(); i++)
        globalSize[i] = ceil(localSize[i], textureSize.s[i]);
    return globalSize;
}

cl::NDRange QUtilityCL::ceil(const cl::NDRange& localSize, cl_uint textureSize)
{
    if (localSize.dimensions() == 1)
        return cl::NDRange(
        ceil(localSize[0], textureSize));
    else if (localSize.dimensions() == 2)
        return cl::NDRange(
        ceil(localSize[0], textureSize),
        ceil(localSize[1], textureSize));
    else
        return cl::NDRange(
        ceil(localSize[0], textureSize),
        ceil(localSize[1], textureSize),
        ceil(localSize[2], textureSize));
}

cl::NDRange QUtilityCL::ceil(const cl::NDRange& localSize, const cl_uint4& textureSize)
{
    if (localSize.dimensions() == 1)
        return cl::NDRange(
            ceil(localSize[0], textureSize.s[0]));
    else if (localSize.dimensions() == 2)
        return cl::NDRange(
            ceil(localSize[0], textureSize.s[0]),
            ceil(localSize[1], textureSize.s[1]));
    else
        return cl::NDRange(
            ceil(localSize[0], textureSize.s[0]),
            ceil(localSize[1], textureSize.s[1]),
            ceil(localSize[2], textureSize.s[2]));
}

bool QUtilityCL::checkCLStatus(const char *file, int line, cl_int status, const char *name)
{
    if (status != CL_SUCCESS)
    {
        std::cerr << " > ERROR: " << file << "(" << line << ") " << name << " failed (";
        switch (status)
        {
        case CL_DEVICE_NOT_FOUND:
            std::cerr << status << ", CL_DEVICE_NOT_FOUND";
            break;
        case CL_DEVICE_NOT_AVAILABLE:
            std::cerr << status << ", CL_DEVICE_NOT_AVAILABLE";
            break;
        case CL_COMPILER_NOT_AVAILABLE:
            std::cerr << status << ", CL_COMPILER_NOT_AVAILABLE";
            break;
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:
            std::cerr << status << ", CL_MEM_OBJECT_ALLOCATION_FAILURE";
            break;
        case CL_OUT_OF_RESOURCES:
            std::cerr << status << ", CL_OUT_OF_RESOURCES";
            break;
        case CL_OUT_OF_HOST_MEMORY:
            std::cerr << status << ", CL_OUT_OF_HOST_MEMORY";
            break;
        case CL_PROFILING_INFO_NOT_AVAILABLE:
            std::cerr << status << ", CL_PROFILING_INFO_NOT_AVAILABLE";
            break;
        case CL_MEM_COPY_OVERLAP:
            std::cerr << status << ", CL_MEM_COPY_OVERLAP";
            break;
        case CL_IMAGE_FORMAT_MISMATCH:
            std::cerr << status << ", CL_IMAGE_FORMAT_MISMATCH";
            break;
        case CL_IMAGE_FORMAT_NOT_SUPPORTED:
            std::cerr << status << ", CL_IMAGE_FORMAT_NOT_SUPPORTED";
            break;
        case CL_BUILD_PROGRAM_FAILURE:
            std::cerr << status << ", CL_BUILD_PROGRAM_FAILURE";
            break;
        case CL_MAP_FAILURE:
            std::cerr << status << ", CL_MAP_FAILURE";
            break;
            /*
        case CL_MISALIGNED_SUB_BUFFER_OFFSET:
            std::cerr << status << ", CL_MISALIGNED_SUB_BUFFER_OFFSET";
            break;
        case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
            std::cerr << status << ", CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
            break;
            */
        case CL_INVALID_VALUE:
            std::cerr << status << ", CL_INVALID_VALUE";
            break;
        case CL_INVALID_DEVICE_TYPE:
            std::cerr << status << ", CL_INVALID_DEVICE_TYPE";
            break;
        case CL_INVALID_PLATFORM:
            std::cerr << status << ", CL_INVALID_PLATFORM";
            break;
        case CL_INVALID_DEVICE:
            std::cerr << status << ", CL_INVALID_DEVICE";
            break;
        case CL_INVALID_CONTEXT:
            std::cerr << status << ", CL_INVALID_CONTEXT";
            break;
        case CL_INVALID_QUEUE_PROPERTIES:
            std::cerr << status << ", CL_INVALID_QUEUE_PROPERTIES";
            break;
        case CL_INVALID_COMMAND_QUEUE:
            std::cerr << status << ", CL_INVALID_COMMAND_QUEUE";
            break;
        case CL_INVALID_HOST_PTR:
            std::cerr << status << ", CL_INVALID_HOST_PTR";
            break;
        case CL_INVALID_MEM_OBJECT:
            std::cerr << status << ", CL_INVALID_MEM_OBJECT";
            break;
        case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
            std::cerr << status << ", CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
            break;
        case CL_INVALID_IMAGE_SIZE:
            std::cerr << status << ", CL_INVALID_IMAGE_SIZE";
            break;
        case CL_INVALID_SAMPLER:
            std::cerr << status << ", CL_INVALID_SAMPLER";
            break;
        case CL_INVALID_BINARY:
            std::cerr << status << ", CL_INVALID_BINARY";
            break;
        case CL_INVALID_BUILD_OPTIONS:
            std::cerr << status << ", CL_INVALID_BUILD_OPTIONS";
            break;
        case CL_INVALID_PROGRAM:
            std::cerr << status << ", CL_INVALID_PROGRAM";
            break;
        case CL_INVALID_PROGRAM_EXECUTABLE:
            std::cerr << status << ", CL_INVALID_PROGRAM_EXECUTABLE";
            break;
        case CL_INVALID_KERNEL_NAME:
            std::cerr << status << ", CL_INVALID_KERNEL_NAME";
            break;
        case CL_INVALID_KERNEL_DEFINITION:
            std::cerr << status << ", CL_INVALID_KERNEL_DEFINITION";
            break;
        case CL_INVALID_KERNEL:
            std::cerr << status << ", CL_INVALID_KERNEL";
            break;
        case CL_INVALID_ARG_INDEX:
            std::cerr << status << ", CL_INVALID_ARG_INDEX";
            break;
        case CL_INVALID_ARG_VALUE:
            std::cerr << status << ", CL_INVALID_ARG_VALUE";
            break;
        case CL_INVALID_ARG_SIZE:
            std::cerr << status << ", CL_INVALID_ARG_SIZE";
            break;
        case CL_INVALID_KERNEL_ARGS:
            std::cerr << status << ", CL_INVALID_KERNEL_ARGS";
            break;
        case CL_INVALID_WORK_DIMENSION:
            std::cerr << status << ", CL_INVALID_WORK_DIMENSION";
            break;
        case CL_INVALID_WORK_GROUP_SIZE:
            std::cerr << status << ", CL_INVALID_WORK_GROUP_SIZE";
            break;
        case CL_INVALID_WORK_ITEM_SIZE:
            std::cerr << status << ", CL_INVALID_WORK_ITEM_SIZE";
            break;
        case CL_INVALID_GLOBAL_OFFSET:
            std::cerr << status << ", CL_INVALID_GLOBAL_OFFSET";
            break;
        case CL_INVALID_EVENT_WAIT_LIST:
            std::cerr << status << ", CL_INVALID_EVENT_WAIT_LIST";
            break;
        case CL_INVALID_EVENT:
            std::cerr << status << ", CL_INVALID_EVENT";
            break;
        case CL_INVALID_OPERATION:
            std::cerr << status << ", CL_INVALID_OPERATION";
            break;
        case CL_INVALID_GL_OBJECT:
            std::cerr << status << ", CL_INVALID_GL_OBJECT";
            break;
        case CL_INVALID_BUFFER_SIZE:
            std::cerr << status << ", CL_INVALID_BUFFER_SIZE";
            break;
        case CL_INVALID_MIP_LEVEL:
            std::cerr << status << ", CL_INVALID_MIP_LEVEL";
            break;
        case CL_INVALID_GLOBAL_WORK_SIZE:
            std::cerr << status << ", CL_INVALID_GLOBAL_WORK_SIZE";
            break;
        case CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR:
            std::cerr << status << ", CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
        }
        std::cerr << ")" << std::endl;
        return false;
    }
    return true;
}

void QUtilityCL::getCachedProgram(const cl::Context &context, const cl::Device &device, cl::Program& program,
    const std::string& path, const std::list<std::string>& files,
    const std::string& options, const std::string& header)
{
    if (files.empty())
        throw QError(2, Q_RUNTIME_ERROR, "no files.");

    std::list<std::string> sourcePool(1, header);
    cl::Program::Sources sources(1, std::make_pair(header.c_str(), header.length()));
    std::ostringstream sourceStream;
    sourceStream << sourcePool.begin()->c_str();
    for (auto i = files.begin(); i != files.end(); i++)
    {
        std::ifstream file(path + *i);
        sourcePool.push_front(std::string(std::istreambuf_iterator<char>(file), (std::istreambuf_iterator<char>())));
        sources.push_back(std::make_pair(sourcePool.begin()->c_str(), sourcePool.begin()->length()));
        sourceStream << sourcePool.begin()->c_str();
    }

    std::string source = sourceStream.str();
    if (source.empty())
        throw QError(2, Q_RUNTIME_ERROR, "file is empty.");

    std::ostringstream prefixStream;
    prefixStream << path << source.size() << '-' << options.size() << '-' << header.size();
    std::string prefix = prefixStream.str();

    long long size;
    cl_int compare;
    std::string cached;
    if (!QIO::getFileContent(prefix + ".ocl.tmp", cached) || 0 != (compare = source.compare(cached))
     || !QIO::getFileSize(prefix + ".bin.tmp", size))
    {
        try
        {
            program = cl::Program(context, sources);
            program.build(std::vector<cl::Device>(1, device), options.c_str());
            std::cout << " > BUILD: [ program ] " << program() << std::endl;
        }
        catch (cl::Error& e)
        {
            if (e.err() == CL_BUILD_PROGRAM_FAILURE)
            {
                std::string log = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
                std::string name = device.getInfo<CL_DEVICE_NAME>();
                std::cout << " > BUILD LOG: [ device " << name << " ] " << log << std::endl;
            }
            throw e;
        }

        std::vector<char*> binaries = program.getInfo<CL_PROGRAM_BINARIES>();
        std::vector<::size_t> sizes = program.getInfo<CL_PROGRAM_BINARY_SIZES>();
        if (!QIO::saveFileData(prefix + ".bin.tmp", binaries.front(), sizes.front()))
            throw QError(2, Q_RUNTIME_ERROR, "save binary file failed.");

        if (cached.empty() || compare != 0)
            if (!QIO::saveFileContent(prefix + ".ocl.tmp", source))
                throw QError(2, Q_RUNTIME_ERROR, "save text file failed.");

        while (!binaries.empty())
        {
            if (binaries.back()) delete[] binaries.back();
            binaries.pop_back();
        }
    }
    else
    {
        std::vector<char> binary(size);
        if (!QIO::getFileData(prefix + ".bin.tmp", binary.data(), size))
            throw QError(2, Q_RUNTIME_ERROR, "load binary file failed.");
        
        cl::Program::Binaries binaries;
        binaries.push_back(std::make_pair(binary.data(), binary.size()));
        try
        {
            program = cl::Program(context, std::vector<cl::Device>(1, device), binaries);
            program.build(std::vector<cl::Device>(1, device), options.c_str());
            std::cout << " > BUILD: [ program ] " << program() << std::endl;
        }
        catch (cl::Error& e)
        {
            if (e.err() == CL_BUILD_PROGRAM_FAILURE)
            {
                std::string log = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
                std::string name = device.getInfo<CL_DEVICE_NAME>();
                std::cout << " > BUILD LOG: [ device " << name << " ] " << log << std::endl;
            }
            throw e;
        }
    }
}

cl_ulong QUtilityCL::getElapsedTime(std::vector<cl::Event>& events, const cl::CommandQueue& queue)
{
	if (!queue()) return 0;
	queue.finish();
    cl_ulong nseconds(0);
    for (auto i = events.begin(); i != events.end(); i++)
        if ((*i)())
        {
            cl_ulong start = i->getProfilingInfo<CL_PROFILING_COMMAND_START>();
            cl_ulong end = i->getProfilingInfo<CL_PROFILING_COMMAND_END>();
            nseconds += end - start;
        };
    return nseconds;
}

std::vector<::size_t> QUtilityCL::getLocalSize(const cl_uint4& localSize)
{
    return std::vector<::size_t>(localSize.s, localSize.s + 3);
}

std::vector<::size_t> QUtilityCL::getGlobalSize(std::vector<::size_t>& localSize,
    const cl_uint4& textureSize)
{
    return ceil(localSize, textureSize);
}

cl::NDRange QUtilityCL::getGlobalSize(const cl::NDRange& localSize,
    const cl_uint4& textureSize)
{
    return ceil(localSize, textureSize);
}