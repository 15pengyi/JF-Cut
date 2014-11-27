/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QIO.cpp
 * @brief   QIO class declaration.
 * 
 * This file declares the most commonly used methods defined in QIO.h.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2012/02/07
 */

#include <iostream>
#include <fstream>

#include "QIO.h"

QIO::QIO()
{}

QIO::~QIO()
{}

bool QIO::getFileContent(const std::string& fileName, std::string &content)
{
    std::ifstream file(fileName);
    if (!file) return false;
    
    content = std::string(std::istreambuf_iterator<char>(file), (std::istreambuf_iterator<char>()));
    file.close();
    
    return true;
}

bool QIO::saveFileContent(const std::string& fileName, const std::string &content)
{
    std::ofstream file(fileName);
    if (!file) return false;

    file.write(content.data(), content.size());
    if (file.fail()) return false;
    file.close();

    return true;
}

bool QIO::getFileData(const std::string& fileName, void *data, long long size)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file) return false;
    
    file.read((char *)data, size);
    if (file.gcount() != size) return false;
    file.close();

    return true;
}

bool QIO::saveFileData(const std::string& fileName, void *data, long long size)
{
    std::ofstream file(fileName, std::ios::binary);
    if (!file) return false;

    file.write((char *)data, size);
    if (file.fail()) return false;
    file.close();

    return true; 
}

bool QIO::getFileSize(const std::string& fileName, long long& size)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file) return false;

    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.seekg(0, std::ios::beg);
    file.close();

    return true;
}
