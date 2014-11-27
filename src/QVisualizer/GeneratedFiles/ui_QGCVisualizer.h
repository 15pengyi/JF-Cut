/********************************************************************************
** Form generated from reading UI file 'QGCVisualizer.ui'
**
** Created: Fri Nov 28 00:29:26 2014
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGCVISUALIZER_H
#define UI_QGCVISUALIZER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QVisualizerClass
{
public:
    QAction *actionVector_Field_Visualization;
    QAction *actionMarching_Cubes;
    QAction *actionVolume_Rendering;
    QAction *actionTensor_Field_Visualization;
    QAction *actionVirtual_Environment_For_Visualization;
    QAction *actionLarge_Scale_Data_Visualization;
    QAction *actionVisualization_Software_and_Frameworks;
    QAction *actionPerceptual_Issues_in_Visualization;
    QAction *actionSelected_Topics_and_QApplications;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuSettings;
    QMenu *menuAbout;

    void setupUi(QMainWindow *QVisualizerClass)
    {
        if (QVisualizerClass->objectName().isEmpty())
            QVisualizerClass->setObjectName(QString::fromUtf8("QVisualizerClass"));
        QVisualizerClass->resize(800, 600);
        QVisualizerClass->setMinimumSize(QSize(0, 0));
        QVisualizerClass->setMaximumSize(QSize(16777215, 16777215));
        actionVector_Field_Visualization = new QAction(QVisualizerClass);
        actionVector_Field_Visualization->setObjectName(QString::fromUtf8("actionVector_Field_Visualization"));
        actionMarching_Cubes = new QAction(QVisualizerClass);
        actionMarching_Cubes->setObjectName(QString::fromUtf8("actionMarching_Cubes"));
        actionVolume_Rendering = new QAction(QVisualizerClass);
        actionVolume_Rendering->setObjectName(QString::fromUtf8("actionVolume_Rendering"));
        actionTensor_Field_Visualization = new QAction(QVisualizerClass);
        actionTensor_Field_Visualization->setObjectName(QString::fromUtf8("actionTensor_Field_Visualization"));
        actionVirtual_Environment_For_Visualization = new QAction(QVisualizerClass);
        actionVirtual_Environment_For_Visualization->setObjectName(QString::fromUtf8("actionVirtual_Environment_For_Visualization"));
        actionLarge_Scale_Data_Visualization = new QAction(QVisualizerClass);
        actionLarge_Scale_Data_Visualization->setObjectName(QString::fromUtf8("actionLarge_Scale_Data_Visualization"));
        actionVisualization_Software_and_Frameworks = new QAction(QVisualizerClass);
        actionVisualization_Software_and_Frameworks->setObjectName(QString::fromUtf8("actionVisualization_Software_and_Frameworks"));
        actionPerceptual_Issues_in_Visualization = new QAction(QVisualizerClass);
        actionPerceptual_Issues_in_Visualization->setObjectName(QString::fromUtf8("actionPerceptual_Issues_in_Visualization"));
        actionSelected_Topics_and_QApplications = new QAction(QVisualizerClass);
        actionSelected_Topics_and_QApplications->setObjectName(QString::fromUtf8("actionSelected_Topics_and_QApplications"));
        centralwidget = new QWidget(QVisualizerClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QVisualizerClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QVisualizerClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        QVisualizerClass->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuAbout->menuAction());

        retranslateUi(QVisualizerClass);

        QMetaObject::connectSlotsByName(QVisualizerClass);
    } // setupUi

    void retranslateUi(QMainWindow *QVisualizerClass)
    {
        QVisualizerClass->setWindowTitle(QApplication::translate("QVisualizerClass", "QVisualizer", 0, QApplication::UnicodeUTF8));
        actionVector_Field_Visualization->setText(QApplication::translate("QVisualizerClass", "Vector Field Visualization", 0, QApplication::UnicodeUTF8));
        actionMarching_Cubes->setText(QApplication::translate("QVisualizerClass", "Marching Cubes", 0, QApplication::UnicodeUTF8));
        actionVolume_Rendering->setText(QApplication::translate("QVisualizerClass", "Volume Rendering", 0, QApplication::UnicodeUTF8));
        actionTensor_Field_Visualization->setText(QApplication::translate("QVisualizerClass", "Tensor Field Visualization", 0, QApplication::UnicodeUTF8));
        actionVirtual_Environment_For_Visualization->setText(QApplication::translate("QVisualizerClass", "Virtual Environment For Visualization", 0, QApplication::UnicodeUTF8));
        actionLarge_Scale_Data_Visualization->setText(QApplication::translate("QVisualizerClass", "Large-Scale Data Visualization", 0, QApplication::UnicodeUTF8));
        actionVisualization_Software_and_Frameworks->setText(QApplication::translate("QVisualizerClass", "Visualization Software and Frameworks", 0, QApplication::UnicodeUTF8));
        actionPerceptual_Issues_in_Visualization->setText(QApplication::translate("QVisualizerClass", "Perceptual Issues in Visualization", 0, QApplication::UnicodeUTF8));
        actionSelected_Topics_and_QApplications->setText(QApplication::translate("QVisualizerClass", "Selected Topics and QApplications", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("QVisualizerClass", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("QVisualizerClass", "Edit", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("QVisualizerClass", "View", 0, QApplication::UnicodeUTF8));
        menuSettings->setTitle(QApplication::translate("QVisualizerClass", "Settings", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("QVisualizerClass", "About", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QVisualizerClass: public Ui_QVisualizerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGCVISUALIZER_H
