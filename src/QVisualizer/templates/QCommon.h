/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QCommon.h
 * @brief   QCommon class definition.
 * 
 * This file defines a base class for visualization.
 * The class consists of four components:
 *     a parent widget which should be the main UI,
 *     a render for display,
 *     a panel for user interation,
 *     and a menu list for registration.
 * 
 * @version 1.0
 * @author  Edgar Liao, Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2012/02/07
 */

#ifndef QCOMMON_H
#define QCOMMON_H

#include <list>
#include <QtGui/QMainWindow>
#include <QtGui/QAction>
#include <QtGui/QWidget>

// This structure is used to save the actions in each file in different modes.
struct Menu
{
    std::list<QAction*> file;
    std::list<QAction*> edit;
    std::list<QAction*> view;
    std::list<QAction*> settings;
};

class QCommom : public QMainWindow
{
    Q_OBJECT

public:
    QCommom();
    QCommom(QWidget* parent, Qt::WFlags flags = 0);
    ~QCommom();
    
    QWidget* getParent();
    QWidget* getRender();
    QWidget* getPanel();
    struct Menu* getMenus();
    
protected:
    QWidget *parent_, *render_, *panel_;
    struct Menu menus_;

    virtual void initMenus();
    virtual void initPanels();
    virtual void initConnections();
};

#endif