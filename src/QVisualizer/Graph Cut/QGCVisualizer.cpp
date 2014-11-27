/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * rr
 * @file    QGCVisualizer.cpp
 * @brief   QGCVisualizer class declaration.
 * 
 * This file declares the initialization methods of components defined in QGCVisualizer.h.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/01/09
 */

#include <fstream>

#include "../utilities/QUtilityMath.h"
#include "QGCVisualizer.h"

QGCVisualizer::QGCVisualizer(QWidget* parent) : QCommom(parent)
{
    ui.setupUi(this);

    initMenus();
    initWidgets();
}

QGCVisualizer::~QGCVisualizer()
{

}

void QGCVisualizer::initMenus()
{
    Menu* menus = this->getMenus();
    for (auto i = menus->file.begin(); i != menus->file.end(); i++)
        ui.menuFile->addAction(*i);
    for (auto i = menus->edit.begin(); i != menus->edit.end(); i++)
        ui.menuEdit->addAction(*i);
    for (auto i = menus->view.begin(); i != menus->view.end(); i++)
        ui.menuView->addAction(*i);
    for (auto i = menus->settings.begin(); i != menus->settings.end(); i++)
        ui.menuSettings->addAction(*i);
}

void QGCVisualizer::initWidgets()
{
    std::ifstream file("./settings/settings_graph_cut.txt");
    std::string line;

    std::getline(file, line);
    line = line.substr(line.find_first_of(':') + 1);
    std::string dataset = line;
    QUtilityMath::trim(dataset);

    std::getline(file, line);
    line = line.substr(line.find_first_of(':') + 1);
    std::string corporation = line;
    QUtilityMath::trim(corporation);

    file.close();

    panel_ = new QGCPanel(parent_);
    this->setCentralWidget(panel_);

    const Ui::QGCPanel* ui = ((QGCPanel*)panel_)->getUI();
    ui->widgetRender->initConnections((QGCPanel* )panel_);
    ui->widgetRender->initData(dataset);
    ui->widgetRender->initCorporation(corporation);

    ((QGCPanel*)panel_)->initialize(ui->widgetRender->dataFilePath);
}