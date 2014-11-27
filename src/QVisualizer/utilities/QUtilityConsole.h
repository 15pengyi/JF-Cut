/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QUtilityConsole.h
 * @brief   QUtilityConsole class definition.
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

#ifndef QUTILITYCONSOLE_H
#define QUTILITYCONSOLE_H

#include <iostream>

class QUtilityConsole
{
public:
    QUtilityConsole();
    ~QUtilityConsole();
    
    static void printFPS(unsigned long milliseconds, const std::string& name = std::string());
    static void printTimeCost(unsigned long milliseconds, const std::string& name = std::string());
    static void printBandWidth(::size_t bytes, unsigned long milliseconds, const std::string& name = std::string());
};

#endif  // QUTILITYCONSOLE_H