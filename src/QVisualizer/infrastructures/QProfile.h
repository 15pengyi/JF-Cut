/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QProfile.h
 * @brief   QProfile class definition.
 * 
 * This file defines ...
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/07/24
 */

#ifndef QPROFILE_H
#define QPROFILE_H

#include <vector>

#include <QWidget>

class QPushButton;

class QProfile : public QWidget
{
    Q_OBJECT

public:
    QProfile(QWidget *parent = 0);
    ~QProfile();
    
    QWidget *profile;
    QPushButton *load, *save;

    void initialize(const std::string& path);

public slots:
    void slotLoad();
    void slotSave();

private:
    std::string path;
};

#endif  // QPROFILE_H