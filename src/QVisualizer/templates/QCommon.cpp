/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QCommon.cpp
 * @brief   QCommon class declaration.
 * 
 * This file declares the initialization methods for the components defined in QCommon.h.
 * 
 * @version 1.0
 * @author  Edgar Liao, Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2012/02/07
 */

#include "QCommon.h"

QCommom::QCommom() :
    render_(NULL), parent_(NULL), panel_(NULL)
{}

QCommom::QCommom(QWidget* parent, Qt::WFlags flags) :
    render_(NULL), parent_(parent), panel_(NULL)
{}

QCommom::~QCommom()
{}

QWidget* QCommom::getParent()
{
    return parent_;
}

QWidget* QCommom::getRender()
{
    return render_;
}

QWidget* QCommom::getPanel()
{
    return panel_;
}

struct Menu* QCommom::getMenus()
{
    return &menus_;
}

void QCommom::initConnections()
{}

void QCommom::initMenus()
{}

void QCommom::initPanels()
{}