/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QGCVisualizer.h
 * @brief   QGCVisualizer class definition.
 * 
 * This file defines a subclass corresponds to a particular visualization algorithm named Time-varying Volumetric Data Visualization Framework.
 *     QGCVisualizer class also has four components(see the definition of QCommon),
 *         the parent widget is the main UI,
 *         the panel corresponds to a 1D Transfer Function Editor,
 *         the render is a standard volume render,
 *         and the menu list includes open file, save file and so on.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/01/09
 */

#ifndef QGCVISUALIZER_H
#define QGCVISUALIZER_H

#include "ui_QGCVisualizer.h"
#include "ui_QGCPanel.h"

#include "../templates/QCommon.h"
#include "QGCWidget.h"
#include "QGCPanel.h"

class QGCVisualizer : public QCommom
{
    Q_OBJECT

public:
    QGCVisualizer(QWidget* parent = 0);
    ~QGCVisualizer();

protected:
    void initMenus();
    void initWidgets();

private:
    Ui::QVisualizerClass ui;
};
#endif