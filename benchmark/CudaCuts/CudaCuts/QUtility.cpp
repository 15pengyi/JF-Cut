/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QUtility.cpp
 * @brief   QUtility class declaration.
 * 
 * This file declares the most commonly used methods defined in QUtility.h.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2012/02/07
 */

#include "QUtility.h"
#include "QIO.h"

QUtility::QUtility()
{}

QUtility::~QUtility()
{}

void QUtility::trim(std::string &s)
{
    if (!s.empty())
    {
        int found = s.find_first_of('\t');
        while (found != std::string::npos)
        {
            s.replace(found, 1, " ");
            found = s.find_first_of('\t', found + 1);
        }
        s.erase(0, s.find_first_not_of(' '));
        s.erase(s.find_last_not_of(' ') + 1);
    }
}

::size_t QUtility::ceil(::size_t local_size, ::size_t global_size) 
{
    ::size_t r = global_size % local_size;
    return r == 0 ? global_size : global_size + local_size - r;
}