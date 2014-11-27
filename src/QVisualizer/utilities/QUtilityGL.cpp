/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QUtilityGL.cpp
 * @brief   QUtilityGL class declaration.
 * 
 * This file declares the most commonly used methods defined in QUtilityGL.h.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/07/25
 */

#include <iostream>

#include "QUtilityGL.h"

QUtilityGL::QUtilityGL()
{}

QUtilityGL::~QUtilityGL()
{}

bool QUtilityGL::checkGLStatus(char *file, int line, char *name)
{
    GLenum error = glGetError();
    while (error != GL_NO_ERROR)
    {
        std::cerr << " > ERROR: " << file << "(" << line << ") " << name << " failed. ";
        switch (error)
        {
        case GL_INVALID_ENUM:
            std::cerr << "an unacceptable value is specified for an enumerated argument. The offending command is ignored, and has no other side effect than to set the error flag.";
            break;
        case GL_INVALID_VALUE:
            std::cerr << "a numeric argument is out of range. The offending command is ignored, and has no other side effect than to set the error flag.";
            break;
        case GL_STACK_OVERFLOW:
            std::cerr << "this command would cause a stack overflow. The offending command is ignored, and has no other side effect than to set the error flag.";
            break;
        case GL_STACK_UNDERFLOW:
            std::cerr << "this command would cause a stack underflow. The offending command is ignored, and has no other side effect than to set the error flag.";
            break;
        case GL_OUT_OF_MEMORY:
            std::cerr << "there is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
            break;
        case GL_INVALID_OPERATION:
            std::cerr << "the specified operation is not allowed in the current state. The offending command is ignored, and has no other side effect than to set the error flag.";
            break;
        default:
            std::cerr << "unknown.";
            break;
        }
        std::cerr << std::endl;

        if (error = glGetError() == GL_NO_ERROR) return false;
    }
    return true;
}

bool QUtilityGL::checkShaderStatus(char *file, int line, GLuint shader, GLenum name)
{
    GLint status = true;
    glGetShaderiv(shader, name, &status);
    if (!status)
    {
        std::cerr << " > ERROR: " << file << "(" << line << ") checkShaderStatus()." << std::endl;
        return false;
    }

    return true;
}

bool QUtilityGL::checkProgramStatus(char *file, int line, GLuint program, GLenum name)
{
    GLint status = true;
    glGetProgramiv(program, name, &status);
    if (!status)
    {
        std::cerr << " > ERROR: " << file << "(" << line << ") checkProgramStatus()." << std::endl;
        return false;
    }

    return true;
}

bool QUtilityGL::checkBufferStatus(int number)
{
    int maxBuffers = 0;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxBuffers);
    if (maxBuffers < number)
    {
        std::cerr << " > ERROR: checking buffers." << std::endl;
        return false;
    }
    return true;
}

bool QUtilityGL::checkFramebufferStatus(unsigned int target)
{
    unsigned int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << " > ERROR: ";
        switch (status)
        {
        case GL_FRAMEBUFFER_UNDEFINED:
            std::cerr << "target is the default framebuffer, but the default framebuffer does not exist.";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            std::cerr << "any of the framebuffer attachment points are framebuffer incomplete.";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            std::cerr << "the framebuffer does not have at least one image attached to it.";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            std::cerr << "the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAWBUFFERi.";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            std::cerr << "GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER.";
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED:
            std::cerr << "the combination of internal formats of the attached images violates an implementation-dependent set of restrictions";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            std::cerr << "the value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or, the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES; the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, the attached images are a mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not true for all attached textures.";
            break;
        /*
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            std::cerr << "any framebuffer attachment is layered, and any populated attachment is not layered, or all populated color attachments are not from textures of the same target.";
            break;
        */
        default:
            std::cerr << "unknown.";
            break;
        }
        std::cerr << std::endl;
        return false;
    }
    return true;
}

bool QUtilityGL::checkSupport()
{
    return QUtilityGL::checkOpenGLSupport() && QUtilityGL::checkGlewSupport() && QUtilityGL::checkShaderSupport();
}

bool QUtilityGL::checkGlewSupport()
{
    unsigned int error = glewInit();
    if (error != GLEW_OK || !glewIsSupported("GL_VERSION_2_1"))
    {
        std::cerr << " > ERROR: checking glew support." << std::endl;
        std::cerr << " > ERROR: " << glewGetErrorString(error) << std::endl;
        return false;
    }
    return true;
}

bool QUtilityGL::checkOpenGLSupport()
{
    if (!GL_VERSION_3_0)
    {
        std::cerr << " > ERROR: checking opengl support." << std::endl;
        return false;
    }
    else
    {
        std::cerr << " > GL_VERSION: " << glGetString(GL_VERSION) << std::endl;
    }
    return true;
}

bool QUtilityGL::checkShaderSupport()
{
    if (!GL_VERTEX_SHADER || !GL_FRAGMENT_SHADER)
    {
        std::cerr << " > ERROR: checking shader support." << std::endl;
        return false;
    }
    return true;
}

bool QUtilityGL::checkArguments(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << " > ERROR: checking arguments." << std::endl;
        std::cerr << " > Usage: jrendering <file.dat>." << std::endl;
        return false;
    }
    return true;
}

unsigned int QUtilityGL::getSize(unsigned int target)
{
    switch (target)
    {
    case GL_UNSIGNED_BYTE:
        return 1;
    case GL_UNSIGNED_SHORT:
        return 2;
    case GL_FLOAT:
        return 4;
    case GL_DOUBLE:
        return 8;
    default:
        return 0;
    }
}