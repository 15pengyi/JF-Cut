/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QGCPanel.h
 * @brief   QGCPanel class definition.
 * 
 * This file defines a panel widget for users to adjust the parameters of Marching Cubes.
 *     The parameters includes
 *         the iso-value of iso-surface.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/01/09
 */

#ifndef QGCCONTROLPANEL_H
#define QGCCONTROLPANEL_H

#include <QWidget>

#include "ui_QGCPanel.h"

class QGCPanel : public QWidget
{
    Q_OBJECT

public:
    QGCPanel(QWidget* parent = 0);
    ~QGCPanel();

    const Ui::QGCPanel* getUI();
    void initialize(const std::string& path);

public slots:
    void slotToolkitColorForeChanged();
    void slotToolkitColorBackChanged();
    void slotToolkitColorCutChanged();
    void slotToolkitColorTagChanged();

public:
    void selectColor(QPushButton *pushButtonColor);
    
private:
    Ui::QGCPanel ui;
};

#endif