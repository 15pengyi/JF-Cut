/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QProfile.cpp
 * @brief   QProfile class declaration.
 * 
 * This file declares ...
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/07/24
 */

#include <QPushButton>
#include <QGridLayout>
#include <QApplication>

#include "../utilities/QUtilityUI.h"
#include "QProfile.h"

QProfile::QProfile(QWidget *parent)
    : QWidget(parent),
    path("./")
{
    profile = new QWidget(this);
    profile->setObjectName(QString::fromUtf8("profile"));
    profile->setMaximumSize(QSize(16777215, 32));

    QGridLayout* gridLayout = new QGridLayout(profile);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setHorizontalSpacing(24);
    gridLayout->setVerticalSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    load = new QPushButton(profile);
    load->setObjectName(QString::fromUtf8("load"));
    load->setMinimumSize(QSize(60, 0));
    load->setMaximumSize(QSize(60, 16777215));
    load->setText(QApplication::translate("QProfile", "Load", 0, QApplication::UnicodeUTF8));
    gridLayout->addWidget(load, 0, 0, 1, 1);

    save = new QPushButton(profile);
    save->setObjectName(QString::fromUtf8("save"));
    save->setMinimumSize(QSize(60, 0));
    save->setMaximumSize(QSize(60, 16777215));
    save->setText(QApplication::translate("QProfile", "Save", 0, QApplication::UnicodeUTF8));
    gridLayout->addWidget(save, 0, 1, 1, 1);
}

QProfile::~QProfile()
{}

void QProfile::initialize(const std::string& path)
{
    this->path = path;

    QVBoxLayout* layout = (QVBoxLayout*)this->layout();
    layout->insertWidget(0, profile);

    connect(load, SIGNAL(clicked()), this, SLOT(slotLoad()));
    connect(save, SIGNAL(clicked()), this, SLOT(slotSave()));
}

void QProfile::slotLoad()
{
    QUtilityUI::loadWidget(path, this);
}

void QProfile::slotSave()
{
    QUtilityUI::saveWidget(path, this);
}