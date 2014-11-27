/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QIO.h
 * @brief   QIO class definition.
 * 
 * This file defines the commonly used IO methods.
 * These methods includes reading/writing a text file or a binary file.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2012/02/07
 */

#ifndef QIO_H
#define QIO_H

#include <string>

class QIO
{
public:
    QIO();
    ~QIO();
    static bool getFileContent(const std::string& fileName, std::string &content);
    static bool saveFileContent(const std::string& fileName, const std::string &content);
    static bool getFileData(const std::string& fileName, void *data, long long size);
    static bool saveFileData(const std::string& fileName, void *data, long long size);
    static bool getFileSize(const std::string& fileName, long long& size);
private:

};

#endif  // QIO_H