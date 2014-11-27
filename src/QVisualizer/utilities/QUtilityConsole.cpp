/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QUtilityConsole.cpp
 * @brief   QUtilityConsole class declaration.
 * 
 * This file declares the most commonly used methods defined in QUtilityConsole.h.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/07/25
 */

#include "QUtilityConsole.h"

QUtilityConsole::QUtilityConsole()
{}

QUtilityConsole::~QUtilityConsole()
{}

void QUtilityConsole::printTimeCost(unsigned long milliseconds, const std::string& name)
{
    std::cerr << " > LOG: " << name.c_str() << " " << milliseconds << " ms." << std::endl;
}

void QUtilityConsole::printFPS(unsigned long milliseconds, const std::string& name)
{
    double fps = milliseconds == 0 ? 1000.0 : 1000.0 / milliseconds;
    std::cerr << " > LOG: " << name.c_str() << " " << fps << " fps." << std::endl;
}

void QUtilityConsole::printBandWidth(::size_t bytes, unsigned long milliseconds, const std::string& name)
{
    double rate = milliseconds == 0 ? 1000.0 : 1000.0 * bytes / (1 << 20) / milliseconds;
    std::cerr << " > LOG: " << name.c_str() << " " << rate << " MB/s." << std::endl;
}