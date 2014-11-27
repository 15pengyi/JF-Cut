/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QGCPanel.cpp
 * @brief   QGCPanel class declaration.
 * 
 * This file declares the methods of the widget defined in QGCPanel.h.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/01/09
 */

#include <QColorDialog>

#include "../utilities/QUtilityUI.h"
#include "QGCPanel.h"

QGCPanel::QGCPanel(QWidget* parent) : QWidget(parent)
{
    ui.setupUi(this);

    connect(ui.pushButtonColorFore, SIGNAL(clicked()), this, SLOT(slotToolkitColorForeChanged()));
    connect(ui.pushButtonColorBack, SIGNAL(clicked()), this, SLOT(slotToolkitColorBackChanged()));
    connect(ui.pushButtonColorCut, SIGNAL(clicked()), this, SLOT(slotToolkitColorCutChanged()));
    connect(ui.pushButtonColorTag, SIGNAL(clicked()), this, SLOT(slotToolkitColorTagChanged()));
}

QGCPanel::~QGCPanel()
{

}

const Ui::QGCPanel* QGCPanel::getUI()
{
    return &ui;
}

void QGCPanel::initialize(const std::string& path)
{
    foreach (QProfile* profile, this->findChildren<QProfile*>())
        profile->initialize(path);
}

void QGCPanel::selectColor(QPushButton *pushButtonColor)
{
    glm::vec4 color = QUtilityUI::getColor(pushButtonColor->toolTip());
    QColor c(QColorDialog::getColor(QColor::fromRgbF(color.r, color.g, color.b), this, "Select Color"));
    if (c.isValid())
    {
        QString rgb = QString("%1, %2, %3").arg(c.red()).arg(c.green()).arg(c.blue());
        QString styleSheet = QString("border-radius: 12px; background-color: rgba(%1, 127);").arg(rgb);
        pushButtonColor->setStyleSheet(styleSheet);
        pushButtonColor->setToolTip(rgb);
        pushButtonColor->update();
    }
}

void QGCPanel::slotToolkitColorForeChanged()
{
    selectColor(ui.pushButtonColorFore);
}

void QGCPanel::slotToolkitColorBackChanged()
{
    selectColor(ui.pushButtonColorBack);
}

void QGCPanel::slotToolkitColorCutChanged()
{
    selectColor(ui.pushButtonColorCut);
}

void QGCPanel::slotToolkitColorTagChanged()
{
    selectColor(ui.pushButtonColorTag);
}