/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QSetting.h
 * @brief   QSetting class definition.
 * 
 * This file defines the most often used settings such as
 *     volume offset and volume scale(also known as window width and window level),
 *     geometry(translation and rotation),
 *     illumination parameters,
 *     and transfer functions.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/10/27
 */

#ifndef QERROR_H
#define QERROR_H

#include "../3rdParty/cl/cl_stacktrace.hpp"

#define Q_LOGIC_ERROR       -100
#define Q_INVALID_ARGUMENT  -101
#define Q_LENGTH_ERROR      -102
#define Q_OUT_OF_RANGE      -103
#define Q_FUTURE_ERROR      -104
#define Q_RUNTIME_ERROR     -110
#define Q_RANGE_ERROR       -111
#define Q_OVERFLOW_ERROR    -112
#define Q_UNDERFLOW_ERROR   -113
#define Q_SYSTEM_ERROR      -114

class QError : public cl::Error
{
protected:
    cl_int level_;
    void serialize(std::ostringstream& s, cl_int code)
    {
        std::string error;
        switch (code)
        {
        case Q_LOGIC_ERROR: error = "Q_LOGIC_ERROR"; break;
        case Q_INVALID_ARGUMENT: error = "Q_INVALID_ARGUMENT"; break;
        case Q_LENGTH_ERROR: error = "Q_LENGTH_ERROR"; break;
        case Q_OUT_OF_RANGE: error = "Q_OUT_OF_RANGE"; break;
        case Q_FUTURE_ERROR: error = "Q_FUTURE_ERROR"; break;
        case Q_RUNTIME_ERROR: error = "Q_RUNTIME_ERROR"; break;
        case Q_RANGE_ERROR: error = "Q_RANGE_ERROR"; break;
        case Q_OVERFLOW_ERROR: error = "Q_OVERFLOW_ERROR"; break;
        case Q_UNDERFLOW_ERROR: error = "Q_UNDERFLOW_ERROR"; break;
        case Q_SYSTEM_ERROR: error = "Q_SYSTEM_ERROR"; break;
        }
        if (!error.empty()) s << " > " << error << ", ";
        cl::Error::serialize(s, code);
    }
public:
    QError(cl_int level, cl_int err, const char * errStr = NULL) : level_(level), cl::Error(err, errStr) {}

    ~QError() throw() {}

    cl_int level(void) const { return level_; }

    virtual const char * what() throw ()
    {
        std::ostringstream s;
        serialize(s, err_);
        errStr_ = s.str();
        return errStr_.c_str();
    }
};

#endif  // QERROR_H