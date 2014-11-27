/********************************************************************************
** Form generated from reading UI file 'QGCPanel.ui'
**
** Created: Fri Nov 28 00:29:25 2014
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGCPANEL_H
#define UI_QGCPANEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../Graph Cut/QGCWidget.h"
#include "../infrastructures/QProfile.h"
#include "../infrastructures/QTransferFunction1D.h"

QT_BEGIN_NAMESPACE

class Ui_QGCPanel
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QGroupBox *groupBoxVolumeRendering;
    QGridLayout *gridLayoutVolumeRendering;
    QGroupBox *groupBoxGraphCut;
    QGridLayout *gridLayoutGraphCut;
    QTabWidget *tabWidgetBackStage;
    QProfile *tabAlgorithm;
    QVBoxLayout *verticalLayoutAlgorithm;
    QWidget *widgetHeightField;
    QGridLayout *gridLayoutHeightField;
    QLabel *labelHeightField;
    QRadioButton *radioButtonGlobalRelabel;
    QSpacerItem *horizontalSpacerHeightField;
    QRadioButton *radioButtonNone;
    QPushButton *pushButtonExport;
    QWidget *widgetCutMethod;
    QGridLayout *gridLayoutMethod;
    QRadioButton *radioButtonCutMethodFastCut;
    QLabel *labelCutMethod;
    QSpacerItem *horizontalSpacerCutMethod;
    QRadioButton *radioButtonCutMethodJFCut;
    QPushButton *pushButtonCutAlgorithm;
    QWidget *widgetTile2D;
    QGridLayout *gridLayoutTile2D;
    QSpinBox *spinBoxTile2DY;
    QSpinBox *spinBoxTile2DX;
    QLabel *labelTile2D;
    QSpacerItem *horizontalSpacerTile2D;
    QWidget *widgetTile3D;
    QGridLayout *gridLayoutTile3D;
    QSpacerItem *horizontalSpacerTile3D;
    QLabel *labelTile3D;
    QSpinBox *spinBoxTile3DY;
    QSpinBox *spinBoxTile3DZ;
    QSpinBox *spinBoxTile3DX;
    QProfile *tabModeling;
    QVBoxLayout *verticalLayoutModeling;
    QWidget *widgetModeling;
    QGridLayout *gridLayoutModelingMethod;
    QLabel *labelModelingMethod;
    QPushButton *pushButtonCutModeling;
    QSpacerItem *horizontalSpacerModelingMethod;
    QRadioButton *radioButtonBK;
    QRadioButton *radioButtonLazySnapping;
    QWidget *widgetClustering;
    QGridLayout *gridLayoutClustering;
    QLabel *labelKMeans;
    QLabel *labelKMeansIterations;
    QSpinBox *spinBoxKMeansIterations;
    QLabel *labelClustering;
    QSpinBox *spinBoxK;
    QWidget *widgetLazyCapacity;
    QGridLayout *gridLayoutLazyCapacity;
    QDoubleSpinBox *doubleSpinBoxLazyTerminal;
    QLabel *labelLazyTerminal;
    QLabel *labelLazyNeighbor;
    QLabel *labelLazyCapacity;
    QDoubleSpinBox *doubleSpinBoxLazyNeighbor;
    QWidget *widgetBKCapacity;
    QGridLayout *gridLayoutLazyCapacity_2;
    QLabel *labelBKCapacity;
    QLabel *labelBKNeighbor;
    QLabel *labelBKTerminal;
    QDoubleSpinBox *doubleSpinBoxBKTerminal;
    QDoubleSpinBox *doubleSpinBoxBKNeighbor;
    QProfile *tabConvergence;
    QVBoxLayout *verticalLayoutConvergence;
    QWidget *widgetLaunch;
    QGridLayout *gridLayoutLaunch;
    QCheckBox *checkBoxPrint;
    QPushButton *pushButtonCut;
    QLabel *labelLaunch;
    QCheckBox *checkBoxEnergy;
    QCheckBox *checkBoxComputeTag;
    QWidget *widgetUpdate;
    QGridLayout *gridLayoutUpdate;
    QSpinBox *spinBoxCountIterations;
    QLabel *labelUpdate;
    QLabel *labelCountIterations;
    QLabel *labelCutIterations;
    QSpinBox *spinBoxCutIterations;
    QWidget *widgetOther;
    QGridLayout *gridLayoutUpdate_2;
    QSpinBox *spinBoxTotalIterations;
    QLabel *labelOther;
    QLabel *labelTotalIterations;
    QLabel *labelPrintIterations;
    QSpinBox *spinBoxPrintIterations;
    QProfile *tabFeature;
    QVBoxLayout *verticalLayoutFeature;
    QWidget *widgetWeight;
    QGridLayout *gridLayoutWeight;
    QDoubleSpinBox *doubleSpinBoxWeightX;
    QDoubleSpinBox *doubleSpinBoxWeightY;
    QLabel *labelWeight;
    QDoubleSpinBox *doubleSpinBoxWeightW;
    QLabel *labelWeightZ;
    QLabel *labelWeightW;
    QLabel *labelWeightX;
    QLabel *labelWeightY;
    QDoubleSpinBox *doubleSpinBoxWeightZ;
    QSpacerItem *horizontalSpacerWeight;
    QProfile *tabOpenCL;
    QVBoxLayout *verticalLayoutOpenCL;
    QWidget *widgetMaxGroup;
    QGridLayout *gridLayoutMaxGroup;
    QSpacerItem *horizontalSpacerMaxGroup;
    QLabel *labelMaxGroup;
    QSpinBox *spinBoxMaxGroup;
    QWidget *widgetLocal1D;
    QGridLayout *gridLayoutLocal1D;
    QLabel *labelLocalSize1DX;
    QSpacerItem *horizontalSpacerLocal1D;
    QSpinBox *spinBoxLocalSize1DX;
    QWidget *widgetLocal2D;
    QGridLayout *gridLayoutLocal2D;
    QSpacerItem *horizontalSpacerLocal2D;
    QLabel *labelLocalSize2D;
    QSpinBox *spinBoxLocalSize2DX;
    QSpinBox *spinBoxLocalSize2DY;
    QWidget *widgetLocal3D;
    QGridLayout *gridLayoutLocal3D;
    QSpinBox *spinBoxLocalSize3DY;
    QSpacerItem *horizontalSpacerLocal3D;
    QLabel *labelLocalSize3D;
    QSpinBox *spinBoxLocalSize3DX;
    QSpinBox *spinBoxLocalSize3DZ;
    QTabWidget *tabWidgetFrontStage;
    QProfile *tabBrushing;
    QVBoxLayout *verticalLayoutBrushing;
    QWidget *widgetBrushingOpacity;
    QGridLayout *gridLayoutBrushingOpacity;
    QLabel *labelOpacity;
    QSlider *horizontalSliderOpacity;
    QSpinBox *spinBoxOpacity;
    QWidget *widgetBrushingSize;
    QGridLayout *gridLayoutBrushingSize;
    QLabel *labelSize;
    QSlider *horizontalSliderSize;
    QSpinBox *spinBoxSize;
    QWidget *widgetBrushingShape;
    QGridLayout *gridLayoutBrushingShape;
    QRadioButton *radioButtonShapeSquare;
    QLabel *labelShape;
    QRadioButton *radioButtonShapeCross;
    QRadioButton *radioButtonShapeCircle;
    QSpacerItem *horizontalSpacerShape;
    QProfile *tabMode;
    QVBoxLayout *verticalLayoutMode;
    QWidget *widgetModeType;
    QGridLayout *gridLayoutModeType;
    QLabel *labelType;
    QRadioButton *radioButtonModeBrush;
    QRadioButton *radioButtonModeNormal;
    QRadioButton *radioButtonModeEraser;
    QSpacerItem *horizontalSpacerModeType;
    QWidget *widgetBrushingObject;
    QGridLayout *gridLayoutBrushingObject;
    QLabel *labelBrushingObject;
    QRadioButton *radioButtonBrushingObjectBack;
    QRadioButton *radioButtonBrushingObjectCut;
    QRadioButton *radioButtonBrushingObjectFore;
    QRadioButton *radioButtonBrushingObjectTag;
    QWidget *widgetModeEdit;
    QGridLayout *gridLayoutModeEdit;
    QPushButton *pushButtonClear;
    QLabel *labelModeEdit;
    QPushButton *pushButtonUndo;
    QPushButton *pushButtonRedo;
    QSpacerItem *horizontalSpacerModeEdit2;
    QProfile *tabColor;
    QVBoxLayout *verticalLayoutColor;
    QWidget *widgetColorFore;
    QGridLayout *gridLayoutColorFore;
    QPushButton *pushButtonColorFore;
    QLabel *labelColorForeNote;
    QSlider *horizontalSliderColorFore;
    QSpinBox *spinBoxColorFore;
    QWidget *widgetColorBack;
    QGridLayout *gridLayoutColorBack;
    QSlider *horizontalSliderColorBack;
    QPushButton *pushButtonColorBack;
    QLabel *labelColorBackNote;
    QSpinBox *spinBoxColorBack;
    QWidget *widgetColorCut;
    QGridLayout *gridLayoutColorCut;
    QPushButton *pushButtonColorCut;
    QLabel *labelColorCutNote;
    QSlider *horizontalSliderColorCut;
    QSpinBox *spinBoxColorCut;
    QWidget *widgetColorTag;
    QGridLayout *gridLayoutColorTag;
    QPushButton *pushButtonColorTag;
    QLabel *labelColorTagNote;
    QSlider *horizontalSliderColorTag;
    QSpinBox *spinBoxColorTag;
    QProfile *tabTexture;
    QVBoxLayout *verticalLayoutTexture;
    QWidget *widgetTextureGraph;
    QGridLayout *gridLayoutTextureGraph;
    QPushButton *pushButtonSaveGraph;
    QPushButton *pushButtonLoadGraph;
    QLabel *labelGraph;
    QCheckBox *checkBoxGraph;
    QWidget *widgetTextureGradient;
    QGridLayout *gridLayoutTextureGradient;
    QPushButton *pushButtonLoadGradient;
    QPushButton *pushButtonSaveGradient;
    QLabel *labelGradient;
    QCheckBox *checkBoxGradient;
    QWidget *widgetTextureFeature;
    QGridLayout *gridLayoutTextureFeature;
    QPushButton *pushButtonLoadFeature;
    QPushButton *pushButtonSaveFeature;
    QLabel *labelFeature;
    QCheckBox *checkBoxFeature;
    QWidget *widgetTextureCut;
    QGridLayout *gridLayoutTextureCut;
    QCheckBox *checkBoxCut;
    QPushButton *pushButtonSaveCut;
    QPushButton *pushButtonLoadCut;
    QLabel *labelCut;
    QGCWidget *widgetRender;
    QGroupBox *groupBoxRendering;
    QGridLayout *gridLayoutRendering;
    QGroupBox *groupBoxTransferFunctionEditor;
    QGridLayout *gridLayoutTransferFunctionEditor;
    QTransferFunction1D *widgetEditor;
    QGroupBox *groupBoxWindow;
    QGridLayout *gridLayoutWindow;
    QSlider *verticalSliderWindowLevel;
    QSlider *verticalSliderWindowWidth;
    QLabel *labelWindowWidth;
    QLabel *labelWindowLevel;
    QLabel *labelWindowLevelNote;
    QLabel *labelWindowWidthNote;
    QTabWidget *tabWidgetSettings;
    QWidget *tabTransferFunction;
    QVBoxLayout *verticalLayoutTransferFunction;
    QWidget *widgetTransferFunctionSettings;
    QGridLayout *gridLayoutTransferFunctionSettings;
    QPushButton *pushButtonLoadTransferFunction;
    QPushButton *pushButtonSaveTransferFunction;
    QWidget *widgetInterpolation;
    QGridLayout *gridLayoutInterpolation;
    QRadioButton *radioButtonInterpolationLinear;
    QLabel *labelInterpolation;
    QRadioButton *radioButtonInterpolationCubic;
    QSpacerItem *horizontalSpacerInterpolation;
    QWidget *widgetPointNumber;
    QGridLayout *gridLayoutPointNumber;
    QLabel *labelPointNumber;
    QRadioButton *radioButtonPointNumber4;
    QRadioButton *radioButtonPointNumber8;
    QRadioButton *radioButtonPointNumber16;
    QWidget *widgetLayout;
    QGridLayout *gridLayoutLayout;
    QLabel *labelLayout;
    QRadioButton *radioButtonLayoutNormal;
    QRadioButton *radioButtonLayoutVertical;
    QRadioButton *radioButtonLayoutWave;
    QWidget *widgetColorSpace;
    QGridLayout *gridLayoutColorSpace;
    QRadioButton *radioButtonColorSpaceLUV;
    QRadioButton *radioButtonColorSpaceRGB;
    QLabel *labelColorSpace;
    QRadioButton *radioButtonColorSpaceHSL;
    QProfile *tabView;
    QVBoxLayout *verticalLayoutView;
    QWidget *widgetViewTranslation;
    QGridLayout *gridLayoutViewTranslation;
    QLabel *labelViewTranslation;
    QDoubleSpinBox *doubleSpinBoxTranslationX;
    QDoubleSpinBox *doubleSpinBoxTranslationZ;
    QDoubleSpinBox *doubleSpinBoxTranslationY;
    QSpacerItem *horizontalSpacerViewTranslation;
    QWidget *widgetViewRotation;
    QGridLayout *gridLayoutViewRotation;
    QDoubleSpinBox *doubleSpinBoxRotationX;
    QDoubleSpinBox *doubleSpinBoxRotationY;
    QLabel *labelViewRotation;
    QDoubleSpinBox *doubleSpinBoxRotationW;
    QLabel *labelRotationZ;
    QDoubleSpinBox *doubleSpinBoxRotationZ;
    QLabel *labelRotationW;
    QLabel *labelRotationY;
    QLabel *labelRotationX;
    QSpacerItem *horizontalSpacerViewRotation;
    QWidget *widgetViewSize;
    QGridLayout *gridLayoutViewSize;
    QLabel *labelSizeY;
    QSpinBox *spinBoxViewSizeY;
    QLabel *labelViewSize;
    QSpinBox *spinBoxViewSizeX;
    QLabel *labelSizeX;
    QSpacerItem *horizontalSpacerViewSize;
    QProfile *tabProjection;
    QVBoxLayout *verticalLayoutProjection;
    QWidget *widgetProjectionMode;
    QGridLayout *gridLayoutProjectionMode;
    QRadioButton *radioButtonPerspective;
    QRadioButton *radioButtonOrthogonal;
    QLabel *labelProjectionMode;
    QSpacerItem *horizontalSpacerProjectionMode;
    QWidget *widgetProjectionPerspective;
    QGridLayout *gridLayoutProjectionPerspective;
    QDoubleSpinBox *doubleSpinBoxZNear;
    QDoubleSpinBox *doubleSpinBoxZFar;
    QLabel *labelPerspective;
    QLabel *labelZNear;
    QLabel *labelZFar;
    QWidget *widgetProjectionFOVY;
    QGridLayout *gridLayoutProjectionFOVY;
    QLabel *labelFOVY;
    QSlider *horizontalSliderFOVY;
    QSpinBox *spinBoxFOVY;
    QWidget *widgetProjectionOrthogonal;
    QGridLayout *gridLayoutProjectionOrthogonal;
    QLabel *labelOrthogonal;
    QSlider *horizontalSliderOrthogonal;
    QSpinBox *spinBoxOrthogonal;
    QProfile *tabRayCasting;
    QVBoxLayout *verticalLayoutRayCasting;
    QWidget *widgetRayCastingMode;
    QGridLayout *gridLayoutRayCastingMode;
    QRadioButton *radioButtonNormal;
    QRadioButton *radioButtonPreIntegration;
    QSpacerItem *horizontalSpacerRayCastingMode;
    QLabel *labelRayCastingMode;
    QRadioButton *radioButtonFeature;
    QWidget *widgetRayCastingObject;
    QGridLayout *gridLayoutRayCastingObject;
    QLabel *labelRayCastingObject;
    QRadioButton *radioButtonRayCastingObjectAll;
    QRadioButton *radioButtonRayCastingObjectFore;
    QRadioButton *radioButtonRayCastingObjectBack;
    QRadioButton *radioButtonRayCastingObjectTag;
    QRadioButton *radioButtonRayCastingObjectCut;
    QSpacerItem *horizontalSpacerRayCastingObject;
    QWidget *widgetRayCastingSampleApproximation;
    QGridLayout *gridLayoutRayCastingSampleApproximation;
    QLabel *labelSampleApproximation;
    QLabel *labelSampleRatio;
    QSpinBox *spinBoxSampleScale;
    QDoubleSpinBox *doubleSpinBoxSampleRatio;
    QSpacerItem *horizontalSpacerSampleApproximation;
    QLabel *labelSampleScale;
    QWidget *widgetRayCastingSampleNumber;
    QGridLayout *gridLayoutRayCastingSampleNumber;
    QLabel *labelSampleNumber;
    QSpinBox *spinBoxSampleNumber;
    QSlider *horizontalSliderSampleNumber;
    QProfile *tabPreIntegration;
    QVBoxLayout *verticalLayoutPreIntegration;
    QWidget *widgetPreIntegrationBias;
    QGridLayout *gridLayoutPreIntegrationBias;
    QSpinBox *spinBoxPreIntegrationBias;
    QSlider *horizontalSliderPreIntegrationBias;
    QLabel *labelPreIntegrationBias;
    QWidget *widgetPreIntegrationScale;
    QGridLayout *gridLayoutPreIntegrationScale;
    QSlider *horizontalSliderPreIntegrationScale;
    QLabel *labelPreIntegrationScale;
    QSpinBox *spinBoxPreIntegrationScale;

    void setupUi(QWidget *QGCPanel)
    {
        if (QGCPanel->objectName().isEmpty())
            QGCPanel->setObjectName(QString::fromUtf8("QGCPanel"));
        QGCPanel->resize(1600, 1200);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(2);
        sizePolicy.setHeightForWidth(QGCPanel->sizePolicy().hasHeightForWidth());
        QGCPanel->setSizePolicy(sizePolicy);
        QGCPanel->setMinimumSize(QSize(1600, 1200));
        QGCPanel->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(QGCPanel);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(QGCPanel);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        groupBoxVolumeRendering = new QGroupBox(splitter);
        groupBoxVolumeRendering->setObjectName(QString::fromUtf8("groupBoxVolumeRendering"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBoxVolumeRendering->sizePolicy().hasHeightForWidth());
        groupBoxVolumeRendering->setSizePolicy(sizePolicy1);
        groupBoxVolumeRendering->setMinimumSize(QSize(0, 0));
        groupBoxVolumeRendering->setMaximumSize(QSize(16777215, 16777215));
        gridLayoutVolumeRendering = new QGridLayout(groupBoxVolumeRendering);
        gridLayoutVolumeRendering->setContentsMargins(6, 6, 6, 6);
        gridLayoutVolumeRendering->setObjectName(QString::fromUtf8("gridLayoutVolumeRendering"));
        groupBoxGraphCut = new QGroupBox(groupBoxVolumeRendering);
        groupBoxGraphCut->setObjectName(QString::fromUtf8("groupBoxGraphCut"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBoxGraphCut->sizePolicy().hasHeightForWidth());
        groupBoxGraphCut->setSizePolicy(sizePolicy2);
        groupBoxGraphCut->setMinimumSize(QSize(420, 0));
        gridLayoutGraphCut = new QGridLayout(groupBoxGraphCut);
        gridLayoutGraphCut->setContentsMargins(6, 6, 6, 6);
        gridLayoutGraphCut->setObjectName(QString::fromUtf8("gridLayoutGraphCut"));
        tabWidgetBackStage = new QTabWidget(groupBoxGraphCut);
        tabWidgetBackStage->setObjectName(QString::fromUtf8("tabWidgetBackStage"));
        tabWidgetBackStage->setMinimumSize(QSize(0, 256));
        tabWidgetBackStage->setMaximumSize(QSize(16777215, 16777215));
        tabAlgorithm = new QProfile();
        tabAlgorithm->setObjectName(QString::fromUtf8("tabAlgorithm"));
        verticalLayoutAlgorithm = new QVBoxLayout(tabAlgorithm);
        verticalLayoutAlgorithm->setObjectName(QString::fromUtf8("verticalLayoutAlgorithm"));
        verticalLayoutAlgorithm->setContentsMargins(-1, 12, -1, 12);
        widgetHeightField = new QWidget(tabAlgorithm);
        widgetHeightField->setObjectName(QString::fromUtf8("widgetHeightField"));
        widgetHeightField->setMinimumSize(QSize(0, 0));
        widgetHeightField->setMaximumSize(QSize(16777215, 32));
        gridLayoutHeightField = new QGridLayout(widgetHeightField);
        gridLayoutHeightField->setContentsMargins(0, 0, 0, 0);
        gridLayoutHeightField->setObjectName(QString::fromUtf8("gridLayoutHeightField"));
        gridLayoutHeightField->setHorizontalSpacing(24);
        gridLayoutHeightField->setVerticalSpacing(0);
        labelHeightField = new QLabel(widgetHeightField);
        labelHeightField->setObjectName(QString::fromUtf8("labelHeightField"));
        labelHeightField->setMinimumSize(QSize(90, 0));
        labelHeightField->setMaximumSize(QSize(90, 16777215));
        labelHeightField->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutHeightField->addWidget(labelHeightField, 0, 0, 1, 1);

        radioButtonGlobalRelabel = new QRadioButton(widgetHeightField);
        radioButtonGlobalRelabel->setObjectName(QString::fromUtf8("radioButtonGlobalRelabel"));
        radioButtonGlobalRelabel->setMinimumSize(QSize(60, 0));
        radioButtonGlobalRelabel->setMaximumSize(QSize(60, 16777215));
        radioButtonGlobalRelabel->setLayoutDirection(Qt::LeftToRight);
        radioButtonGlobalRelabel->setChecked(false);

        gridLayoutHeightField->addWidget(radioButtonGlobalRelabel, 0, 3, 1, 1);

        horizontalSpacerHeightField = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutHeightField->addItem(horizontalSpacerHeightField, 0, 7, 1, 1);

        radioButtonNone = new QRadioButton(widgetHeightField);
        radioButtonNone->setObjectName(QString::fromUtf8("radioButtonNone"));
        radioButtonNone->setMinimumSize(QSize(60, 0));
        radioButtonNone->setMaximumSize(QSize(60, 16777215));
        radioButtonNone->setLayoutDirection(Qt::LeftToRight);
        radioButtonNone->setChecked(true);

        gridLayoutHeightField->addWidget(radioButtonNone, 0, 5, 1, 1);

        pushButtonExport = new QPushButton(widgetHeightField);
        pushButtonExport->setObjectName(QString::fromUtf8("pushButtonExport"));
        pushButtonExport->setMinimumSize(QSize(60, 0));
        pushButtonExport->setMaximumSize(QSize(60, 16777215));

        gridLayoutHeightField->addWidget(pushButtonExport, 0, 6, 1, 1);


        verticalLayoutAlgorithm->addWidget(widgetHeightField);

        widgetCutMethod = new QWidget(tabAlgorithm);
        widgetCutMethod->setObjectName(QString::fromUtf8("widgetCutMethod"));
        widgetCutMethod->setMinimumSize(QSize(0, 0));
        widgetCutMethod->setMaximumSize(QSize(16777215, 32));
        gridLayoutMethod = new QGridLayout(widgetCutMethod);
        gridLayoutMethod->setContentsMargins(0, 0, 0, 0);
        gridLayoutMethod->setObjectName(QString::fromUtf8("gridLayoutMethod"));
        gridLayoutMethod->setHorizontalSpacing(24);
        gridLayoutMethod->setVerticalSpacing(0);
        radioButtonCutMethodFastCut = new QRadioButton(widgetCutMethod);
        radioButtonCutMethodFastCut->setObjectName(QString::fromUtf8("radioButtonCutMethodFastCut"));
        radioButtonCutMethodFastCut->setMinimumSize(QSize(60, 0));
        radioButtonCutMethodFastCut->setMaximumSize(QSize(60, 16777215));
        radioButtonCutMethodFastCut->setLayoutDirection(Qt::LeftToRight);
        radioButtonCutMethodFastCut->setChecked(false);

        gridLayoutMethod->addWidget(radioButtonCutMethodFastCut, 0, 2, 1, 1);

        labelCutMethod = new QLabel(widgetCutMethod);
        labelCutMethod->setObjectName(QString::fromUtf8("labelCutMethod"));
        labelCutMethod->setMinimumSize(QSize(90, 0));
        labelCutMethod->setMaximumSize(QSize(90, 16777215));
        labelCutMethod->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutMethod->addWidget(labelCutMethod, 0, 0, 1, 1);

        horizontalSpacerCutMethod = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutMethod->addItem(horizontalSpacerCutMethod, 0, 8, 1, 1);

        radioButtonCutMethodJFCut = new QRadioButton(widgetCutMethod);
        radioButtonCutMethodJFCut->setObjectName(QString::fromUtf8("radioButtonCutMethodJFCut"));
        radioButtonCutMethodJFCut->setMinimumSize(QSize(60, 0));
        radioButtonCutMethodJFCut->setMaximumSize(QSize(60, 16777215));
        radioButtonCutMethodJFCut->setLayoutDirection(Qt::LeftToRight);
        radioButtonCutMethodJFCut->setChecked(true);

        gridLayoutMethod->addWidget(radioButtonCutMethodJFCut, 0, 1, 1, 1);

        pushButtonCutAlgorithm = new QPushButton(widgetCutMethod);
        pushButtonCutAlgorithm->setObjectName(QString::fromUtf8("pushButtonCutAlgorithm"));
        pushButtonCutAlgorithm->setMinimumSize(QSize(60, 0));
        pushButtonCutAlgorithm->setMaximumSize(QSize(60, 16777215));

        gridLayoutMethod->addWidget(pushButtonCutAlgorithm, 0, 5, 1, 1);


        verticalLayoutAlgorithm->addWidget(widgetCutMethod);

        widgetTile2D = new QWidget(tabAlgorithm);
        widgetTile2D->setObjectName(QString::fromUtf8("widgetTile2D"));
        widgetTile2D->setMinimumSize(QSize(0, 0));
        widgetTile2D->setMaximumSize(QSize(16777215, 32));
        gridLayoutTile2D = new QGridLayout(widgetTile2D);
        gridLayoutTile2D->setContentsMargins(0, 0, 0, 0);
        gridLayoutTile2D->setObjectName(QString::fromUtf8("gridLayoutTile2D"));
        gridLayoutTile2D->setHorizontalSpacing(24);
        gridLayoutTile2D->setVerticalSpacing(0);
        spinBoxTile2DY = new QSpinBox(widgetTile2D);
        spinBoxTile2DY->setObjectName(QString::fromUtf8("spinBoxTile2DY"));
        spinBoxTile2DY->setEnabled(false);
        spinBoxTile2DY->setMinimumSize(QSize(60, 0));
        spinBoxTile2DY->setMaximumSize(QSize(60, 16777215));
        spinBoxTile2DY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxTile2DY->setReadOnly(true);

        gridLayoutTile2D->addWidget(spinBoxTile2DY, 0, 2, 1, 1);

        spinBoxTile2DX = new QSpinBox(widgetTile2D);
        spinBoxTile2DX->setObjectName(QString::fromUtf8("spinBoxTile2DX"));
        spinBoxTile2DX->setEnabled(false);
        spinBoxTile2DX->setMinimumSize(QSize(60, 0));
        spinBoxTile2DX->setMaximumSize(QSize(60, 16777215));
        spinBoxTile2DX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxTile2DX->setReadOnly(true);

        gridLayoutTile2D->addWidget(spinBoxTile2DX, 0, 1, 1, 1);

        labelTile2D = new QLabel(widgetTile2D);
        labelTile2D->setObjectName(QString::fromUtf8("labelTile2D"));
        labelTile2D->setMinimumSize(QSize(90, 0));
        labelTile2D->setMaximumSize(QSize(90, 16777215));
        labelTile2D->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutTile2D->addWidget(labelTile2D, 0, 0, 1, 1);

        horizontalSpacerTile2D = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutTile2D->addItem(horizontalSpacerTile2D, 0, 5, 1, 1);


        verticalLayoutAlgorithm->addWidget(widgetTile2D);

        widgetTile3D = new QWidget(tabAlgorithm);
        widgetTile3D->setObjectName(QString::fromUtf8("widgetTile3D"));
        widgetTile3D->setMinimumSize(QSize(0, 0));
        widgetTile3D->setMaximumSize(QSize(16777215, 32));
        gridLayoutTile3D = new QGridLayout(widgetTile3D);
        gridLayoutTile3D->setContentsMargins(0, 0, 0, 0);
        gridLayoutTile3D->setObjectName(QString::fromUtf8("gridLayoutTile3D"));
        gridLayoutTile3D->setHorizontalSpacing(24);
        gridLayoutTile3D->setVerticalSpacing(0);
        horizontalSpacerTile3D = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutTile3D->addItem(horizontalSpacerTile3D, 1, 5, 1, 1);

        labelTile3D = new QLabel(widgetTile3D);
        labelTile3D->setObjectName(QString::fromUtf8("labelTile3D"));
        labelTile3D->setMinimumSize(QSize(90, 0));
        labelTile3D->setMaximumSize(QSize(90, 16777215));
        labelTile3D->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutTile3D->addWidget(labelTile3D, 1, 0, 1, 1);

        spinBoxTile3DY = new QSpinBox(widgetTile3D);
        spinBoxTile3DY->setObjectName(QString::fromUtf8("spinBoxTile3DY"));
        spinBoxTile3DY->setEnabled(false);
        spinBoxTile3DY->setMinimumSize(QSize(60, 0));
        spinBoxTile3DY->setMaximumSize(QSize(60, 16777215));
        spinBoxTile3DY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxTile3DY->setReadOnly(true);

        gridLayoutTile3D->addWidget(spinBoxTile3DY, 1, 2, 1, 1);

        spinBoxTile3DZ = new QSpinBox(widgetTile3D);
        spinBoxTile3DZ->setObjectName(QString::fromUtf8("spinBoxTile3DZ"));
        spinBoxTile3DZ->setEnabled(false);
        spinBoxTile3DZ->setMinimumSize(QSize(60, 0));
        spinBoxTile3DZ->setMaximumSize(QSize(60, 16777215));
        spinBoxTile3DZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxTile3DZ->setReadOnly(true);

        gridLayoutTile3D->addWidget(spinBoxTile3DZ, 1, 4, 1, 1);

        spinBoxTile3DX = new QSpinBox(widgetTile3D);
        spinBoxTile3DX->setObjectName(QString::fromUtf8("spinBoxTile3DX"));
        spinBoxTile3DX->setEnabled(false);
        spinBoxTile3DX->setMinimumSize(QSize(60, 0));
        spinBoxTile3DX->setMaximumSize(QSize(60, 16777215));
        spinBoxTile3DX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxTile3DX->setReadOnly(true);

        gridLayoutTile3D->addWidget(spinBoxTile3DX, 1, 1, 1, 1);


        verticalLayoutAlgorithm->addWidget(widgetTile3D);

        tabWidgetBackStage->addTab(tabAlgorithm, QString());
        tabModeling = new QProfile();
        tabModeling->setObjectName(QString::fromUtf8("tabModeling"));
        verticalLayoutModeling = new QVBoxLayout(tabModeling);
        verticalLayoutModeling->setObjectName(QString::fromUtf8("verticalLayoutModeling"));
        verticalLayoutModeling->setContentsMargins(-1, 12, -1, 12);
        widgetModeling = new QWidget(tabModeling);
        widgetModeling->setObjectName(QString::fromUtf8("widgetModeling"));
        widgetModeling->setMinimumSize(QSize(0, 0));
        widgetModeling->setMaximumSize(QSize(16777215, 32));
        gridLayoutModelingMethod = new QGridLayout(widgetModeling);
        gridLayoutModelingMethod->setObjectName(QString::fromUtf8("gridLayoutModelingMethod"));
        gridLayoutModelingMethod->setHorizontalSpacing(24);
        gridLayoutModelingMethod->setVerticalSpacing(0);
        gridLayoutModelingMethod->setContentsMargins(0, 0, 12, 0);
        labelModelingMethod = new QLabel(widgetModeling);
        labelModelingMethod->setObjectName(QString::fromUtf8("labelModelingMethod"));
        labelModelingMethod->setMinimumSize(QSize(60, 0));
        labelModelingMethod->setMaximumSize(QSize(60, 16777215));
        labelModelingMethod->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutModelingMethod->addWidget(labelModelingMethod, 0, 0, 1, 1);

        pushButtonCutModeling = new QPushButton(widgetModeling);
        pushButtonCutModeling->setObjectName(QString::fromUtf8("pushButtonCutModeling"));
        pushButtonCutModeling->setMinimumSize(QSize(60, 0));
        pushButtonCutModeling->setMaximumSize(QSize(60, 16777215));

        gridLayoutModelingMethod->addWidget(pushButtonCutModeling, 0, 8, 1, 1);

        horizontalSpacerModelingMethod = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutModelingMethod->addItem(horizontalSpacerModelingMethod, 0, 1, 1, 1);

        radioButtonBK = new QRadioButton(widgetModeling);
        radioButtonBK->setObjectName(QString::fromUtf8("radioButtonBK"));
        radioButtonBK->setMinimumSize(QSize(50, 0));
        radioButtonBK->setMaximumSize(QSize(50, 16777215));
        radioButtonBK->setLayoutDirection(Qt::LeftToRight);
        radioButtonBK->setChecked(false);

        gridLayoutModelingMethod->addWidget(radioButtonBK, 0, 3, 1, 1);

        radioButtonLazySnapping = new QRadioButton(widgetModeling);
        radioButtonLazySnapping->setObjectName(QString::fromUtf8("radioButtonLazySnapping"));
        radioButtonLazySnapping->setMinimumSize(QSize(60, 0));
        radioButtonLazySnapping->setMaximumSize(QSize(60, 16777215));
        radioButtonLazySnapping->setLayoutDirection(Qt::LeftToRight);
        radioButtonLazySnapping->setChecked(true);

        gridLayoutModelingMethod->addWidget(radioButtonLazySnapping, 0, 2, 1, 1);


        verticalLayoutModeling->addWidget(widgetModeling);

        widgetClustering = new QWidget(tabModeling);
        widgetClustering->setObjectName(QString::fromUtf8("widgetClustering"));
        widgetClustering->setMinimumSize(QSize(0, 0));
        widgetClustering->setMaximumSize(QSize(16777215, 32));
        gridLayoutClustering = new QGridLayout(widgetClustering);
        gridLayoutClustering->setObjectName(QString::fromUtf8("gridLayoutClustering"));
        gridLayoutClustering->setHorizontalSpacing(24);
        gridLayoutClustering->setVerticalSpacing(0);
        gridLayoutClustering->setContentsMargins(0, 0, 12, 0);
        labelKMeans = new QLabel(widgetClustering);
        labelKMeans->setObjectName(QString::fromUtf8("labelKMeans"));
        labelKMeans->setMinimumSize(QSize(50, 0));
        labelKMeans->setMaximumSize(QSize(50, 16777215));
        labelKMeans->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutClustering->addWidget(labelKMeans, 0, 1, 1, 1);

        labelKMeansIterations = new QLabel(widgetClustering);
        labelKMeansIterations->setObjectName(QString::fromUtf8("labelKMeansIterations"));
        labelKMeansIterations->setMinimumSize(QSize(50, 0));
        labelKMeansIterations->setMaximumSize(QSize(50, 16777215));
        labelKMeansIterations->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutClustering->addWidget(labelKMeansIterations, 0, 3, 1, 1);

        spinBoxKMeansIterations = new QSpinBox(widgetClustering);
        spinBoxKMeansIterations->setObjectName(QString::fromUtf8("spinBoxKMeansIterations"));
        spinBoxKMeansIterations->setMinimumSize(QSize(60, 0));
        spinBoxKMeansIterations->setMaximumSize(QSize(60, 16777215));
        spinBoxKMeansIterations->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxKMeansIterations->setMinimum(1);
        spinBoxKMeansIterations->setMaximum(256);
        spinBoxKMeansIterations->setSingleStep(16);
        spinBoxKMeansIterations->setValue(32);

        gridLayoutClustering->addWidget(spinBoxKMeansIterations, 0, 4, 1, 1);

        labelClustering = new QLabel(widgetClustering);
        labelClustering->setObjectName(QString::fromUtf8("labelClustering"));
        labelClustering->setMinimumSize(QSize(60, 0));
        labelClustering->setMaximumSize(QSize(60, 16777215));
        labelClustering->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutClustering->addWidget(labelClustering, 0, 0, 1, 1);

        spinBoxK = new QSpinBox(widgetClustering);
        spinBoxK->setObjectName(QString::fromUtf8("spinBoxK"));
        spinBoxK->setMinimumSize(QSize(60, 0));
        spinBoxK->setMaximumSize(QSize(60, 16777215));
        spinBoxK->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxK->setMinimum(2);
        spinBoxK->setMaximum(32);
        spinBoxK->setValue(8);

        gridLayoutClustering->addWidget(spinBoxK, 0, 2, 1, 1);


        verticalLayoutModeling->addWidget(widgetClustering);

        widgetLazyCapacity = new QWidget(tabModeling);
        widgetLazyCapacity->setObjectName(QString::fromUtf8("widgetLazyCapacity"));
        widgetLazyCapacity->setMinimumSize(QSize(0, 0));
        widgetLazyCapacity->setMaximumSize(QSize(16777215, 32));
        gridLayoutLazyCapacity = new QGridLayout(widgetLazyCapacity);
        gridLayoutLazyCapacity->setObjectName(QString::fromUtf8("gridLayoutLazyCapacity"));
        gridLayoutLazyCapacity->setHorizontalSpacing(24);
        gridLayoutLazyCapacity->setVerticalSpacing(0);
        gridLayoutLazyCapacity->setContentsMargins(0, 0, 12, 0);
        doubleSpinBoxLazyTerminal = new QDoubleSpinBox(widgetLazyCapacity);
        doubleSpinBoxLazyTerminal->setObjectName(QString::fromUtf8("doubleSpinBoxLazyTerminal"));
        doubleSpinBoxLazyTerminal->setMinimumSize(QSize(60, 0));
        doubleSpinBoxLazyTerminal->setMaximumSize(QSize(60, 16777215));
        doubleSpinBoxLazyTerminal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxLazyTerminal->setDecimals(2);
        doubleSpinBoxLazyTerminal->setMinimum(0);
        doubleSpinBoxLazyTerminal->setMaximum(256);
        doubleSpinBoxLazyTerminal->setSingleStep(25);
        doubleSpinBoxLazyTerminal->setValue(1);

        gridLayoutLazyCapacity->addWidget(doubleSpinBoxLazyTerminal, 0, 2, 1, 1);

        labelLazyTerminal = new QLabel(widgetLazyCapacity);
        labelLazyTerminal->setObjectName(QString::fromUtf8("labelLazyTerminal"));
        labelLazyTerminal->setMinimumSize(QSize(50, 0));
        labelLazyTerminal->setMaximumSize(QSize(50, 16777215));
        labelLazyTerminal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutLazyCapacity->addWidget(labelLazyTerminal, 0, 1, 1, 1);

        labelLazyNeighbor = new QLabel(widgetLazyCapacity);
        labelLazyNeighbor->setObjectName(QString::fromUtf8("labelLazyNeighbor"));
        labelLazyNeighbor->setMinimumSize(QSize(50, 0));
        labelLazyNeighbor->setMaximumSize(QSize(50, 16777215));
        labelLazyNeighbor->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutLazyCapacity->addWidget(labelLazyNeighbor, 0, 3, 1, 1);

        labelLazyCapacity = new QLabel(widgetLazyCapacity);
        labelLazyCapacity->setObjectName(QString::fromUtf8("labelLazyCapacity"));
        labelLazyCapacity->setMinimumSize(QSize(60, 0));
        labelLazyCapacity->setMaximumSize(QSize(60, 16777215));
        labelLazyCapacity->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutLazyCapacity->addWidget(labelLazyCapacity, 0, 0, 1, 1);

        doubleSpinBoxLazyNeighbor = new QDoubleSpinBox(widgetLazyCapacity);
        doubleSpinBoxLazyNeighbor->setObjectName(QString::fromUtf8("doubleSpinBoxLazyNeighbor"));
        doubleSpinBoxLazyNeighbor->setMinimumSize(QSize(60, 0));
        doubleSpinBoxLazyNeighbor->setMaximumSize(QSize(60, 16777215));
        doubleSpinBoxLazyNeighbor->setFrame(true);
        doubleSpinBoxLazyNeighbor->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxLazyNeighbor->setDecimals(2);
        doubleSpinBoxLazyNeighbor->setMinimum(0.01);
        doubleSpinBoxLazyNeighbor->setMaximum(256);
        doubleSpinBoxLazyNeighbor->setSingleStep(25);
        doubleSpinBoxLazyNeighbor->setValue(1);

        gridLayoutLazyCapacity->addWidget(doubleSpinBoxLazyNeighbor, 0, 4, 1, 1);


        verticalLayoutModeling->addWidget(widgetLazyCapacity);

        widgetBKCapacity = new QWidget(tabModeling);
        widgetBKCapacity->setObjectName(QString::fromUtf8("widgetBKCapacity"));
        widgetBKCapacity->setMinimumSize(QSize(0, 0));
        widgetBKCapacity->setMaximumSize(QSize(16777215, 32));
        gridLayoutLazyCapacity_2 = new QGridLayout(widgetBKCapacity);
        gridLayoutLazyCapacity_2->setObjectName(QString::fromUtf8("gridLayoutLazyCapacity_2"));
        gridLayoutLazyCapacity_2->setHorizontalSpacing(24);
        gridLayoutLazyCapacity_2->setVerticalSpacing(0);
        gridLayoutLazyCapacity_2->setContentsMargins(0, 0, 12, 0);
        labelBKCapacity = new QLabel(widgetBKCapacity);
        labelBKCapacity->setObjectName(QString::fromUtf8("labelBKCapacity"));
        labelBKCapacity->setMinimumSize(QSize(60, 0));
        labelBKCapacity->setMaximumSize(QSize(60, 16777215));
        labelBKCapacity->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutLazyCapacity_2->addWidget(labelBKCapacity, 0, 0, 1, 1);

        labelBKNeighbor = new QLabel(widgetBKCapacity);
        labelBKNeighbor->setObjectName(QString::fromUtf8("labelBKNeighbor"));
        labelBKNeighbor->setMinimumSize(QSize(50, 0));
        labelBKNeighbor->setMaximumSize(QSize(50, 16777215));
        labelBKNeighbor->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutLazyCapacity_2->addWidget(labelBKNeighbor, 0, 4, 1, 1);

        labelBKTerminal = new QLabel(widgetBKCapacity);
        labelBKTerminal->setObjectName(QString::fromUtf8("labelBKTerminal"));
        labelBKTerminal->setMinimumSize(QSize(50, 0));
        labelBKTerminal->setMaximumSize(QSize(50, 16777215));
        labelBKTerminal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutLazyCapacity_2->addWidget(labelBKTerminal, 0, 1, 1, 1);

        doubleSpinBoxBKTerminal = new QDoubleSpinBox(widgetBKCapacity);
        doubleSpinBoxBKTerminal->setObjectName(QString::fromUtf8("doubleSpinBoxBKTerminal"));
        doubleSpinBoxBKTerminal->setMinimumSize(QSize(60, 0));
        doubleSpinBoxBKTerminal->setMaximumSize(QSize(60, 16777215));
        doubleSpinBoxBKTerminal->setFrame(true);
        doubleSpinBoxBKTerminal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxBKTerminal->setDecimals(2);
        doubleSpinBoxBKTerminal->setMinimum(0);
        doubleSpinBoxBKTerminal->setMaximum(256);
        doubleSpinBoxBKTerminal->setSingleStep(25);
        doubleSpinBoxBKTerminal->setValue(0);

        gridLayoutLazyCapacity_2->addWidget(doubleSpinBoxBKTerminal, 0, 2, 1, 1);

        doubleSpinBoxBKNeighbor = new QDoubleSpinBox(widgetBKCapacity);
        doubleSpinBoxBKNeighbor->setObjectName(QString::fromUtf8("doubleSpinBoxBKNeighbor"));
        doubleSpinBoxBKNeighbor->setMinimumSize(QSize(60, 0));
        doubleSpinBoxBKNeighbor->setMaximumSize(QSize(60, 16777215));
        doubleSpinBoxBKNeighbor->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxBKNeighbor->setDecimals(4);
        doubleSpinBoxBKNeighbor->setMinimum(0.0001);
        doubleSpinBoxBKNeighbor->setMaximum(1);
        doubleSpinBoxBKNeighbor->setSingleStep(0.05);
        doubleSpinBoxBKNeighbor->setValue(0.002);

        gridLayoutLazyCapacity_2->addWidget(doubleSpinBoxBKNeighbor, 0, 5, 1, 1);


        verticalLayoutModeling->addWidget(widgetBKCapacity);

        tabWidgetBackStage->addTab(tabModeling, QString());
        tabConvergence = new QProfile();
        tabConvergence->setObjectName(QString::fromUtf8("tabConvergence"));
        verticalLayoutConvergence = new QVBoxLayout(tabConvergence);
        verticalLayoutConvergence->setObjectName(QString::fromUtf8("verticalLayoutConvergence"));
        verticalLayoutConvergence->setContentsMargins(-1, 12, -1, 12);
        widgetLaunch = new QWidget(tabConvergence);
        widgetLaunch->setObjectName(QString::fromUtf8("widgetLaunch"));
        widgetLaunch->setMinimumSize(QSize(0, 0));
        widgetLaunch->setMaximumSize(QSize(16777215, 32));
        gridLayoutLaunch = new QGridLayout(widgetLaunch);
        gridLayoutLaunch->setObjectName(QString::fromUtf8("gridLayoutLaunch"));
        gridLayoutLaunch->setHorizontalSpacing(24);
        gridLayoutLaunch->setVerticalSpacing(0);
        gridLayoutLaunch->setContentsMargins(0, 0, 12, 0);
        checkBoxPrint = new QCheckBox(widgetLaunch);
        checkBoxPrint->setObjectName(QString::fromUtf8("checkBoxPrint"));
        checkBoxPrint->setMinimumSize(QSize(60, 0));
        checkBoxPrint->setMaximumSize(QSize(60, 16777215));
        checkBoxPrint->setLayoutDirection(Qt::RightToLeft);
        checkBoxPrint->setChecked(false);

        gridLayoutLaunch->addWidget(checkBoxPrint, 0, 3, 1, 1);

        pushButtonCut = new QPushButton(widgetLaunch);
        pushButtonCut->setObjectName(QString::fromUtf8("pushButtonCut"));
        pushButtonCut->setMinimumSize(QSize(60, 0));
        pushButtonCut->setMaximumSize(QSize(60, 16777215));

        gridLayoutLaunch->addWidget(pushButtonCut, 0, 5, 1, 1);

        labelLaunch = new QLabel(widgetLaunch);
        labelLaunch->setObjectName(QString::fromUtf8("labelLaunch"));
        labelLaunch->setMinimumSize(QSize(60, 0));
        labelLaunch->setMaximumSize(QSize(60, 16777215));
        labelLaunch->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutLaunch->addWidget(labelLaunch, 0, 0, 1, 1);

        checkBoxEnergy = new QCheckBox(widgetLaunch);
        checkBoxEnergy->setObjectName(QString::fromUtf8("checkBoxEnergy"));
        checkBoxEnergy->setMinimumSize(QSize(60, 0));
        checkBoxEnergy->setMaximumSize(QSize(60, 16777215));
        checkBoxEnergy->setLayoutDirection(Qt::RightToLeft);

        gridLayoutLaunch->addWidget(checkBoxEnergy, 0, 2, 1, 1);

        checkBoxComputeTag = new QCheckBox(widgetLaunch);
        checkBoxComputeTag->setObjectName(QString::fromUtf8("checkBoxComputeTag"));
        checkBoxComputeTag->setMinimumSize(QSize(45, 0));
        checkBoxComputeTag->setMaximumSize(QSize(45, 16777215));
        checkBoxComputeTag->setLayoutDirection(Qt::RightToLeft);
        checkBoxComputeTag->setChecked(false);

        gridLayoutLaunch->addWidget(checkBoxComputeTag, 0, 4, 1, 1);


        verticalLayoutConvergence->addWidget(widgetLaunch);

        widgetUpdate = new QWidget(tabConvergence);
        widgetUpdate->setObjectName(QString::fromUtf8("widgetUpdate"));
        widgetUpdate->setMinimumSize(QSize(0, 0));
        widgetUpdate->setMaximumSize(QSize(16777215, 32));
        gridLayoutUpdate = new QGridLayout(widgetUpdate);
        gridLayoutUpdate->setObjectName(QString::fromUtf8("gridLayoutUpdate"));
        gridLayoutUpdate->setHorizontalSpacing(24);
        gridLayoutUpdate->setVerticalSpacing(0);
        gridLayoutUpdate->setContentsMargins(0, 0, 12, 0);
        spinBoxCountIterations = new QSpinBox(widgetUpdate);
        spinBoxCountIterations->setObjectName(QString::fromUtf8("spinBoxCountIterations"));
        spinBoxCountIterations->setMinimumSize(QSize(60, 0));
        spinBoxCountIterations->setMaximumSize(QSize(60, 16777215));
        spinBoxCountIterations->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxCountIterations->setMinimum(1);
        spinBoxCountIterations->setMaximum(65536);
        spinBoxCountIterations->setSingleStep(256);
        spinBoxCountIterations->setValue(4);

        gridLayoutUpdate->addWidget(spinBoxCountIterations, 0, 4, 1, 1);

        labelUpdate = new QLabel(widgetUpdate);
        labelUpdate->setObjectName(QString::fromUtf8("labelUpdate"));
        labelUpdate->setMinimumSize(QSize(60, 0));
        labelUpdate->setMaximumSize(QSize(60, 16777215));
        labelUpdate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutUpdate->addWidget(labelUpdate, 0, 0, 1, 1);

        labelCountIterations = new QLabel(widgetUpdate);
        labelCountIterations->setObjectName(QString::fromUtf8("labelCountIterations"));
        labelCountIterations->setMinimumSize(QSize(60, 0));
        labelCountIterations->setMaximumSize(QSize(60, 16777215));
        labelCountIterations->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutUpdate->addWidget(labelCountIterations, 0, 3, 1, 1);

        labelCutIterations = new QLabel(widgetUpdate);
        labelCutIterations->setObjectName(QString::fromUtf8("labelCutIterations"));
        labelCutIterations->setMinimumSize(QSize(45, 0));
        labelCutIterations->setMaximumSize(QSize(45, 16777215));
        labelCutIterations->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutUpdate->addWidget(labelCutIterations, 0, 5, 1, 1);

        spinBoxCutIterations = new QSpinBox(widgetUpdate);
        spinBoxCutIterations->setObjectName(QString::fromUtf8("spinBoxCutIterations"));
        spinBoxCutIterations->setMinimumSize(QSize(60, 0));
        spinBoxCutIterations->setMaximumSize(QSize(60, 16777215));
        spinBoxCutIterations->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxCutIterations->setMinimum(1);
        spinBoxCutIterations->setMaximum(65535);
        spinBoxCutIterations->setSingleStep(256);
        spinBoxCutIterations->setValue(8);

        gridLayoutUpdate->addWidget(spinBoxCutIterations, 0, 6, 1, 1);


        verticalLayoutConvergence->addWidget(widgetUpdate);

        widgetOther = new QWidget(tabConvergence);
        widgetOther->setObjectName(QString::fromUtf8("widgetOther"));
        widgetOther->setMinimumSize(QSize(0, 0));
        widgetOther->setMaximumSize(QSize(16777215, 32));
        gridLayoutUpdate_2 = new QGridLayout(widgetOther);
        gridLayoutUpdate_2->setObjectName(QString::fromUtf8("gridLayoutUpdate_2"));
        gridLayoutUpdate_2->setHorizontalSpacing(24);
        gridLayoutUpdate_2->setVerticalSpacing(0);
        gridLayoutUpdate_2->setContentsMargins(0, 0, 12, 0);
        spinBoxTotalIterations = new QSpinBox(widgetOther);
        spinBoxTotalIterations->setObjectName(QString::fromUtf8("spinBoxTotalIterations"));
        spinBoxTotalIterations->setMinimumSize(QSize(60, 0));
        spinBoxTotalIterations->setMaximumSize(QSize(60, 16777215));
        spinBoxTotalIterations->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxTotalIterations->setMinimum(1);
        spinBoxTotalIterations->setMaximum(65536);
        spinBoxTotalIterations->setSingleStep(1024);
        spinBoxTotalIterations->setValue(256);

        gridLayoutUpdate_2->addWidget(spinBoxTotalIterations, 0, 4, 1, 1);

        labelOther = new QLabel(widgetOther);
        labelOther->setObjectName(QString::fromUtf8("labelOther"));
        labelOther->setMinimumSize(QSize(60, 0));
        labelOther->setMaximumSize(QSize(60, 16777215));
        labelOther->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutUpdate_2->addWidget(labelOther, 0, 0, 1, 1);

        labelTotalIterations = new QLabel(widgetOther);
        labelTotalIterations->setObjectName(QString::fromUtf8("labelTotalIterations"));
        labelTotalIterations->setMinimumSize(QSize(60, 0));
        labelTotalIterations->setMaximumSize(QSize(60, 16777215));
        labelTotalIterations->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutUpdate_2->addWidget(labelTotalIterations, 0, 3, 1, 1);

        labelPrintIterations = new QLabel(widgetOther);
        labelPrintIterations->setObjectName(QString::fromUtf8("labelPrintIterations"));
        labelPrintIterations->setMinimumSize(QSize(45, 0));
        labelPrintIterations->setMaximumSize(QSize(45, 16777215));
        labelPrintIterations->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutUpdate_2->addWidget(labelPrintIterations, 0, 5, 1, 1);

        spinBoxPrintIterations = new QSpinBox(widgetOther);
        spinBoxPrintIterations->setObjectName(QString::fromUtf8("spinBoxPrintIterations"));
        spinBoxPrintIterations->setMinimumSize(QSize(60, 0));
        spinBoxPrintIterations->setMaximumSize(QSize(60, 16777215));
        spinBoxPrintIterations->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxPrintIterations->setMinimum(1);
        spinBoxPrintIterations->setMaximum(65535);
        spinBoxPrintIterations->setSingleStep(256);
        spinBoxPrintIterations->setValue(64);

        gridLayoutUpdate_2->addWidget(spinBoxPrintIterations, 0, 6, 1, 1);


        verticalLayoutConvergence->addWidget(widgetOther);

        tabWidgetBackStage->addTab(tabConvergence, QString());
        tabFeature = new QProfile();
        tabFeature->setObjectName(QString::fromUtf8("tabFeature"));
        verticalLayoutFeature = new QVBoxLayout(tabFeature);
        verticalLayoutFeature->setObjectName(QString::fromUtf8("verticalLayoutFeature"));
        verticalLayoutFeature->setContentsMargins(-1, 12, -1, 12);
        widgetWeight = new QWidget(tabFeature);
        widgetWeight->setObjectName(QString::fromUtf8("widgetWeight"));
        widgetWeight->setMinimumSize(QSize(0, 0));
        widgetWeight->setMaximumSize(QSize(16777215, 76));
        gridLayoutWeight = new QGridLayout(widgetWeight);
        gridLayoutWeight->setObjectName(QString::fromUtf8("gridLayoutWeight"));
        gridLayoutWeight->setHorizontalSpacing(24);
        gridLayoutWeight->setVerticalSpacing(0);
        gridLayoutWeight->setContentsMargins(0, 0, 12, 0);
        doubleSpinBoxWeightX = new QDoubleSpinBox(widgetWeight);
        doubleSpinBoxWeightX->setObjectName(QString::fromUtf8("doubleSpinBoxWeightX"));
        doubleSpinBoxWeightX->setMinimumSize(QSize(60, 0));
        doubleSpinBoxWeightX->setMaximumSize(QSize(60, 16777215));
        doubleSpinBoxWeightX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxWeightX->setDecimals(4);
        doubleSpinBoxWeightX->setMinimum(0);
        doubleSpinBoxWeightX->setMaximum(1);
        doubleSpinBoxWeightX->setSingleStep(0.05);
        doubleSpinBoxWeightX->setValue(0.2126);

        gridLayoutWeight->addWidget(doubleSpinBoxWeightX, 0, 2, 1, 1);

        doubleSpinBoxWeightY = new QDoubleSpinBox(widgetWeight);
        doubleSpinBoxWeightY->setObjectName(QString::fromUtf8("doubleSpinBoxWeightY"));
        doubleSpinBoxWeightY->setMinimumSize(QSize(60, 0));
        doubleSpinBoxWeightY->setMaximumSize(QSize(60, 16777215));
        doubleSpinBoxWeightY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxWeightY->setDecimals(4);
        doubleSpinBoxWeightY->setMinimum(0);
        doubleSpinBoxWeightY->setMaximum(1);
        doubleSpinBoxWeightY->setSingleStep(0.05);
        doubleSpinBoxWeightY->setValue(0.7152);

        gridLayoutWeight->addWidget(doubleSpinBoxWeightY, 0, 4, 1, 1);

        labelWeight = new QLabel(widgetWeight);
        labelWeight->setObjectName(QString::fromUtf8("labelWeight"));
        labelWeight->setMinimumSize(QSize(60, 0));
        labelWeight->setMaximumSize(QSize(60, 16777215));
        labelWeight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutWeight->addWidget(labelWeight, 0, 0, 2, 1);

        doubleSpinBoxWeightW = new QDoubleSpinBox(widgetWeight);
        doubleSpinBoxWeightW->setObjectName(QString::fromUtf8("doubleSpinBoxWeightW"));
        doubleSpinBoxWeightW->setMinimumSize(QSize(60, 0));
        doubleSpinBoxWeightW->setMaximumSize(QSize(60, 16777215));
        doubleSpinBoxWeightW->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxWeightW->setDecimals(4);
        doubleSpinBoxWeightW->setMinimum(0);
        doubleSpinBoxWeightW->setMaximum(1);
        doubleSpinBoxWeightW->setSingleStep(0.05);
        doubleSpinBoxWeightW->setValue(0);

        gridLayoutWeight->addWidget(doubleSpinBoxWeightW, 1, 4, 1, 1);

        labelWeightZ = new QLabel(widgetWeight);
        labelWeightZ->setObjectName(QString::fromUtf8("labelWeightZ"));
        labelWeightZ->setMinimumSize(QSize(12, 0));
        labelWeightZ->setMaximumSize(QSize(12, 16777215));
        labelWeightZ->setAlignment(Qt::AlignCenter);

        gridLayoutWeight->addWidget(labelWeightZ, 1, 1, 1, 1);

        labelWeightW = new QLabel(widgetWeight);
        labelWeightW->setObjectName(QString::fromUtf8("labelWeightW"));
        labelWeightW->setMinimumSize(QSize(12, 0));
        labelWeightW->setMaximumSize(QSize(12, 16777215));
        labelWeightW->setAlignment(Qt::AlignCenter);

        gridLayoutWeight->addWidget(labelWeightW, 1, 3, 1, 1);

        labelWeightX = new QLabel(widgetWeight);
        labelWeightX->setObjectName(QString::fromUtf8("labelWeightX"));
        labelWeightX->setMinimumSize(QSize(12, 0));
        labelWeightX->setMaximumSize(QSize(12, 16777215));
        labelWeightX->setAlignment(Qt::AlignCenter);

        gridLayoutWeight->addWidget(labelWeightX, 0, 1, 1, 1);

        labelWeightY = new QLabel(widgetWeight);
        labelWeightY->setObjectName(QString::fromUtf8("labelWeightY"));
        labelWeightY->setMinimumSize(QSize(12, 0));
        labelWeightY->setMaximumSize(QSize(12, 16777215));
        labelWeightY->setAlignment(Qt::AlignCenter);

        gridLayoutWeight->addWidget(labelWeightY, 0, 3, 1, 1);

        doubleSpinBoxWeightZ = new QDoubleSpinBox(widgetWeight);
        doubleSpinBoxWeightZ->setObjectName(QString::fromUtf8("doubleSpinBoxWeightZ"));
        doubleSpinBoxWeightZ->setMinimumSize(QSize(60, 0));
        doubleSpinBoxWeightZ->setMaximumSize(QSize(60, 16777215));
        doubleSpinBoxWeightZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxWeightZ->setDecimals(4);
        doubleSpinBoxWeightZ->setMinimum(0);
        doubleSpinBoxWeightZ->setMaximum(1);
        doubleSpinBoxWeightZ->setSingleStep(0.05);
        doubleSpinBoxWeightZ->setValue(0.0722);

        gridLayoutWeight->addWidget(doubleSpinBoxWeightZ, 1, 2, 1, 1);

        horizontalSpacerWeight = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutWeight->addItem(horizontalSpacerWeight, 0, 5, 2, 1);


        verticalLayoutFeature->addWidget(widgetWeight);

        tabWidgetBackStage->addTab(tabFeature, QString());
        tabOpenCL = new QProfile();
        tabOpenCL->setObjectName(QString::fromUtf8("tabOpenCL"));
        verticalLayoutOpenCL = new QVBoxLayout(tabOpenCL);
        verticalLayoutOpenCL->setObjectName(QString::fromUtf8("verticalLayoutOpenCL"));
        verticalLayoutOpenCL->setContentsMargins(-1, 12, -1, 12);
        widgetMaxGroup = new QWidget(tabOpenCL);
        widgetMaxGroup->setObjectName(QString::fromUtf8("widgetMaxGroup"));
        widgetMaxGroup->setMinimumSize(QSize(0, 0));
        widgetMaxGroup->setMaximumSize(QSize(16777215, 32));
        gridLayoutMaxGroup = new QGridLayout(widgetMaxGroup);
        gridLayoutMaxGroup->setContentsMargins(0, 0, 0, 0);
        gridLayoutMaxGroup->setObjectName(QString::fromUtf8("gridLayoutMaxGroup"));
        gridLayoutMaxGroup->setHorizontalSpacing(24);
        gridLayoutMaxGroup->setVerticalSpacing(0);
        horizontalSpacerMaxGroup = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutMaxGroup->addItem(horizontalSpacerMaxGroup, 0, 4, 1, 1);

        labelMaxGroup = new QLabel(widgetMaxGroup);
        labelMaxGroup->setObjectName(QString::fromUtf8("labelMaxGroup"));
        labelMaxGroup->setMinimumSize(QSize(75, 0));
        labelMaxGroup->setMaximumSize(QSize(75, 16777215));
        labelMaxGroup->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutMaxGroup->addWidget(labelMaxGroup, 0, 0, 1, 1);

        spinBoxMaxGroup = new QSpinBox(widgetMaxGroup);
        spinBoxMaxGroup->setObjectName(QString::fromUtf8("spinBoxMaxGroup"));
        spinBoxMaxGroup->setEnabled(false);
        spinBoxMaxGroup->setMinimumSize(QSize(60, 0));
        spinBoxMaxGroup->setMaximumSize(QSize(60, 16777215));
        spinBoxMaxGroup->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutMaxGroup->addWidget(spinBoxMaxGroup, 0, 1, 1, 1);


        verticalLayoutOpenCL->addWidget(widgetMaxGroup);

        widgetLocal1D = new QWidget(tabOpenCL);
        widgetLocal1D->setObjectName(QString::fromUtf8("widgetLocal1D"));
        widgetLocal1D->setMinimumSize(QSize(0, 0));
        widgetLocal1D->setMaximumSize(QSize(16777215, 32));
        gridLayoutLocal1D = new QGridLayout(widgetLocal1D);
        gridLayoutLocal1D->setContentsMargins(0, 0, 0, 0);
        gridLayoutLocal1D->setObjectName(QString::fromUtf8("gridLayoutLocal1D"));
        gridLayoutLocal1D->setHorizontalSpacing(24);
        gridLayoutLocal1D->setVerticalSpacing(0);
        labelLocalSize1DX = new QLabel(widgetLocal1D);
        labelLocalSize1DX->setObjectName(QString::fromUtf8("labelLocalSize1DX"));
        labelLocalSize1DX->setMinimumSize(QSize(75, 0));
        labelLocalSize1DX->setMaximumSize(QSize(75, 16777215));
        labelLocalSize1DX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutLocal1D->addWidget(labelLocalSize1DX, 0, 0, 1, 1);

        horizontalSpacerLocal1D = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutLocal1D->addItem(horizontalSpacerLocal1D, 0, 4, 1, 1);

        spinBoxLocalSize1DX = new QSpinBox(widgetLocal1D);
        spinBoxLocalSize1DX->setObjectName(QString::fromUtf8("spinBoxLocalSize1DX"));
        spinBoxLocalSize1DX->setMinimumSize(QSize(60, 0));
        spinBoxLocalSize1DX->setMaximumSize(QSize(60, 16777215));
        spinBoxLocalSize1DX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxLocalSize1DX->setMinimum(1);
        spinBoxLocalSize1DX->setMaximum(1024);
        spinBoxLocalSize1DX->setValue(256);

        gridLayoutLocal1D->addWidget(spinBoxLocalSize1DX, 0, 1, 1, 1);


        verticalLayoutOpenCL->addWidget(widgetLocal1D);

        widgetLocal2D = new QWidget(tabOpenCL);
        widgetLocal2D->setObjectName(QString::fromUtf8("widgetLocal2D"));
        widgetLocal2D->setMinimumSize(QSize(0, 0));
        widgetLocal2D->setMaximumSize(QSize(16777215, 32));
        gridLayoutLocal2D = new QGridLayout(widgetLocal2D);
        gridLayoutLocal2D->setContentsMargins(0, 0, 0, 0);
        gridLayoutLocal2D->setObjectName(QString::fromUtf8("gridLayoutLocal2D"));
        gridLayoutLocal2D->setHorizontalSpacing(24);
        gridLayoutLocal2D->setVerticalSpacing(0);
        horizontalSpacerLocal2D = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutLocal2D->addItem(horizontalSpacerLocal2D, 0, 4, 1, 1);

        labelLocalSize2D = new QLabel(widgetLocal2D);
        labelLocalSize2D->setObjectName(QString::fromUtf8("labelLocalSize2D"));
        labelLocalSize2D->setMinimumSize(QSize(75, 0));
        labelLocalSize2D->setMaximumSize(QSize(75, 16777215));
        labelLocalSize2D->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutLocal2D->addWidget(labelLocalSize2D, 0, 0, 1, 1);

        spinBoxLocalSize2DX = new QSpinBox(widgetLocal2D);
        spinBoxLocalSize2DX->setObjectName(QString::fromUtf8("spinBoxLocalSize2DX"));
        spinBoxLocalSize2DX->setMinimumSize(QSize(60, 0));
        spinBoxLocalSize2DX->setMaximumSize(QSize(60, 16777215));
        spinBoxLocalSize2DX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxLocalSize2DX->setMinimum(1);
        spinBoxLocalSize2DX->setMaximum(1024);
        spinBoxLocalSize2DX->setValue(32);

        gridLayoutLocal2D->addWidget(spinBoxLocalSize2DX, 0, 1, 1, 1);

        spinBoxLocalSize2DY = new QSpinBox(widgetLocal2D);
        spinBoxLocalSize2DY->setObjectName(QString::fromUtf8("spinBoxLocalSize2DY"));
        spinBoxLocalSize2DY->setMinimumSize(QSize(60, 0));
        spinBoxLocalSize2DY->setMaximumSize(QSize(60, 16777215));
        spinBoxLocalSize2DY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxLocalSize2DY->setMinimum(1);
        spinBoxLocalSize2DY->setMaximum(1024);
        spinBoxLocalSize2DY->setValue(2);

        gridLayoutLocal2D->addWidget(spinBoxLocalSize2DY, 0, 2, 1, 1);


        verticalLayoutOpenCL->addWidget(widgetLocal2D);

        widgetLocal3D = new QWidget(tabOpenCL);
        widgetLocal3D->setObjectName(QString::fromUtf8("widgetLocal3D"));
        widgetLocal3D->setMinimumSize(QSize(0, 0));
        widgetLocal3D->setMaximumSize(QSize(16777215, 32));
        gridLayoutLocal3D = new QGridLayout(widgetLocal3D);
        gridLayoutLocal3D->setContentsMargins(0, 0, 0, 0);
        gridLayoutLocal3D->setObjectName(QString::fromUtf8("gridLayoutLocal3D"));
        gridLayoutLocal3D->setHorizontalSpacing(24);
        gridLayoutLocal3D->setVerticalSpacing(0);
        spinBoxLocalSize3DY = new QSpinBox(widgetLocal3D);
        spinBoxLocalSize3DY->setObjectName(QString::fromUtf8("spinBoxLocalSize3DY"));
        spinBoxLocalSize3DY->setMinimumSize(QSize(60, 0));
        spinBoxLocalSize3DY->setMaximumSize(QSize(60, 16777215));
        spinBoxLocalSize3DY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxLocalSize3DY->setMinimum(1);
        spinBoxLocalSize3DY->setMaximum(1024);
        spinBoxLocalSize3DY->setValue(8);

        gridLayoutLocal3D->addWidget(spinBoxLocalSize3DY, 0, 2, 1, 1);

        horizontalSpacerLocal3D = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutLocal3D->addItem(horizontalSpacerLocal3D, 0, 4, 1, 1);

        labelLocalSize3D = new QLabel(widgetLocal3D);
        labelLocalSize3D->setObjectName(QString::fromUtf8("labelLocalSize3D"));
        labelLocalSize3D->setMinimumSize(QSize(75, 0));
        labelLocalSize3D->setMaximumSize(QSize(75, 16777215));
        labelLocalSize3D->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutLocal3D->addWidget(labelLocalSize3D, 0, 0, 1, 1);

        spinBoxLocalSize3DX = new QSpinBox(widgetLocal3D);
        spinBoxLocalSize3DX->setObjectName(QString::fromUtf8("spinBoxLocalSize3DX"));
        spinBoxLocalSize3DX->setMinimumSize(QSize(60, 0));
        spinBoxLocalSize3DX->setMaximumSize(QSize(60, 16777215));
        spinBoxLocalSize3DX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxLocalSize3DX->setMinimum(1);
        spinBoxLocalSize3DX->setMaximum(1024);
        spinBoxLocalSize3DX->setValue(32);

        gridLayoutLocal3D->addWidget(spinBoxLocalSize3DX, 0, 1, 1, 1);

        spinBoxLocalSize3DZ = new QSpinBox(widgetLocal3D);
        spinBoxLocalSize3DZ->setObjectName(QString::fromUtf8("spinBoxLocalSize3DZ"));
        spinBoxLocalSize3DZ->setMinimumSize(QSize(60, 0));
        spinBoxLocalSize3DZ->setMaximumSize(QSize(60, 16777215));
        spinBoxLocalSize3DZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxLocalSize3DZ->setMinimum(1);
        spinBoxLocalSize3DZ->setMaximum(1024);

        gridLayoutLocal3D->addWidget(spinBoxLocalSize3DZ, 0, 3, 1, 1);


        verticalLayoutOpenCL->addWidget(widgetLocal3D);

        tabWidgetBackStage->addTab(tabOpenCL, QString());

        gridLayoutGraphCut->addWidget(tabWidgetBackStage, 2, 1, 1, 1);

        tabWidgetFrontStage = new QTabWidget(groupBoxGraphCut);
        tabWidgetFrontStage->setObjectName(QString::fromUtf8("tabWidgetFrontStage"));
        tabWidgetFrontStage->setMinimumSize(QSize(0, 256));
        tabWidgetFrontStage->setMaximumSize(QSize(16777215, 16777215));
        tabBrushing = new QProfile();
        tabBrushing->setObjectName(QString::fromUtf8("tabBrushing"));
        verticalLayoutBrushing = new QVBoxLayout(tabBrushing);
        verticalLayoutBrushing->setSpacing(9);
        verticalLayoutBrushing->setObjectName(QString::fromUtf8("verticalLayoutBrushing"));
        verticalLayoutBrushing->setContentsMargins(-1, 12, -1, 12);
        widgetBrushingOpacity = new QWidget(tabBrushing);
        widgetBrushingOpacity->setObjectName(QString::fromUtf8("widgetBrushingOpacity"));
        widgetBrushingOpacity->setMinimumSize(QSize(0, 0));
        widgetBrushingOpacity->setMaximumSize(QSize(16777215, 32));
        gridLayoutBrushingOpacity = new QGridLayout(widgetBrushingOpacity);
        gridLayoutBrushingOpacity->setObjectName(QString::fromUtf8("gridLayoutBrushingOpacity"));
        gridLayoutBrushingOpacity->setHorizontalSpacing(24);
        gridLayoutBrushingOpacity->setVerticalSpacing(0);
        gridLayoutBrushingOpacity->setContentsMargins(0, 0, 12, 0);
        labelOpacity = new QLabel(widgetBrushingOpacity);
        labelOpacity->setObjectName(QString::fromUtf8("labelOpacity"));
        labelOpacity->setMinimumSize(QSize(60, 0));
        labelOpacity->setMaximumSize(QSize(60, 16777215));
        labelOpacity->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutBrushingOpacity->addWidget(labelOpacity, 0, 0, 1, 1);

        horizontalSliderOpacity = new QSlider(widgetBrushingOpacity);
        horizontalSliderOpacity->setObjectName(QString::fromUtf8("horizontalSliderOpacity"));
        horizontalSliderOpacity->setMaximum(255);
        horizontalSliderOpacity->setValue(63);
        horizontalSliderOpacity->setOrientation(Qt::Horizontal);

        gridLayoutBrushingOpacity->addWidget(horizontalSliderOpacity, 0, 1, 1, 1);

        spinBoxOpacity = new QSpinBox(widgetBrushingOpacity);
        spinBoxOpacity->setObjectName(QString::fromUtf8("spinBoxOpacity"));
        spinBoxOpacity->setMinimumSize(QSize(45, 0));
        spinBoxOpacity->setMaximumSize(QSize(45, 16777215));
        spinBoxOpacity->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxOpacity->setMaximum(255);
        spinBoxOpacity->setSingleStep(10);
        spinBoxOpacity->setValue(63);

        gridLayoutBrushingOpacity->addWidget(spinBoxOpacity, 0, 2, 1, 1);


        verticalLayoutBrushing->addWidget(widgetBrushingOpacity);

        widgetBrushingSize = new QWidget(tabBrushing);
        widgetBrushingSize->setObjectName(QString::fromUtf8("widgetBrushingSize"));
        widgetBrushingSize->setMinimumSize(QSize(0, 0));
        widgetBrushingSize->setMaximumSize(QSize(16777215, 32));
        gridLayoutBrushingSize = new QGridLayout(widgetBrushingSize);
        gridLayoutBrushingSize->setObjectName(QString::fromUtf8("gridLayoutBrushingSize"));
        gridLayoutBrushingSize->setHorizontalSpacing(24);
        gridLayoutBrushingSize->setVerticalSpacing(0);
        gridLayoutBrushingSize->setContentsMargins(0, 0, 12, 0);
        labelSize = new QLabel(widgetBrushingSize);
        labelSize->setObjectName(QString::fromUtf8("labelSize"));
        labelSize->setMinimumSize(QSize(60, 0));
        labelSize->setMaximumSize(QSize(60, 16777215));
        labelSize->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutBrushingSize->addWidget(labelSize, 0, 0, 1, 1);

        horizontalSliderSize = new QSlider(widgetBrushingSize);
        horizontalSliderSize->setObjectName(QString::fromUtf8("horizontalSliderSize"));
        horizontalSliderSize->setMinimum(2);
        horizontalSliderSize->setMaximum(500);
        horizontalSliderSize->setSingleStep(1);
        horizontalSliderSize->setPageStep(25);
        horizontalSliderSize->setValue(50);
        horizontalSliderSize->setOrientation(Qt::Horizontal);

        gridLayoutBrushingSize->addWidget(horizontalSliderSize, 0, 1, 1, 1);

        spinBoxSize = new QSpinBox(widgetBrushingSize);
        spinBoxSize->setObjectName(QString::fromUtf8("spinBoxSize"));
        spinBoxSize->setMinimumSize(QSize(45, 0));
        spinBoxSize->setMaximumSize(QSize(45, 16777215));
        spinBoxSize->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxSize->setMinimum(2);
        spinBoxSize->setMaximum(500);
        spinBoxSize->setSingleStep(25);
        spinBoxSize->setValue(50);

        gridLayoutBrushingSize->addWidget(spinBoxSize, 0, 2, 1, 1);


        verticalLayoutBrushing->addWidget(widgetBrushingSize);

        widgetBrushingShape = new QWidget(tabBrushing);
        widgetBrushingShape->setObjectName(QString::fromUtf8("widgetBrushingShape"));
        widgetBrushingShape->setMinimumSize(QSize(0, 0));
        widgetBrushingShape->setMaximumSize(QSize(16777215, 32));
        gridLayoutBrushingShape = new QGridLayout(widgetBrushingShape);
        gridLayoutBrushingShape->setContentsMargins(0, 0, 0, 0);
        gridLayoutBrushingShape->setObjectName(QString::fromUtf8("gridLayoutBrushingShape"));
        gridLayoutBrushingShape->setHorizontalSpacing(24);
        gridLayoutBrushingShape->setVerticalSpacing(0);
        radioButtonShapeSquare = new QRadioButton(widgetBrushingShape);
        radioButtonShapeSquare->setObjectName(QString::fromUtf8("radioButtonShapeSquare"));
        radioButtonShapeSquare->setMinimumSize(QSize(60, 0));
        radioButtonShapeSquare->setMaximumSize(QSize(60, 16777215));

        gridLayoutBrushingShape->addWidget(radioButtonShapeSquare, 0, 4, 1, 1);

        labelShape = new QLabel(widgetBrushingShape);
        labelShape->setObjectName(QString::fromUtf8("labelShape"));
        labelShape->setMinimumSize(QSize(60, 0));
        labelShape->setMaximumSize(QSize(60, 16777215));
        labelShape->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutBrushingShape->addWidget(labelShape, 0, 0, 1, 1);

        radioButtonShapeCross = new QRadioButton(widgetBrushingShape);
        radioButtonShapeCross->setObjectName(QString::fromUtf8("radioButtonShapeCross"));
        radioButtonShapeCross->setMinimumSize(QSize(60, 0));
        radioButtonShapeCross->setMaximumSize(QSize(60, 16777215));

        gridLayoutBrushingShape->addWidget(radioButtonShapeCross, 0, 5, 1, 1);

        radioButtonShapeCircle = new QRadioButton(widgetBrushingShape);
        radioButtonShapeCircle->setObjectName(QString::fromUtf8("radioButtonShapeCircle"));
        radioButtonShapeCircle->setMinimumSize(QSize(60, 0));
        radioButtonShapeCircle->setMaximumSize(QSize(60, 16777215));
        radioButtonShapeCircle->setChecked(true);

        gridLayoutBrushingShape->addWidget(radioButtonShapeCircle, 0, 2, 1, 1);

        horizontalSpacerShape = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutBrushingShape->addItem(horizontalSpacerShape, 0, 6, 1, 1);


        verticalLayoutBrushing->addWidget(widgetBrushingShape);

        tabWidgetFrontStage->addTab(tabBrushing, QString());
        tabMode = new QProfile();
        tabMode->setObjectName(QString::fromUtf8("tabMode"));
        verticalLayoutMode = new QVBoxLayout(tabMode);
        verticalLayoutMode->setSpacing(9);
        verticalLayoutMode->setObjectName(QString::fromUtf8("verticalLayoutMode"));
        verticalLayoutMode->setContentsMargins(-1, 12, -1, 12);
        widgetModeType = new QWidget(tabMode);
        widgetModeType->setObjectName(QString::fromUtf8("widgetModeType"));
        widgetModeType->setMinimumSize(QSize(0, 0));
        widgetModeType->setMaximumSize(QSize(16777215, 32));
        gridLayoutModeType = new QGridLayout(widgetModeType);
        gridLayoutModeType->setContentsMargins(0, 0, 0, 0);
        gridLayoutModeType->setObjectName(QString::fromUtf8("gridLayoutModeType"));
        gridLayoutModeType->setHorizontalSpacing(24);
        gridLayoutModeType->setVerticalSpacing(0);
        labelType = new QLabel(widgetModeType);
        labelType->setObjectName(QString::fromUtf8("labelType"));
        labelType->setMinimumSize(QSize(60, 0));
        labelType->setMaximumSize(QSize(60, 16777215));
        labelType->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutModeType->addWidget(labelType, 0, 0, 1, 1);

        radioButtonModeBrush = new QRadioButton(widgetModeType);
        radioButtonModeBrush->setObjectName(QString::fromUtf8("radioButtonModeBrush"));
        radioButtonModeBrush->setMinimumSize(QSize(60, 0));
        radioButtonModeBrush->setMaximumSize(QSize(60, 16777215));

        gridLayoutModeType->addWidget(radioButtonModeBrush, 0, 3, 1, 1);

        radioButtonModeNormal = new QRadioButton(widgetModeType);
        radioButtonModeNormal->setObjectName(QString::fromUtf8("radioButtonModeNormal"));
        radioButtonModeNormal->setMinimumSize(QSize(60, 0));
        radioButtonModeNormal->setMaximumSize(QSize(60, 16777215));
        radioButtonModeNormal->setChecked(true);

        gridLayoutModeType->addWidget(radioButtonModeNormal, 0, 2, 1, 1);

        radioButtonModeEraser = new QRadioButton(widgetModeType);
        radioButtonModeEraser->setObjectName(QString::fromUtf8("radioButtonModeEraser"));
        radioButtonModeEraser->setMinimumSize(QSize(60, 0));
        radioButtonModeEraser->setMaximumSize(QSize(60, 16777215));

        gridLayoutModeType->addWidget(radioButtonModeEraser, 0, 4, 1, 1);

        horizontalSpacerModeType = new QSpacerItem(60, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutModeType->addItem(horizontalSpacerModeType, 0, 5, 1, 1);


        verticalLayoutMode->addWidget(widgetModeType);

        widgetBrushingObject = new QWidget(tabMode);
        widgetBrushingObject->setObjectName(QString::fromUtf8("widgetBrushingObject"));
        widgetBrushingObject->setMinimumSize(QSize(0, 0));
        widgetBrushingObject->setMaximumSize(QSize(16777215, 32));
        gridLayoutBrushingObject = new QGridLayout(widgetBrushingObject);
        gridLayoutBrushingObject->setContentsMargins(0, 0, 0, 0);
        gridLayoutBrushingObject->setObjectName(QString::fromUtf8("gridLayoutBrushingObject"));
        gridLayoutBrushingObject->setHorizontalSpacing(24);
        gridLayoutBrushingObject->setVerticalSpacing(0);
        labelBrushingObject = new QLabel(widgetBrushingObject);
        labelBrushingObject->setObjectName(QString::fromUtf8("labelBrushingObject"));
        labelBrushingObject->setMinimumSize(QSize(60, 0));
        labelBrushingObject->setMaximumSize(QSize(60, 16777215));
        labelBrushingObject->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutBrushingObject->addWidget(labelBrushingObject, 0, 0, 1, 1);

        radioButtonBrushingObjectBack = new QRadioButton(widgetBrushingObject);
        radioButtonBrushingObjectBack->setObjectName(QString::fromUtf8("radioButtonBrushingObjectBack"));
        radioButtonBrushingObjectBack->setMinimumSize(QSize(60, 0));
        radioButtonBrushingObjectBack->setMaximumSize(QSize(60, 16777215));

        gridLayoutBrushingObject->addWidget(radioButtonBrushingObjectBack, 0, 3, 1, 1);

        radioButtonBrushingObjectCut = new QRadioButton(widgetBrushingObject);
        radioButtonBrushingObjectCut->setObjectName(QString::fromUtf8("radioButtonBrushingObjectCut"));
        radioButtonBrushingObjectCut->setMinimumSize(QSize(60, 0));
        radioButtonBrushingObjectCut->setMaximumSize(QSize(60, 16777215));
        radioButtonBrushingObjectCut->setChecked(false);

        gridLayoutBrushingObject->addWidget(radioButtonBrushingObjectCut, 0, 4, 1, 1);

        radioButtonBrushingObjectFore = new QRadioButton(widgetBrushingObject);
        radioButtonBrushingObjectFore->setObjectName(QString::fromUtf8("radioButtonBrushingObjectFore"));
        radioButtonBrushingObjectFore->setMinimumSize(QSize(60, 0));
        radioButtonBrushingObjectFore->setMaximumSize(QSize(60, 16777215));
        radioButtonBrushingObjectFore->setChecked(true);

        gridLayoutBrushingObject->addWidget(radioButtonBrushingObjectFore, 0, 2, 1, 1);

        radioButtonBrushingObjectTag = new QRadioButton(widgetBrushingObject);
        radioButtonBrushingObjectTag->setObjectName(QString::fromUtf8("radioButtonBrushingObjectTag"));
        radioButtonBrushingObjectTag->setMinimumSize(QSize(60, 0));
        radioButtonBrushingObjectTag->setMaximumSize(QSize(60, 16777215));
        radioButtonBrushingObjectTag->setChecked(false);

        gridLayoutBrushingObject->addWidget(radioButtonBrushingObjectTag, 0, 5, 1, 1);


        verticalLayoutMode->addWidget(widgetBrushingObject);

        widgetModeEdit = new QWidget(tabMode);
        widgetModeEdit->setObjectName(QString::fromUtf8("widgetModeEdit"));
        widgetModeEdit->setMinimumSize(QSize(0, 0));
        widgetModeEdit->setMaximumSize(QSize(16777215, 32));
        gridLayoutModeEdit = new QGridLayout(widgetModeEdit);
        gridLayoutModeEdit->setContentsMargins(0, 0, 0, 0);
        gridLayoutModeEdit->setObjectName(QString::fromUtf8("gridLayoutModeEdit"));
        gridLayoutModeEdit->setHorizontalSpacing(24);
        gridLayoutModeEdit->setVerticalSpacing(0);
        pushButtonClear = new QPushButton(widgetModeEdit);
        pushButtonClear->setObjectName(QString::fromUtf8("pushButtonClear"));
        pushButtonClear->setMinimumSize(QSize(60, 0));
        pushButtonClear->setMaximumSize(QSize(60, 16777215));

        gridLayoutModeEdit->addWidget(pushButtonClear, 0, 3, 1, 1);

        labelModeEdit = new QLabel(widgetModeEdit);
        labelModeEdit->setObjectName(QString::fromUtf8("labelModeEdit"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelModeEdit->sizePolicy().hasHeightForWidth());
        labelModeEdit->setSizePolicy(sizePolicy3);
        labelModeEdit->setMinimumSize(QSize(60, 0));
        labelModeEdit->setMaximumSize(QSize(60, 16777215));
        labelModeEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutModeEdit->addWidget(labelModeEdit, 0, 0, 1, 1);

        pushButtonUndo = new QPushButton(widgetModeEdit);
        pushButtonUndo->setObjectName(QString::fromUtf8("pushButtonUndo"));
        pushButtonUndo->setMinimumSize(QSize(60, 0));
        pushButtonUndo->setMaximumSize(QSize(60, 16777215));

        gridLayoutModeEdit->addWidget(pushButtonUndo, 0, 2, 1, 1);

        pushButtonRedo = new QPushButton(widgetModeEdit);
        pushButtonRedo->setObjectName(QString::fromUtf8("pushButtonRedo"));
        pushButtonRedo->setMinimumSize(QSize(60, 0));
        pushButtonRedo->setMaximumSize(QSize(60, 16777215));

        gridLayoutModeEdit->addWidget(pushButtonRedo, 0, 1, 1, 1);

        horizontalSpacerModeEdit2 = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutModeEdit->addItem(horizontalSpacerModeEdit2, 0, 4, 1, 1);


        verticalLayoutMode->addWidget(widgetModeEdit);

        tabWidgetFrontStage->addTab(tabMode, QString());
        tabColor = new QProfile();
        tabColor->setObjectName(QString::fromUtf8("tabColor"));
        verticalLayoutColor = new QVBoxLayout(tabColor);
        verticalLayoutColor->setSpacing(9);
        verticalLayoutColor->setObjectName(QString::fromUtf8("verticalLayoutColor"));
        verticalLayoutColor->setContentsMargins(-1, 12, -1, 12);
        widgetColorFore = new QWidget(tabColor);
        widgetColorFore->setObjectName(QString::fromUtf8("widgetColorFore"));
        widgetColorFore->setMinimumSize(QSize(0, 0));
        widgetColorFore->setMaximumSize(QSize(16777215, 32));
        gridLayoutColorFore = new QGridLayout(widgetColorFore);
        gridLayoutColorFore->setObjectName(QString::fromUtf8("gridLayoutColorFore"));
        gridLayoutColorFore->setHorizontalSpacing(24);
        gridLayoutColorFore->setVerticalSpacing(0);
        gridLayoutColorFore->setContentsMargins(0, 0, 12, 0);
        pushButtonColorFore = new QPushButton(widgetColorFore);
        pushButtonColorFore->setObjectName(QString::fromUtf8("pushButtonColorFore"));
        pushButtonColorFore->setMinimumSize(QSize(24, 24));
        pushButtonColorFore->setMaximumSize(QSize(24, 24));
        pushButtonColorFore->setStyleSheet(QString::fromUtf8("border-radius: 12px; background-color: rgba(255, 127, 127, 127);"));

        gridLayoutColorFore->addWidget(pushButtonColorFore, 0, 1, 1, 1);

        labelColorForeNote = new QLabel(widgetColorFore);
        labelColorForeNote->setObjectName(QString::fromUtf8("labelColorForeNote"));
        labelColorForeNote->setMinimumSize(QSize(60, 0));
        labelColorForeNote->setMaximumSize(QSize(60, 16777215));
        labelColorForeNote->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutColorFore->addWidget(labelColorForeNote, 0, 0, 1, 1);

        horizontalSliderColorFore = new QSlider(widgetColorFore);
        horizontalSliderColorFore->setObjectName(QString::fromUtf8("horizontalSliderColorFore"));
        horizontalSliderColorFore->setMaximum(255);
        horizontalSliderColorFore->setSingleStep(1);
        horizontalSliderColorFore->setPageStep(10);
        horizontalSliderColorFore->setValue(127);
        horizontalSliderColorFore->setOrientation(Qt::Horizontal);

        gridLayoutColorFore->addWidget(horizontalSliderColorFore, 0, 2, 1, 1);

        spinBoxColorFore = new QSpinBox(widgetColorFore);
        spinBoxColorFore->setObjectName(QString::fromUtf8("spinBoxColorFore"));
        spinBoxColorFore->setMinimumSize(QSize(45, 0));
        spinBoxColorFore->setMaximumSize(QSize(45, 16777215));
        spinBoxColorFore->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxColorFore->setMaximum(255);
        spinBoxColorFore->setSingleStep(10);
        spinBoxColorFore->setValue(63);

        gridLayoutColorFore->addWidget(spinBoxColorFore, 0, 3, 1, 1);


        verticalLayoutColor->addWidget(widgetColorFore);

        widgetColorBack = new QWidget(tabColor);
        widgetColorBack->setObjectName(QString::fromUtf8("widgetColorBack"));
        widgetColorBack->setMinimumSize(QSize(0, 0));
        widgetColorBack->setMaximumSize(QSize(16777215, 32));
        gridLayoutColorBack = new QGridLayout(widgetColorBack);
        gridLayoutColorBack->setObjectName(QString::fromUtf8("gridLayoutColorBack"));
        gridLayoutColorBack->setHorizontalSpacing(24);
        gridLayoutColorBack->setVerticalSpacing(0);
        gridLayoutColorBack->setContentsMargins(0, 0, 12, 0);
        horizontalSliderColorBack = new QSlider(widgetColorBack);
        horizontalSliderColorBack->setObjectName(QString::fromUtf8("horizontalSliderColorBack"));
        horizontalSliderColorBack->setMaximum(255);
        horizontalSliderColorBack->setSingleStep(1);
        horizontalSliderColorBack->setPageStep(10);
        horizontalSliderColorBack->setValue(127);
        horizontalSliderColorBack->setOrientation(Qt::Horizontal);

        gridLayoutColorBack->addWidget(horizontalSliderColorBack, 0, 2, 1, 1);

        pushButtonColorBack = new QPushButton(widgetColorBack);
        pushButtonColorBack->setObjectName(QString::fromUtf8("pushButtonColorBack"));
        pushButtonColorBack->setMinimumSize(QSize(24, 24));
        pushButtonColorBack->setMaximumSize(QSize(24, 24));
        pushButtonColorBack->setStyleSheet(QString::fromUtf8("border-radius: 12px; background-color: rgba(127, 255, 127, 127);"));

        gridLayoutColorBack->addWidget(pushButtonColorBack, 0, 1, 1, 1);

        labelColorBackNote = new QLabel(widgetColorBack);
        labelColorBackNote->setObjectName(QString::fromUtf8("labelColorBackNote"));
        labelColorBackNote->setMinimumSize(QSize(60, 0));
        labelColorBackNote->setMaximumSize(QSize(60, 16777215));
        labelColorBackNote->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutColorBack->addWidget(labelColorBackNote, 0, 0, 1, 1);

        spinBoxColorBack = new QSpinBox(widgetColorBack);
        spinBoxColorBack->setObjectName(QString::fromUtf8("spinBoxColorBack"));
        spinBoxColorBack->setMinimumSize(QSize(45, 0));
        spinBoxColorBack->setMaximumSize(QSize(45, 16777215));
        spinBoxColorBack->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxColorBack->setMaximum(255);
        spinBoxColorBack->setSingleStep(10);
        spinBoxColorBack->setValue(63);

        gridLayoutColorBack->addWidget(spinBoxColorBack, 0, 3, 1, 1);


        verticalLayoutColor->addWidget(widgetColorBack);

        widgetColorCut = new QWidget(tabColor);
        widgetColorCut->setObjectName(QString::fromUtf8("widgetColorCut"));
        widgetColorCut->setMinimumSize(QSize(0, 0));
        widgetColorCut->setMaximumSize(QSize(16777215, 32));
        gridLayoutColorCut = new QGridLayout(widgetColorCut);
        gridLayoutColorCut->setObjectName(QString::fromUtf8("gridLayoutColorCut"));
        gridLayoutColorCut->setHorizontalSpacing(24);
        gridLayoutColorCut->setVerticalSpacing(0);
        gridLayoutColorCut->setContentsMargins(0, 0, 12, 0);
        pushButtonColorCut = new QPushButton(widgetColorCut);
        pushButtonColorCut->setObjectName(QString::fromUtf8("pushButtonColorCut"));
        pushButtonColorCut->setMinimumSize(QSize(24, 24));
        pushButtonColorCut->setMaximumSize(QSize(24, 24));
        pushButtonColorCut->setStyleSheet(QString::fromUtf8("border-radius: 12px; background-color: rgba(127, 127, 225, 127);"));

        gridLayoutColorCut->addWidget(pushButtonColorCut, 0, 1, 1, 1);

        labelColorCutNote = new QLabel(widgetColorCut);
        labelColorCutNote->setObjectName(QString::fromUtf8("labelColorCutNote"));
        labelColorCutNote->setMinimumSize(QSize(60, 0));
        labelColorCutNote->setMaximumSize(QSize(60, 16777215));
        labelColorCutNote->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutColorCut->addWidget(labelColorCutNote, 0, 0, 1, 1);

        horizontalSliderColorCut = new QSlider(widgetColorCut);
        horizontalSliderColorCut->setObjectName(QString::fromUtf8("horizontalSliderColorCut"));
        horizontalSliderColorCut->setMaximum(255);
        horizontalSliderColorCut->setSingleStep(1);
        horizontalSliderColorCut->setPageStep(10);
        horizontalSliderColorCut->setValue(127);
        horizontalSliderColorCut->setOrientation(Qt::Horizontal);

        gridLayoutColorCut->addWidget(horizontalSliderColorCut, 0, 2, 1, 1);

        spinBoxColorCut = new QSpinBox(widgetColorCut);
        spinBoxColorCut->setObjectName(QString::fromUtf8("spinBoxColorCut"));
        spinBoxColorCut->setMinimumSize(QSize(45, 0));
        spinBoxColorCut->setMaximumSize(QSize(45, 16777215));
        spinBoxColorCut->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxColorCut->setMaximum(255);
        spinBoxColorCut->setSingleStep(10);
        spinBoxColorCut->setValue(63);

        gridLayoutColorCut->addWidget(spinBoxColorCut, 0, 3, 1, 1);


        verticalLayoutColor->addWidget(widgetColorCut);

        widgetColorTag = new QWidget(tabColor);
        widgetColorTag->setObjectName(QString::fromUtf8("widgetColorTag"));
        widgetColorTag->setMinimumSize(QSize(0, 0));
        widgetColorTag->setMaximumSize(QSize(16777215, 32));
        gridLayoutColorTag = new QGridLayout(widgetColorTag);
        gridLayoutColorTag->setObjectName(QString::fromUtf8("gridLayoutColorTag"));
        gridLayoutColorTag->setHorizontalSpacing(24);
        gridLayoutColorTag->setVerticalSpacing(0);
        gridLayoutColorTag->setContentsMargins(0, 0, 12, 0);
        pushButtonColorTag = new QPushButton(widgetColorTag);
        pushButtonColorTag->setObjectName(QString::fromUtf8("pushButtonColorTag"));
        pushButtonColorTag->setMinimumSize(QSize(24, 24));
        pushButtonColorTag->setMaximumSize(QSize(24, 24));
        pushButtonColorTag->setStyleSheet(QString::fromUtf8("border-radius: 12px; background-color: rgba(255, 127, 225, 127);"));

        gridLayoutColorTag->addWidget(pushButtonColorTag, 0, 1, 1, 1);

        labelColorTagNote = new QLabel(widgetColorTag);
        labelColorTagNote->setObjectName(QString::fromUtf8("labelColorTagNote"));
        labelColorTagNote->setMinimumSize(QSize(60, 0));
        labelColorTagNote->setMaximumSize(QSize(60, 16777215));
        labelColorTagNote->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutColorTag->addWidget(labelColorTagNote, 0, 0, 1, 1);

        horizontalSliderColorTag = new QSlider(widgetColorTag);
        horizontalSliderColorTag->setObjectName(QString::fromUtf8("horizontalSliderColorTag"));
        horizontalSliderColorTag->setMaximum(255);
        horizontalSliderColorTag->setSingleStep(1);
        horizontalSliderColorTag->setPageStep(10);
        horizontalSliderColorTag->setValue(127);
        horizontalSliderColorTag->setOrientation(Qt::Horizontal);

        gridLayoutColorTag->addWidget(horizontalSliderColorTag, 0, 2, 1, 1);

        spinBoxColorTag = new QSpinBox(widgetColorTag);
        spinBoxColorTag->setObjectName(QString::fromUtf8("spinBoxColorTag"));
        spinBoxColorTag->setMinimumSize(QSize(45, 0));
        spinBoxColorTag->setMaximumSize(QSize(45, 16777215));
        spinBoxColorTag->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxColorTag->setMaximum(255);
        spinBoxColorTag->setSingleStep(10);
        spinBoxColorTag->setValue(63);

        gridLayoutColorTag->addWidget(spinBoxColorTag, 0, 3, 1, 1);


        verticalLayoutColor->addWidget(widgetColorTag);

        tabWidgetFrontStage->addTab(tabColor, QString());
        tabTexture = new QProfile();
        tabTexture->setObjectName(QString::fromUtf8("tabTexture"));
        verticalLayoutTexture = new QVBoxLayout(tabTexture);
        verticalLayoutTexture->setSpacing(9);
        verticalLayoutTexture->setObjectName(QString::fromUtf8("verticalLayoutTexture"));
        verticalLayoutTexture->setContentsMargins(-1, 12, 9, 12);
        widgetTextureGraph = new QWidget(tabTexture);
        widgetTextureGraph->setObjectName(QString::fromUtf8("widgetTextureGraph"));
        widgetTextureGraph->setMinimumSize(QSize(0, 0));
        widgetTextureGraph->setMaximumSize(QSize(16777215, 32));
        gridLayoutTextureGraph = new QGridLayout(widgetTextureGraph);
        gridLayoutTextureGraph->setContentsMargins(0, 0, 0, 0);
        gridLayoutTextureGraph->setObjectName(QString::fromUtf8("gridLayoutTextureGraph"));
        gridLayoutTextureGraph->setHorizontalSpacing(24);
        gridLayoutTextureGraph->setVerticalSpacing(0);
        pushButtonSaveGraph = new QPushButton(widgetTextureGraph);
        pushButtonSaveGraph->setObjectName(QString::fromUtf8("pushButtonSaveGraph"));
        pushButtonSaveGraph->setMinimumSize(QSize(60, 0));
        pushButtonSaveGraph->setMaximumSize(QSize(60, 16777215));

        gridLayoutTextureGraph->addWidget(pushButtonSaveGraph, 0, 2, 1, 1);

        pushButtonLoadGraph = new QPushButton(widgetTextureGraph);
        pushButtonLoadGraph->setObjectName(QString::fromUtf8("pushButtonLoadGraph"));
        pushButtonLoadGraph->setMinimumSize(QSize(60, 0));
        pushButtonLoadGraph->setMaximumSize(QSize(60, 16777215));

        gridLayoutTextureGraph->addWidget(pushButtonLoadGraph, 0, 3, 1, 1);

        labelGraph = new QLabel(widgetTextureGraph);
        labelGraph->setObjectName(QString::fromUtf8("labelGraph"));
        labelGraph->setMinimumSize(QSize(60, 0));
        labelGraph->setMaximumSize(QSize(60, 16777215));
        labelGraph->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutTextureGraph->addWidget(labelGraph, 0, 0, 1, 1);

        checkBoxGraph = new QCheckBox(widgetTextureGraph);
        checkBoxGraph->setObjectName(QString::fromUtf8("checkBoxGraph"));
        checkBoxGraph->setMinimumSize(QSize(60, 0));
        checkBoxGraph->setMaximumSize(QSize(60, 16777215));
        checkBoxGraph->setLayoutDirection(Qt::RightToLeft);
        checkBoxGraph->setChecked(true);

        gridLayoutTextureGraph->addWidget(checkBoxGraph, 0, 4, 1, 1);


        verticalLayoutTexture->addWidget(widgetTextureGraph);

        widgetTextureGradient = new QWidget(tabTexture);
        widgetTextureGradient->setObjectName(QString::fromUtf8("widgetTextureGradient"));
        widgetTextureGradient->setMinimumSize(QSize(0, 0));
        widgetTextureGradient->setMaximumSize(QSize(16777215, 32));
        gridLayoutTextureGradient = new QGridLayout(widgetTextureGradient);
        gridLayoutTextureGradient->setContentsMargins(0, 0, 0, 0);
        gridLayoutTextureGradient->setObjectName(QString::fromUtf8("gridLayoutTextureGradient"));
        gridLayoutTextureGradient->setHorizontalSpacing(24);
        gridLayoutTextureGradient->setVerticalSpacing(0);
        pushButtonLoadGradient = new QPushButton(widgetTextureGradient);
        pushButtonLoadGradient->setObjectName(QString::fromUtf8("pushButtonLoadGradient"));
        pushButtonLoadGradient->setMinimumSize(QSize(60, 0));
        pushButtonLoadGradient->setMaximumSize(QSize(60, 16777215));

        gridLayoutTextureGradient->addWidget(pushButtonLoadGradient, 0, 3, 1, 1);

        pushButtonSaveGradient = new QPushButton(widgetTextureGradient);
        pushButtonSaveGradient->setObjectName(QString::fromUtf8("pushButtonSaveGradient"));
        pushButtonSaveGradient->setMinimumSize(QSize(60, 0));
        pushButtonSaveGradient->setMaximumSize(QSize(60, 16777215));

        gridLayoutTextureGradient->addWidget(pushButtonSaveGradient, 0, 2, 1, 1);

        labelGradient = new QLabel(widgetTextureGradient);
        labelGradient->setObjectName(QString::fromUtf8("labelGradient"));
        labelGradient->setMinimumSize(QSize(60, 0));
        labelGradient->setMaximumSize(QSize(60, 16777215));
        labelGradient->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutTextureGradient->addWidget(labelGradient, 0, 0, 1, 1);

        checkBoxGradient = new QCheckBox(widgetTextureGradient);
        checkBoxGradient->setObjectName(QString::fromUtf8("checkBoxGradient"));
        checkBoxGradient->setMinimumSize(QSize(60, 0));
        checkBoxGradient->setMaximumSize(QSize(60, 16777215));
        checkBoxGradient->setLayoutDirection(Qt::RightToLeft);
        checkBoxGradient->setChecked(false);

        gridLayoutTextureGradient->addWidget(checkBoxGradient, 0, 4, 1, 1);


        verticalLayoutTexture->addWidget(widgetTextureGradient);

        widgetTextureFeature = new QWidget(tabTexture);
        widgetTextureFeature->setObjectName(QString::fromUtf8("widgetTextureFeature"));
        widgetTextureFeature->setMinimumSize(QSize(0, 0));
        widgetTextureFeature->setMaximumSize(QSize(16777215, 32));
        gridLayoutTextureFeature = new QGridLayout(widgetTextureFeature);
        gridLayoutTextureFeature->setContentsMargins(0, 0, 0, 0);
        gridLayoutTextureFeature->setObjectName(QString::fromUtf8("gridLayoutTextureFeature"));
        gridLayoutTextureFeature->setHorizontalSpacing(24);
        gridLayoutTextureFeature->setVerticalSpacing(0);
        pushButtonLoadFeature = new QPushButton(widgetTextureFeature);
        pushButtonLoadFeature->setObjectName(QString::fromUtf8("pushButtonLoadFeature"));
        pushButtonLoadFeature->setMinimumSize(QSize(60, 0));
        pushButtonLoadFeature->setMaximumSize(QSize(60, 16777215));

        gridLayoutTextureFeature->addWidget(pushButtonLoadFeature, 0, 3, 1, 1);

        pushButtonSaveFeature = new QPushButton(widgetTextureFeature);
        pushButtonSaveFeature->setObjectName(QString::fromUtf8("pushButtonSaveFeature"));
        pushButtonSaveFeature->setMinimumSize(QSize(60, 0));
        pushButtonSaveFeature->setMaximumSize(QSize(60, 16777215));

        gridLayoutTextureFeature->addWidget(pushButtonSaveFeature, 0, 2, 1, 1);

        labelFeature = new QLabel(widgetTextureFeature);
        labelFeature->setObjectName(QString::fromUtf8("labelFeature"));
        labelFeature->setMinimumSize(QSize(60, 0));
        labelFeature->setMaximumSize(QSize(60, 16777215));
        labelFeature->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutTextureFeature->addWidget(labelFeature, 0, 0, 1, 1);

        checkBoxFeature = new QCheckBox(widgetTextureFeature);
        checkBoxFeature->setObjectName(QString::fromUtf8("checkBoxFeature"));
        checkBoxFeature->setMinimumSize(QSize(60, 0));
        checkBoxFeature->setMaximumSize(QSize(60, 16777215));
        checkBoxFeature->setLayoutDirection(Qt::RightToLeft);
        checkBoxFeature->setChecked(false);

        gridLayoutTextureFeature->addWidget(checkBoxFeature, 0, 4, 1, 1);


        verticalLayoutTexture->addWidget(widgetTextureFeature);

        widgetTextureCut = new QWidget(tabTexture);
        widgetTextureCut->setObjectName(QString::fromUtf8("widgetTextureCut"));
        widgetTextureCut->setMinimumSize(QSize(0, 0));
        widgetTextureCut->setMaximumSize(QSize(16777215, 32));
        gridLayoutTextureCut = new QGridLayout(widgetTextureCut);
        gridLayoutTextureCut->setContentsMargins(0, 0, 0, 0);
        gridLayoutTextureCut->setObjectName(QString::fromUtf8("gridLayoutTextureCut"));
        gridLayoutTextureCut->setHorizontalSpacing(24);
        gridLayoutTextureCut->setVerticalSpacing(0);
        checkBoxCut = new QCheckBox(widgetTextureCut);
        checkBoxCut->setObjectName(QString::fromUtf8("checkBoxCut"));
        checkBoxCut->setMinimumSize(QSize(60, 0));
        checkBoxCut->setMaximumSize(QSize(60, 16777215));
        checkBoxCut->setLayoutDirection(Qt::RightToLeft);
        checkBoxCut->setChecked(false);

        gridLayoutTextureCut->addWidget(checkBoxCut, 0, 4, 1, 1);

        pushButtonSaveCut = new QPushButton(widgetTextureCut);
        pushButtonSaveCut->setObjectName(QString::fromUtf8("pushButtonSaveCut"));
        pushButtonSaveCut->setMinimumSize(QSize(60, 0));
        pushButtonSaveCut->setMaximumSize(QSize(60, 16777215));

        gridLayoutTextureCut->addWidget(pushButtonSaveCut, 0, 2, 1, 1);

        pushButtonLoadCut = new QPushButton(widgetTextureCut);
        pushButtonLoadCut->setObjectName(QString::fromUtf8("pushButtonLoadCut"));
        pushButtonLoadCut->setMinimumSize(QSize(60, 0));
        pushButtonLoadCut->setMaximumSize(QSize(60, 16777215));

        gridLayoutTextureCut->addWidget(pushButtonLoadCut, 0, 3, 1, 1);

        labelCut = new QLabel(widgetTextureCut);
        labelCut->setObjectName(QString::fromUtf8("labelCut"));
        labelCut->setMinimumSize(QSize(60, 0));
        labelCut->setMaximumSize(QSize(60, 16777215));
        labelCut->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutTextureCut->addWidget(labelCut, 0, 0, 1, 1);


        verticalLayoutTexture->addWidget(widgetTextureCut);

        tabWidgetFrontStage->addTab(tabTexture, QString());

        gridLayoutGraphCut->addWidget(tabWidgetFrontStage, 0, 1, 1, 1);


        gridLayoutVolumeRendering->addWidget(groupBoxGraphCut, 0, 0, 1, 1);

        widgetRender = new QGCWidget(groupBoxVolumeRendering);
        widgetRender->setObjectName(QString::fromUtf8("widgetRender"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(widgetRender->sizePolicy().hasHeightForWidth());
        widgetRender->setSizePolicy(sizePolicy4);
        widgetRender->setMinimumSize(QSize(0, 0));
        widgetRender->setMaximumSize(QSize(16777215, 16777215));
        widgetRender->setMouseTracking(true);

        gridLayoutVolumeRendering->addWidget(widgetRender, 0, 2, 1, 1);

        splitter->addWidget(groupBoxVolumeRendering);
        groupBoxRendering = new QGroupBox(splitter);
        groupBoxRendering->setObjectName(QString::fromUtf8("groupBoxRendering"));
        groupBoxRendering->setMinimumSize(QSize(0, 288));
        groupBoxRendering->setMaximumSize(QSize(16777215, 16777215));
        gridLayoutRendering = new QGridLayout(groupBoxRendering);
        gridLayoutRendering->setContentsMargins(6, 6, 6, 6);
        gridLayoutRendering->setObjectName(QString::fromUtf8("gridLayoutRendering"));
        groupBoxTransferFunctionEditor = new QGroupBox(groupBoxRendering);
        groupBoxTransferFunctionEditor->setObjectName(QString::fromUtf8("groupBoxTransferFunctionEditor"));
        groupBoxTransferFunctionEditor->setMinimumSize(QSize(0, 0));
        groupBoxTransferFunctionEditor->setMaximumSize(QSize(16777215, 16777215));
        groupBoxTransferFunctionEditor->setCheckable(false);
        gridLayoutTransferFunctionEditor = new QGridLayout(groupBoxTransferFunctionEditor);
        gridLayoutTransferFunctionEditor->setContentsMargins(6, 6, 6, 6);
        gridLayoutTransferFunctionEditor->setObjectName(QString::fromUtf8("gridLayoutTransferFunctionEditor"));
        widgetEditor = new QTransferFunction1D(groupBoxTransferFunctionEditor);
        widgetEditor->setObjectName(QString::fromUtf8("widgetEditor"));
        widgetEditor->setMinimumSize(QSize(0, 0));
        widgetEditor->setMaximumSize(QSize(16777215, 16777215));

        gridLayoutTransferFunctionEditor->addWidget(widgetEditor, 0, 0, 1, 1);


        gridLayoutRendering->addWidget(groupBoxTransferFunctionEditor, 0, 1, 1, 1);

        groupBoxWindow = new QGroupBox(groupBoxRendering);
        groupBoxWindow->setObjectName(QString::fromUtf8("groupBoxWindow"));
        sizePolicy2.setHeightForWidth(groupBoxWindow->sizePolicy().hasHeightForWidth());
        groupBoxWindow->setSizePolicy(sizePolicy2);
        groupBoxWindow->setMinimumSize(QSize(100, 0));
        gridLayoutWindow = new QGridLayout(groupBoxWindow);
        gridLayoutWindow->setContentsMargins(6, 6, 6, 6);
        gridLayoutWindow->setObjectName(QString::fromUtf8("gridLayoutWindow"));
        verticalSliderWindowLevel = new QSlider(groupBoxWindow);
        verticalSliderWindowLevel->setObjectName(QString::fromUtf8("verticalSliderWindowLevel"));
        verticalSliderWindowLevel->setMinimumSize(QSize(24, 0));
        verticalSliderWindowLevel->setMaximum(65535);
        verticalSliderWindowLevel->setPageStep(100);
        verticalSliderWindowLevel->setValue(32767);
        verticalSliderWindowLevel->setSliderPosition(32767);
        verticalSliderWindowLevel->setOrientation(Qt::Vertical);

        gridLayoutWindow->addWidget(verticalSliderWindowLevel, 2, 1, 1, 1);

        verticalSliderWindowWidth = new QSlider(groupBoxWindow);
        verticalSliderWindowWidth->setObjectName(QString::fromUtf8("verticalSliderWindowWidth"));
        verticalSliderWindowWidth->setMinimumSize(QSize(24, 0));
        verticalSliderWindowWidth->setMaximum(65535);
        verticalSliderWindowWidth->setPageStep(100);
        verticalSliderWindowWidth->setValue(65535);
        verticalSliderWindowWidth->setSliderPosition(65535);
        verticalSliderWindowWidth->setOrientation(Qt::Vertical);

        gridLayoutWindow->addWidget(verticalSliderWindowWidth, 2, 0, 1, 1);

        labelWindowWidth = new QLabel(groupBoxWindow);
        labelWindowWidth->setObjectName(QString::fromUtf8("labelWindowWidth"));
        sizePolicy2.setHeightForWidth(labelWindowWidth->sizePolicy().hasHeightForWidth());
        labelWindowWidth->setSizePolicy(sizePolicy2);
        labelWindowWidth->setMinimumSize(QSize(30, 0));
        labelWindowWidth->setMaximumSize(QSize(16777215, 16777215));
        labelWindowWidth->setAlignment(Qt::AlignCenter);

        gridLayoutWindow->addWidget(labelWindowWidth, 3, 0, 1, 1);

        labelWindowLevel = new QLabel(groupBoxWindow);
        labelWindowLevel->setObjectName(QString::fromUtf8("labelWindowLevel"));
        sizePolicy2.setHeightForWidth(labelWindowLevel->sizePolicy().hasHeightForWidth());
        labelWindowLevel->setSizePolicy(sizePolicy2);
        labelWindowLevel->setMinimumSize(QSize(30, 0));
        labelWindowLevel->setMaximumSize(QSize(16777215, 16777215));
        labelWindowLevel->setAlignment(Qt::AlignCenter);

        gridLayoutWindow->addWidget(labelWindowLevel, 3, 1, 1, 1);

        labelWindowLevelNote = new QLabel(groupBoxWindow);
        labelWindowLevelNote->setObjectName(QString::fromUtf8("labelWindowLevelNote"));
        sizePolicy2.setHeightForWidth(labelWindowLevelNote->sizePolicy().hasHeightForWidth());
        labelWindowLevelNote->setSizePolicy(sizePolicy2);
        labelWindowLevelNote->setMinimumSize(QSize(24, 0));
        labelWindowLevelNote->setAlignment(Qt::AlignCenter);

        gridLayoutWindow->addWidget(labelWindowLevelNote, 1, 1, 1, 1);

        labelWindowWidthNote = new QLabel(groupBoxWindow);
        labelWindowWidthNote->setObjectName(QString::fromUtf8("labelWindowWidthNote"));
        sizePolicy2.setHeightForWidth(labelWindowWidthNote->sizePolicy().hasHeightForWidth());
        labelWindowWidthNote->setSizePolicy(sizePolicy2);
        labelWindowWidthNote->setMinimumSize(QSize(24, 0));
        labelWindowWidthNote->setAlignment(Qt::AlignCenter);

        gridLayoutWindow->addWidget(labelWindowWidthNote, 1, 0, 1, 1);


        gridLayoutRendering->addWidget(groupBoxWindow, 0, 2, 1, 1);

        tabWidgetSettings = new QTabWidget(groupBoxRendering);
        tabWidgetSettings->setObjectName(QString::fromUtf8("tabWidgetSettings"));
        sizePolicy2.setHeightForWidth(tabWidgetSettings->sizePolicy().hasHeightForWidth());
        tabWidgetSettings->setSizePolicy(sizePolicy2);
        tabWidgetSettings->setMinimumSize(QSize(420, 0));
        tabWidgetSettings->setMaximumSize(QSize(0, 16777215));
        tabTransferFunction = new QWidget();
        tabTransferFunction->setObjectName(QString::fromUtf8("tabTransferFunction"));
        verticalLayoutTransferFunction = new QVBoxLayout(tabTransferFunction);
        verticalLayoutTransferFunction->setObjectName(QString::fromUtf8("verticalLayoutTransferFunction"));
        verticalLayoutTransferFunction->setContentsMargins(-1, 12, -1, 12);
        widgetTransferFunctionSettings = new QWidget(tabTransferFunction);
        widgetTransferFunctionSettings->setObjectName(QString::fromUtf8("widgetTransferFunctionSettings"));
        widgetTransferFunctionSettings->setMinimumSize(QSize(0, 0));
        widgetTransferFunctionSettings->setMaximumSize(QSize(16777215, 32));
        gridLayoutTransferFunctionSettings = new QGridLayout(widgetTransferFunctionSettings);
        gridLayoutTransferFunctionSettings->setContentsMargins(0, 0, 0, 0);
        gridLayoutTransferFunctionSettings->setObjectName(QString::fromUtf8("gridLayoutTransferFunctionSettings"));
        gridLayoutTransferFunctionSettings->setHorizontalSpacing(24);
        gridLayoutTransferFunctionSettings->setVerticalSpacing(0);
        pushButtonLoadTransferFunction = new QPushButton(widgetTransferFunctionSettings);
        pushButtonLoadTransferFunction->setObjectName(QString::fromUtf8("pushButtonLoadTransferFunction"));
        pushButtonLoadTransferFunction->setMinimumSize(QSize(60, 0));
        pushButtonLoadTransferFunction->setMaximumSize(QSize(60, 16777215));

        gridLayoutTransferFunctionSettings->addWidget(pushButtonLoadTransferFunction, 0, 1, 1, 1);

        pushButtonSaveTransferFunction = new QPushButton(widgetTransferFunctionSettings);
        pushButtonSaveTransferFunction->setObjectName(QString::fromUtf8("pushButtonSaveTransferFunction"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pushButtonSaveTransferFunction->sizePolicy().hasHeightForWidth());
        pushButtonSaveTransferFunction->setSizePolicy(sizePolicy5);
        pushButtonSaveTransferFunction->setMinimumSize(QSize(60, 0));
        pushButtonSaveTransferFunction->setMaximumSize(QSize(60, 16777215));

        gridLayoutTransferFunctionSettings->addWidget(pushButtonSaveTransferFunction, 0, 2, 1, 1);


        verticalLayoutTransferFunction->addWidget(widgetTransferFunctionSettings);

        widgetInterpolation = new QWidget(tabTransferFunction);
        widgetInterpolation->setObjectName(QString::fromUtf8("widgetInterpolation"));
        widgetInterpolation->setMinimumSize(QSize(0, 0));
        widgetInterpolation->setMaximumSize(QSize(16777215, 32));
        gridLayoutInterpolation = new QGridLayout(widgetInterpolation);
        gridLayoutInterpolation->setContentsMargins(0, 0, 0, 0);
        gridLayoutInterpolation->setObjectName(QString::fromUtf8("gridLayoutInterpolation"));
        gridLayoutInterpolation->setHorizontalSpacing(24);
        gridLayoutInterpolation->setVerticalSpacing(0);
        radioButtonInterpolationLinear = new QRadioButton(widgetInterpolation);
        radioButtonInterpolationLinear->setObjectName(QString::fromUtf8("radioButtonInterpolationLinear"));
        radioButtonInterpolationLinear->setMinimumSize(QSize(75, 0));
        radioButtonInterpolationLinear->setMaximumSize(QSize(75, 16777215));
        radioButtonInterpolationLinear->setLayoutDirection(Qt::LeftToRight);
        radioButtonInterpolationLinear->setChecked(false);

        gridLayoutInterpolation->addWidget(radioButtonInterpolationLinear, 0, 1, 1, 1);

        labelInterpolation = new QLabel(widgetInterpolation);
        labelInterpolation->setObjectName(QString::fromUtf8("labelInterpolation"));
        labelInterpolation->setMinimumSize(QSize(90, 0));
        labelInterpolation->setMaximumSize(QSize(90, 16777215));
        labelInterpolation->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutInterpolation->addWidget(labelInterpolation, 0, 0, 1, 1);

        radioButtonInterpolationCubic = new QRadioButton(widgetInterpolation);
        radioButtonInterpolationCubic->setObjectName(QString::fromUtf8("radioButtonInterpolationCubic"));
        radioButtonInterpolationCubic->setMinimumSize(QSize(75, 0));
        radioButtonInterpolationCubic->setMaximumSize(QSize(75, 16777215));
        radioButtonInterpolationCubic->setLayoutDirection(Qt::LeftToRight);
        radioButtonInterpolationCubic->setChecked(true);

        gridLayoutInterpolation->addWidget(radioButtonInterpolationCubic, 0, 2, 1, 1);

        horizontalSpacerInterpolation = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutInterpolation->addItem(horizontalSpacerInterpolation, 0, 5, 1, 1);


        verticalLayoutTransferFunction->addWidget(widgetInterpolation);

        widgetPointNumber = new QWidget(tabTransferFunction);
        widgetPointNumber->setObjectName(QString::fromUtf8("widgetPointNumber"));
        widgetPointNumber->setMinimumSize(QSize(0, 0));
        widgetPointNumber->setMaximumSize(QSize(16777215, 32));
        gridLayoutPointNumber = new QGridLayout(widgetPointNumber);
        gridLayoutPointNumber->setContentsMargins(0, 0, 0, 0);
        gridLayoutPointNumber->setObjectName(QString::fromUtf8("gridLayoutPointNumber"));
        gridLayoutPointNumber->setHorizontalSpacing(24);
        gridLayoutPointNumber->setVerticalSpacing(0);
        labelPointNumber = new QLabel(widgetPointNumber);
        labelPointNumber->setObjectName(QString::fromUtf8("labelPointNumber"));
        labelPointNumber->setMinimumSize(QSize(90, 0));
        labelPointNumber->setMaximumSize(QSize(90, 16777215));
        labelPointNumber->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutPointNumber->addWidget(labelPointNumber, 0, 0, 1, 1);

        radioButtonPointNumber4 = new QRadioButton(widgetPointNumber);
        radioButtonPointNumber4->setObjectName(QString::fromUtf8("radioButtonPointNumber4"));
        radioButtonPointNumber4->setMinimumSize(QSize(75, 0));
        radioButtonPointNumber4->setMaximumSize(QSize(75, 16777215));
        radioButtonPointNumber4->setLayoutDirection(Qt::LeftToRight);
        radioButtonPointNumber4->setChecked(true);

        gridLayoutPointNumber->addWidget(radioButtonPointNumber4, 0, 1, 1, 1);

        radioButtonPointNumber8 = new QRadioButton(widgetPointNumber);
        radioButtonPointNumber8->setObjectName(QString::fromUtf8("radioButtonPointNumber8"));
        radioButtonPointNumber8->setMinimumSize(QSize(75, 0));
        radioButtonPointNumber8->setMaximumSize(QSize(75, 16777215));
        radioButtonPointNumber8->setLayoutDirection(Qt::LeftToRight);
        radioButtonPointNumber8->setChecked(false);

        gridLayoutPointNumber->addWidget(radioButtonPointNumber8, 0, 2, 1, 1);

        radioButtonPointNumber16 = new QRadioButton(widgetPointNumber);
        radioButtonPointNumber16->setObjectName(QString::fromUtf8("radioButtonPointNumber16"));
        radioButtonPointNumber16->setMinimumSize(QSize(75, 0));
        radioButtonPointNumber16->setMaximumSize(QSize(75, 16777215));
        radioButtonPointNumber16->setLayoutDirection(Qt::LeftToRight);

        gridLayoutPointNumber->addWidget(radioButtonPointNumber16, 0, 3, 1, 1);


        verticalLayoutTransferFunction->addWidget(widgetPointNumber);

        widgetLayout = new QWidget(tabTransferFunction);
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
        widgetLayout->setMinimumSize(QSize(0, 0));
        widgetLayout->setMaximumSize(QSize(16777215, 32));
        gridLayoutLayout = new QGridLayout(widgetLayout);
        gridLayoutLayout->setContentsMargins(0, 0, 0, 0);
        gridLayoutLayout->setObjectName(QString::fromUtf8("gridLayoutLayout"));
        gridLayoutLayout->setHorizontalSpacing(24);
        gridLayoutLayout->setVerticalSpacing(0);
        labelLayout = new QLabel(widgetLayout);
        labelLayout->setObjectName(QString::fromUtf8("labelLayout"));
        labelLayout->setMinimumSize(QSize(90, 0));
        labelLayout->setMaximumSize(QSize(90, 16777215));
        labelLayout->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutLayout->addWidget(labelLayout, 0, 0, 1, 1);

        radioButtonLayoutNormal = new QRadioButton(widgetLayout);
        radioButtonLayoutNormal->setObjectName(QString::fromUtf8("radioButtonLayoutNormal"));
        radioButtonLayoutNormal->setMinimumSize(QSize(75, 0));
        radioButtonLayoutNormal->setMaximumSize(QSize(75, 16777215));
        radioButtonLayoutNormal->setLayoutDirection(Qt::LeftToRight);
        radioButtonLayoutNormal->setChecked(true);

        gridLayoutLayout->addWidget(radioButtonLayoutNormal, 0, 1, 1, 1);

        radioButtonLayoutVertical = new QRadioButton(widgetLayout);
        radioButtonLayoutVertical->setObjectName(QString::fromUtf8("radioButtonLayoutVertical"));
        radioButtonLayoutVertical->setMinimumSize(QSize(75, 0));
        radioButtonLayoutVertical->setMaximumSize(QSize(75, 16777215));
        radioButtonLayoutVertical->setLayoutDirection(Qt::LeftToRight);
        radioButtonLayoutVertical->setChecked(false);

        gridLayoutLayout->addWidget(radioButtonLayoutVertical, 0, 2, 1, 1);

        radioButtonLayoutWave = new QRadioButton(widgetLayout);
        radioButtonLayoutWave->setObjectName(QString::fromUtf8("radioButtonLayoutWave"));
        radioButtonLayoutWave->setMinimumSize(QSize(75, 0));
        radioButtonLayoutWave->setMaximumSize(QSize(75, 16777215));
        radioButtonLayoutWave->setLayoutDirection(Qt::LeftToRight);

        gridLayoutLayout->addWidget(radioButtonLayoutWave, 0, 3, 1, 1);


        verticalLayoutTransferFunction->addWidget(widgetLayout);

        widgetColorSpace = new QWidget(tabTransferFunction);
        widgetColorSpace->setObjectName(QString::fromUtf8("widgetColorSpace"));
        widgetColorSpace->setMinimumSize(QSize(0, 0));
        widgetColorSpace->setMaximumSize(QSize(16777215, 32));
        gridLayoutColorSpace = new QGridLayout(widgetColorSpace);
        gridLayoutColorSpace->setContentsMargins(0, 0, 0, 0);
        gridLayoutColorSpace->setObjectName(QString::fromUtf8("gridLayoutColorSpace"));
        gridLayoutColorSpace->setHorizontalSpacing(24);
        gridLayoutColorSpace->setVerticalSpacing(0);
        radioButtonColorSpaceLUV = new QRadioButton(widgetColorSpace);
        radioButtonColorSpaceLUV->setObjectName(QString::fromUtf8("radioButtonColorSpaceLUV"));
        radioButtonColorSpaceLUV->setMinimumSize(QSize(75, 0));
        radioButtonColorSpaceLUV->setMaximumSize(QSize(75, 16777215));
        radioButtonColorSpaceLUV->setLayoutDirection(Qt::LeftToRight);
        radioButtonColorSpaceLUV->setChecked(false);

        gridLayoutColorSpace->addWidget(radioButtonColorSpaceLUV, 0, 2, 1, 1);

        radioButtonColorSpaceRGB = new QRadioButton(widgetColorSpace);
        radioButtonColorSpaceRGB->setObjectName(QString::fromUtf8("radioButtonColorSpaceRGB"));
        radioButtonColorSpaceRGB->setMinimumSize(QSize(75, 0));
        radioButtonColorSpaceRGB->setMaximumSize(QSize(75, 16777215));
        radioButtonColorSpaceRGB->setLayoutDirection(Qt::LeftToRight);
        radioButtonColorSpaceRGB->setChecked(true);

        gridLayoutColorSpace->addWidget(radioButtonColorSpaceRGB, 0, 1, 1, 1);

        labelColorSpace = new QLabel(widgetColorSpace);
        labelColorSpace->setObjectName(QString::fromUtf8("labelColorSpace"));
        labelColorSpace->setMinimumSize(QSize(90, 0));
        labelColorSpace->setMaximumSize(QSize(90, 16777215));
        labelColorSpace->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutColorSpace->addWidget(labelColorSpace, 0, 0, 1, 1);

        radioButtonColorSpaceHSL = new QRadioButton(widgetColorSpace);
        radioButtonColorSpaceHSL->setObjectName(QString::fromUtf8("radioButtonColorSpaceHSL"));
        radioButtonColorSpaceHSL->setMinimumSize(QSize(75, 0));
        radioButtonColorSpaceHSL->setMaximumSize(QSize(75, 16777215));
        radioButtonColorSpaceHSL->setLayoutDirection(Qt::LeftToRight);

        gridLayoutColorSpace->addWidget(radioButtonColorSpaceHSL, 0, 3, 1, 1);


        verticalLayoutTransferFunction->addWidget(widgetColorSpace);

        tabWidgetSettings->addTab(tabTransferFunction, QString());
        tabView = new QProfile();
        tabView->setObjectName(QString::fromUtf8("tabView"));
        verticalLayoutView = new QVBoxLayout(tabView);
        verticalLayoutView->setObjectName(QString::fromUtf8("verticalLayoutView"));
        verticalLayoutView->setContentsMargins(-1, 12, -1, 12);
        widgetViewTranslation = new QWidget(tabView);
        widgetViewTranslation->setObjectName(QString::fromUtf8("widgetViewTranslation"));
        widgetViewTranslation->setMinimumSize(QSize(0, 0));
        widgetViewTranslation->setMaximumSize(QSize(16777215, 32));
        gridLayoutViewTranslation = new QGridLayout(widgetViewTranslation);
        gridLayoutViewTranslation->setObjectName(QString::fromUtf8("gridLayoutViewTranslation"));
        gridLayoutViewTranslation->setHorizontalSpacing(24);
        gridLayoutViewTranslation->setVerticalSpacing(0);
        gridLayoutViewTranslation->setContentsMargins(0, 0, 12, 0);
        labelViewTranslation = new QLabel(widgetViewTranslation);
        labelViewTranslation->setObjectName(QString::fromUtf8("labelViewTranslation"));
        labelViewTranslation->setMinimumSize(QSize(75, 0));
        labelViewTranslation->setMaximumSize(QSize(75, 16777215));
        labelViewTranslation->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutViewTranslation->addWidget(labelViewTranslation, 0, 0, 1, 1);

        doubleSpinBoxTranslationX = new QDoubleSpinBox(widgetViewTranslation);
        doubleSpinBoxTranslationX->setObjectName(QString::fromUtf8("doubleSpinBoxTranslationX"));
        doubleSpinBoxTranslationX->setMinimumSize(QSize(65, 0));
        doubleSpinBoxTranslationX->setMaximumSize(QSize(65, 16777215));
        doubleSpinBoxTranslationX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxTranslationX->setDecimals(5);
        doubleSpinBoxTranslationX->setMinimum(-10);
        doubleSpinBoxTranslationX->setMaximum(10);
        doubleSpinBoxTranslationX->setSingleStep(0.5);

        gridLayoutViewTranslation->addWidget(doubleSpinBoxTranslationX, 0, 2, 1, 1);

        doubleSpinBoxTranslationZ = new QDoubleSpinBox(widgetViewTranslation);
        doubleSpinBoxTranslationZ->setObjectName(QString::fromUtf8("doubleSpinBoxTranslationZ"));
        doubleSpinBoxTranslationZ->setMinimumSize(QSize(65, 0));
        doubleSpinBoxTranslationZ->setMaximumSize(QSize(65, 16777215));
        doubleSpinBoxTranslationZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxTranslationZ->setDecimals(5);
        doubleSpinBoxTranslationZ->setMinimum(-10);
        doubleSpinBoxTranslationZ->setMaximum(10);
        doubleSpinBoxTranslationZ->setSingleStep(0.5);
        doubleSpinBoxTranslationZ->setValue(-3);

        gridLayoutViewTranslation->addWidget(doubleSpinBoxTranslationZ, 0, 5, 1, 1);

        doubleSpinBoxTranslationY = new QDoubleSpinBox(widgetViewTranslation);
        doubleSpinBoxTranslationY->setObjectName(QString::fromUtf8("doubleSpinBoxTranslationY"));
        doubleSpinBoxTranslationY->setMinimumSize(QSize(65, 0));
        doubleSpinBoxTranslationY->setMaximumSize(QSize(65, 16777215));
        doubleSpinBoxTranslationY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxTranslationY->setDecimals(5);
        doubleSpinBoxTranslationY->setMinimum(-10);
        doubleSpinBoxTranslationY->setMaximum(10);
        doubleSpinBoxTranslationY->setSingleStep(0.5);

        gridLayoutViewTranslation->addWidget(doubleSpinBoxTranslationY, 0, 4, 1, 1);

        horizontalSpacerViewTranslation = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutViewTranslation->addItem(horizontalSpacerViewTranslation, 0, 6, 1, 1);


        verticalLayoutView->addWidget(widgetViewTranslation);

        widgetViewRotation = new QWidget(tabView);
        widgetViewRotation->setObjectName(QString::fromUtf8("widgetViewRotation"));
        widgetViewRotation->setMinimumSize(QSize(0, 0));
        widgetViewRotation->setMaximumSize(QSize(16777215, 76));
        gridLayoutViewRotation = new QGridLayout(widgetViewRotation);
        gridLayoutViewRotation->setObjectName(QString::fromUtf8("gridLayoutViewRotation"));
        gridLayoutViewRotation->setHorizontalSpacing(24);
        gridLayoutViewRotation->setVerticalSpacing(0);
        gridLayoutViewRotation->setContentsMargins(0, 0, 12, 0);
        doubleSpinBoxRotationX = new QDoubleSpinBox(widgetViewRotation);
        doubleSpinBoxRotationX->setObjectName(QString::fromUtf8("doubleSpinBoxRotationX"));
        doubleSpinBoxRotationX->setMinimumSize(QSize(65, 0));
        doubleSpinBoxRotationX->setMaximumSize(QSize(65, 16777215));
        doubleSpinBoxRotationX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxRotationX->setDecimals(4);
        doubleSpinBoxRotationX->setMinimum(-1);
        doubleSpinBoxRotationX->setMaximum(1);
        doubleSpinBoxRotationX->setSingleStep(0.05);
        doubleSpinBoxRotationX->setValue(1);

        gridLayoutViewRotation->addWidget(doubleSpinBoxRotationX, 0, 2, 1, 1);

        doubleSpinBoxRotationY = new QDoubleSpinBox(widgetViewRotation);
        doubleSpinBoxRotationY->setObjectName(QString::fromUtf8("doubleSpinBoxRotationY"));
        doubleSpinBoxRotationY->setMinimumSize(QSize(65, 0));
        doubleSpinBoxRotationY->setMaximumSize(QSize(65, 16777215));
        doubleSpinBoxRotationY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxRotationY->setDecimals(4);
        doubleSpinBoxRotationY->setMinimum(-1);
        doubleSpinBoxRotationY->setMaximum(1);
        doubleSpinBoxRotationY->setSingleStep(0.05);

        gridLayoutViewRotation->addWidget(doubleSpinBoxRotationY, 0, 4, 1, 1);

        labelViewRotation = new QLabel(widgetViewRotation);
        labelViewRotation->setObjectName(QString::fromUtf8("labelViewRotation"));
        labelViewRotation->setMinimumSize(QSize(75, 0));
        labelViewRotation->setMaximumSize(QSize(75, 16777215));
        labelViewRotation->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutViewRotation->addWidget(labelViewRotation, 0, 0, 2, 1);

        doubleSpinBoxRotationW = new QDoubleSpinBox(widgetViewRotation);
        doubleSpinBoxRotationW->setObjectName(QString::fromUtf8("doubleSpinBoxRotationW"));
        doubleSpinBoxRotationW->setMinimumSize(QSize(65, 0));
        doubleSpinBoxRotationW->setMaximumSize(QSize(65, 16777215));
        doubleSpinBoxRotationW->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxRotationW->setDecimals(4);
        doubleSpinBoxRotationW->setMinimum(-1);
        doubleSpinBoxRotationW->setMaximum(1);
        doubleSpinBoxRotationW->setSingleStep(0.05);

        gridLayoutViewRotation->addWidget(doubleSpinBoxRotationW, 1, 4, 1, 1);

        labelRotationZ = new QLabel(widgetViewRotation);
        labelRotationZ->setObjectName(QString::fromUtf8("labelRotationZ"));
        labelRotationZ->setMinimumSize(QSize(12, 0));
        labelRotationZ->setMaximumSize(QSize(12, 16777215));
        labelRotationZ->setAlignment(Qt::AlignCenter);

        gridLayoutViewRotation->addWidget(labelRotationZ, 1, 1, 1, 1);

        doubleSpinBoxRotationZ = new QDoubleSpinBox(widgetViewRotation);
        doubleSpinBoxRotationZ->setObjectName(QString::fromUtf8("doubleSpinBoxRotationZ"));
        doubleSpinBoxRotationZ->setMinimumSize(QSize(65, 0));
        doubleSpinBoxRotationZ->setMaximumSize(QSize(65, 16777215));
        doubleSpinBoxRotationZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxRotationZ->setDecimals(4);
        doubleSpinBoxRotationZ->setMinimum(-1);
        doubleSpinBoxRotationZ->setMaximum(1);
        doubleSpinBoxRotationZ->setSingleStep(0.05);

        gridLayoutViewRotation->addWidget(doubleSpinBoxRotationZ, 1, 2, 1, 1);

        labelRotationW = new QLabel(widgetViewRotation);
        labelRotationW->setObjectName(QString::fromUtf8("labelRotationW"));
        labelRotationW->setMinimumSize(QSize(12, 0));
        labelRotationW->setMaximumSize(QSize(12, 16777215));
        labelRotationW->setAlignment(Qt::AlignCenter);

        gridLayoutViewRotation->addWidget(labelRotationW, 1, 3, 1, 1);

        labelRotationY = new QLabel(widgetViewRotation);
        labelRotationY->setObjectName(QString::fromUtf8("labelRotationY"));
        labelRotationY->setMinimumSize(QSize(12, 0));
        labelRotationY->setMaximumSize(QSize(12, 16777215));
        labelRotationY->setAlignment(Qt::AlignCenter);

        gridLayoutViewRotation->addWidget(labelRotationY, 0, 3, 1, 1);

        labelRotationX = new QLabel(widgetViewRotation);
        labelRotationX->setObjectName(QString::fromUtf8("labelRotationX"));
        labelRotationX->setMinimumSize(QSize(12, 0));
        labelRotationX->setMaximumSize(QSize(12, 16777215));
        labelRotationX->setAlignment(Qt::AlignCenter);

        gridLayoutViewRotation->addWidget(labelRotationX, 0, 1, 1, 1);

        horizontalSpacerViewRotation = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutViewRotation->addItem(horizontalSpacerViewRotation, 0, 7, 2, 1);


        verticalLayoutView->addWidget(widgetViewRotation);

        widgetViewSize = new QWidget(tabView);
        widgetViewSize->setObjectName(QString::fromUtf8("widgetViewSize"));
        widgetViewSize->setMinimumSize(QSize(0, 0));
        widgetViewSize->setMaximumSize(QSize(16777215, 32));
        gridLayoutViewSize = new QGridLayout(widgetViewSize);
        gridLayoutViewSize->setObjectName(QString::fromUtf8("gridLayoutViewSize"));
        gridLayoutViewSize->setHorizontalSpacing(24);
        gridLayoutViewSize->setVerticalSpacing(0);
        gridLayoutViewSize->setContentsMargins(0, 0, 12, 0);
        labelSizeY = new QLabel(widgetViewSize);
        labelSizeY->setObjectName(QString::fromUtf8("labelSizeY"));
        labelSizeY->setMinimumSize(QSize(12, 0));
        labelSizeY->setMaximumSize(QSize(12, 16777215));
        labelSizeY->setAlignment(Qt::AlignCenter);

        gridLayoutViewSize->addWidget(labelSizeY, 0, 3, 1, 1);

        spinBoxViewSizeY = new QSpinBox(widgetViewSize);
        spinBoxViewSizeY->setObjectName(QString::fromUtf8("spinBoxViewSizeY"));
        spinBoxViewSizeY->setEnabled(false);
        spinBoxViewSizeY->setMinimumSize(QSize(65, 0));
        spinBoxViewSizeY->setMaximumSize(QSize(65, 16777215));
        spinBoxViewSizeY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxViewSizeY->setReadOnly(false);
        spinBoxViewSizeY->setMinimum(1);
        spinBoxViewSizeY->setMaximum(2048);
        spinBoxViewSizeY->setSingleStep(64);
        spinBoxViewSizeY->setValue(512);

        gridLayoutViewSize->addWidget(spinBoxViewSizeY, 0, 4, 1, 1);

        labelViewSize = new QLabel(widgetViewSize);
        labelViewSize->setObjectName(QString::fromUtf8("labelViewSize"));
        labelViewSize->setMinimumSize(QSize(75, 0));
        labelViewSize->setMaximumSize(QSize(75, 16777215));
        labelViewSize->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutViewSize->addWidget(labelViewSize, 0, 0, 1, 1);

        spinBoxViewSizeX = new QSpinBox(widgetViewSize);
        spinBoxViewSizeX->setObjectName(QString::fromUtf8("spinBoxViewSizeX"));
        spinBoxViewSizeX->setEnabled(false);
        spinBoxViewSizeX->setMinimumSize(QSize(65, 0));
        spinBoxViewSizeX->setMaximumSize(QSize(65, 16777215));
        spinBoxViewSizeX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxViewSizeX->setReadOnly(false);
        spinBoxViewSizeX->setMinimum(1);
        spinBoxViewSizeX->setMaximum(2048);
        spinBoxViewSizeX->setSingleStep(64);
        spinBoxViewSizeX->setValue(512);

        gridLayoutViewSize->addWidget(spinBoxViewSizeX, 0, 2, 1, 1);

        labelSizeX = new QLabel(widgetViewSize);
        labelSizeX->setObjectName(QString::fromUtf8("labelSizeX"));
        labelSizeX->setMinimumSize(QSize(12, 0));
        labelSizeX->setMaximumSize(QSize(12, 16777215));
        labelSizeX->setAlignment(Qt::AlignCenter);

        gridLayoutViewSize->addWidget(labelSizeX, 0, 1, 1, 1);

        horizontalSpacerViewSize = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutViewSize->addItem(horizontalSpacerViewSize, 0, 5, 1, 1);


        verticalLayoutView->addWidget(widgetViewSize);

        tabWidgetSettings->addTab(tabView, QString());
        tabProjection = new QProfile();
        tabProjection->setObjectName(QString::fromUtf8("tabProjection"));
        verticalLayoutProjection = new QVBoxLayout(tabProjection);
        verticalLayoutProjection->setObjectName(QString::fromUtf8("verticalLayoutProjection"));
        verticalLayoutProjection->setContentsMargins(-1, 12, -1, 12);
        widgetProjectionMode = new QWidget(tabProjection);
        widgetProjectionMode->setObjectName(QString::fromUtf8("widgetProjectionMode"));
        widgetProjectionMode->setMinimumSize(QSize(0, 0));
        widgetProjectionMode->setMaximumSize(QSize(16777215, 32));
        gridLayoutProjectionMode = new QGridLayout(widgetProjectionMode);
        gridLayoutProjectionMode->setContentsMargins(0, 0, 0, 0);
        gridLayoutProjectionMode->setObjectName(QString::fromUtf8("gridLayoutProjectionMode"));
        gridLayoutProjectionMode->setHorizontalSpacing(24);
        gridLayoutProjectionMode->setVerticalSpacing(0);
        radioButtonPerspective = new QRadioButton(widgetProjectionMode);
        radioButtonPerspective->setObjectName(QString::fromUtf8("radioButtonPerspective"));
        radioButtonPerspective->setMinimumSize(QSize(90, 0));
        radioButtonPerspective->setMaximumSize(QSize(90, 16777215));
        radioButtonPerspective->setChecked(true);

        gridLayoutProjectionMode->addWidget(radioButtonPerspective, 0, 2, 1, 1);

        radioButtonOrthogonal = new QRadioButton(widgetProjectionMode);
        radioButtonOrthogonal->setObjectName(QString::fromUtf8("radioButtonOrthogonal"));
        radioButtonOrthogonal->setMinimumSize(QSize(90, 0));
        radioButtonOrthogonal->setMaximumSize(QSize(90, 16777215));
        radioButtonOrthogonal->setChecked(false);

        gridLayoutProjectionMode->addWidget(radioButtonOrthogonal, 0, 3, 1, 1);

        labelProjectionMode = new QLabel(widgetProjectionMode);
        labelProjectionMode->setObjectName(QString::fromUtf8("labelProjectionMode"));
        labelProjectionMode->setMinimumSize(QSize(75, 0));
        labelProjectionMode->setMaximumSize(QSize(75, 16777215));
        labelProjectionMode->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutProjectionMode->addWidget(labelProjectionMode, 0, 0, 1, 1);

        horizontalSpacerProjectionMode = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutProjectionMode->addItem(horizontalSpacerProjectionMode, 0, 4, 1, 1);


        verticalLayoutProjection->addWidget(widgetProjectionMode);

        widgetProjectionPerspective = new QWidget(tabProjection);
        widgetProjectionPerspective->setObjectName(QString::fromUtf8("widgetProjectionPerspective"));
        widgetProjectionPerspective->setMinimumSize(QSize(0, 0));
        widgetProjectionPerspective->setMaximumSize(QSize(16777215, 32));
        gridLayoutProjectionPerspective = new QGridLayout(widgetProjectionPerspective);
        gridLayoutProjectionPerspective->setObjectName(QString::fromUtf8("gridLayoutProjectionPerspective"));
        gridLayoutProjectionPerspective->setHorizontalSpacing(24);
        gridLayoutProjectionPerspective->setVerticalSpacing(0);
        gridLayoutProjectionPerspective->setContentsMargins(0, 0, 12, 0);
        doubleSpinBoxZNear = new QDoubleSpinBox(widgetProjectionPerspective);
        doubleSpinBoxZNear->setObjectName(QString::fromUtf8("doubleSpinBoxZNear"));
        doubleSpinBoxZNear->setMinimumSize(QSize(60, 0));
        doubleSpinBoxZNear->setMaximumSize(QSize(60, 16777215));
        doubleSpinBoxZNear->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxZNear->setDecimals(3);
        doubleSpinBoxZNear->setMinimum(0.001);
        doubleSpinBoxZNear->setMaximum(1);
        doubleSpinBoxZNear->setSingleStep(0.05);
        doubleSpinBoxZNear->setValue(0.1);

        gridLayoutProjectionPerspective->addWidget(doubleSpinBoxZNear, 0, 2, 1, 1);

        doubleSpinBoxZFar = new QDoubleSpinBox(widgetProjectionPerspective);
        doubleSpinBoxZFar->setObjectName(QString::fromUtf8("doubleSpinBoxZFar"));
        doubleSpinBoxZFar->setMinimumSize(QSize(60, 0));
        doubleSpinBoxZFar->setMaximumSize(QSize(60, 16777215));
        doubleSpinBoxZFar->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxZFar->setDecimals(0);
        doubleSpinBoxZFar->setMinimum(1);
        doubleSpinBoxZFar->setMaximum(100000);
        doubleSpinBoxZFar->setSingleStep(5000);
        doubleSpinBoxZFar->setValue(10000);

        gridLayoutProjectionPerspective->addWidget(doubleSpinBoxZFar, 0, 4, 1, 1);

        labelPerspective = new QLabel(widgetProjectionPerspective);
        labelPerspective->setObjectName(QString::fromUtf8("labelPerspective"));
        labelPerspective->setMinimumSize(QSize(75, 0));
        labelPerspective->setMaximumSize(QSize(75, 16777215));
        labelPerspective->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutProjectionPerspective->addWidget(labelPerspective, 0, 0, 1, 1);

        labelZNear = new QLabel(widgetProjectionPerspective);
        labelZNear->setObjectName(QString::fromUtf8("labelZNear"));
        labelZNear->setMinimumSize(QSize(45, 0));
        labelZNear->setMaximumSize(QSize(45, 16777215));
        labelZNear->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutProjectionPerspective->addWidget(labelZNear, 0, 1, 1, 1);

        labelZFar = new QLabel(widgetProjectionPerspective);
        labelZFar->setObjectName(QString::fromUtf8("labelZFar"));
        labelZFar->setMinimumSize(QSize(45, 0));
        labelZFar->setMaximumSize(QSize(45, 16777215));
        labelZFar->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutProjectionPerspective->addWidget(labelZFar, 0, 3, 1, 1);


        verticalLayoutProjection->addWidget(widgetProjectionPerspective);

        widgetProjectionFOVY = new QWidget(tabProjection);
        widgetProjectionFOVY->setObjectName(QString::fromUtf8("widgetProjectionFOVY"));
        widgetProjectionFOVY->setMinimumSize(QSize(0, 0));
        widgetProjectionFOVY->setMaximumSize(QSize(16777215, 32));
        gridLayoutProjectionFOVY = new QGridLayout(widgetProjectionFOVY);
        gridLayoutProjectionFOVY->setObjectName(QString::fromUtf8("gridLayoutProjectionFOVY"));
        gridLayoutProjectionFOVY->setHorizontalSpacing(24);
        gridLayoutProjectionFOVY->setVerticalSpacing(0);
        gridLayoutProjectionFOVY->setContentsMargins(0, 0, 12, 0);
        labelFOVY = new QLabel(widgetProjectionFOVY);
        labelFOVY->setObjectName(QString::fromUtf8("labelFOVY"));
        labelFOVY->setMinimumSize(QSize(75, 0));
        labelFOVY->setMaximumSize(QSize(75, 16777215));
        labelFOVY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutProjectionFOVY->addWidget(labelFOVY, 0, 0, 1, 1);

        horizontalSliderFOVY = new QSlider(widgetProjectionFOVY);
        horizontalSliderFOVY->setObjectName(QString::fromUtf8("horizontalSliderFOVY"));
        horizontalSliderFOVY->setMinimum(1);
        horizontalSliderFOVY->setMaximum(179);
        horizontalSliderFOVY->setSingleStep(1);
        horizontalSliderFOVY->setPageStep(9);
        horizontalSliderFOVY->setValue(60);
        horizontalSliderFOVY->setOrientation(Qt::Horizontal);

        gridLayoutProjectionFOVY->addWidget(horizontalSliderFOVY, 0, 1, 1, 1);

        spinBoxFOVY = new QSpinBox(widgetProjectionFOVY);
        spinBoxFOVY->setObjectName(QString::fromUtf8("spinBoxFOVY"));
        spinBoxFOVY->setMinimumSize(QSize(45, 0));
        spinBoxFOVY->setMaximumSize(QSize(45, 16777215));
        spinBoxFOVY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxFOVY->setMinimum(1);
        spinBoxFOVY->setMaximum(179);
        spinBoxFOVY->setSingleStep(9);
        spinBoxFOVY->setValue(60);

        gridLayoutProjectionFOVY->addWidget(spinBoxFOVY, 0, 2, 1, 1);


        verticalLayoutProjection->addWidget(widgetProjectionFOVY);

        widgetProjectionOrthogonal = new QWidget(tabProjection);
        widgetProjectionOrthogonal->setObjectName(QString::fromUtf8("widgetProjectionOrthogonal"));
        widgetProjectionOrthogonal->setMinimumSize(QSize(0, 0));
        widgetProjectionOrthogonal->setMaximumSize(QSize(16777215, 32));
        gridLayoutProjectionOrthogonal = new QGridLayout(widgetProjectionOrthogonal);
        gridLayoutProjectionOrthogonal->setObjectName(QString::fromUtf8("gridLayoutProjectionOrthogonal"));
        gridLayoutProjectionOrthogonal->setHorizontalSpacing(24);
        gridLayoutProjectionOrthogonal->setVerticalSpacing(0);
        gridLayoutProjectionOrthogonal->setContentsMargins(0, 0, 12, 0);
        labelOrthogonal = new QLabel(widgetProjectionOrthogonal);
        labelOrthogonal->setObjectName(QString::fromUtf8("labelOrthogonal"));
        labelOrthogonal->setMinimumSize(QSize(75, 0));
        labelOrthogonal->setMaximumSize(QSize(75, 16777215));
        labelOrthogonal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutProjectionOrthogonal->addWidget(labelOrthogonal, 0, 0, 1, 1);

        horizontalSliderOrthogonal = new QSlider(widgetProjectionOrthogonal);
        horizontalSliderOrthogonal->setObjectName(QString::fromUtf8("horizontalSliderOrthogonal"));
        horizontalSliderOrthogonal->setMinimum(1);
        horizontalSliderOrthogonal->setMaximum(100);
        horizontalSliderOrthogonal->setSingleStep(1);
        horizontalSliderOrthogonal->setPageStep(5);
        horizontalSliderOrthogonal->setValue(85);
        horizontalSliderOrthogonal->setOrientation(Qt::Horizontal);

        gridLayoutProjectionOrthogonal->addWidget(horizontalSliderOrthogonal, 0, 1, 1, 1);

        spinBoxOrthogonal = new QSpinBox(widgetProjectionOrthogonal);
        spinBoxOrthogonal->setObjectName(QString::fromUtf8("spinBoxOrthogonal"));
        spinBoxOrthogonal->setMinimumSize(QSize(45, 0));
        spinBoxOrthogonal->setMaximumSize(QSize(45, 16777215));
        spinBoxOrthogonal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxOrthogonal->setMinimum(1);
        spinBoxOrthogonal->setMaximum(100);
        spinBoxOrthogonal->setSingleStep(5);
        spinBoxOrthogonal->setValue(85);

        gridLayoutProjectionOrthogonal->addWidget(spinBoxOrthogonal, 0, 2, 1, 1);


        verticalLayoutProjection->addWidget(widgetProjectionOrthogonal);

        tabWidgetSettings->addTab(tabProjection, QString());
        tabRayCasting = new QProfile();
        tabRayCasting->setObjectName(QString::fromUtf8("tabRayCasting"));
        verticalLayoutRayCasting = new QVBoxLayout(tabRayCasting);
        verticalLayoutRayCasting->setObjectName(QString::fromUtf8("verticalLayoutRayCasting"));
        verticalLayoutRayCasting->setContentsMargins(-1, 12, -1, 12);
        widgetRayCastingMode = new QWidget(tabRayCasting);
        widgetRayCastingMode->setObjectName(QString::fromUtf8("widgetRayCastingMode"));
        widgetRayCastingMode->setMinimumSize(QSize(0, 0));
        widgetRayCastingMode->setMaximumSize(QSize(16777215, 32));
        gridLayoutRayCastingMode = new QGridLayout(widgetRayCastingMode);
        gridLayoutRayCastingMode->setContentsMargins(0, 0, 0, 0);
        gridLayoutRayCastingMode->setObjectName(QString::fromUtf8("gridLayoutRayCastingMode"));
        gridLayoutRayCastingMode->setHorizontalSpacing(24);
        gridLayoutRayCastingMode->setVerticalSpacing(0);
        radioButtonNormal = new QRadioButton(widgetRayCastingMode);
        radioButtonNormal->setObjectName(QString::fromUtf8("radioButtonNormal"));
        radioButtonNormal->setMinimumSize(QSize(65, 0));
        radioButtonNormal->setMaximumSize(QSize(65, 16777215));
        radioButtonNormal->setLayoutDirection(Qt::LeftToRight);
        radioButtonNormal->setChecked(true);

        gridLayoutRayCastingMode->addWidget(radioButtonNormal, 0, 1, 1, 1);

        radioButtonPreIntegration = new QRadioButton(widgetRayCastingMode);
        radioButtonPreIntegration->setObjectName(QString::fromUtf8("radioButtonPreIntegration"));
        radioButtonPreIntegration->setMinimumSize(QSize(65, 0));
        radioButtonPreIntegration->setMaximumSize(QSize(65, 16777215));
        radioButtonPreIntegration->setLayoutDirection(Qt::LeftToRight);

        gridLayoutRayCastingMode->addWidget(radioButtonPreIntegration, 0, 2, 1, 1);

        horizontalSpacerRayCastingMode = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutRayCastingMode->addItem(horizontalSpacerRayCastingMode, 0, 4, 1, 1);

        labelRayCastingMode = new QLabel(widgetRayCastingMode);
        labelRayCastingMode->setObjectName(QString::fromUtf8("labelRayCastingMode"));
        labelRayCastingMode->setMinimumSize(QSize(75, 0));
        labelRayCastingMode->setMaximumSize(QSize(75, 16777215));
        labelRayCastingMode->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutRayCastingMode->addWidget(labelRayCastingMode, 0, 0, 1, 1);

        radioButtonFeature = new QRadioButton(widgetRayCastingMode);
        radioButtonFeature->setObjectName(QString::fromUtf8("radioButtonFeature"));
        radioButtonFeature->setMinimumSize(QSize(65, 0));
        radioButtonFeature->setMaximumSize(QSize(65, 16777215));
        radioButtonFeature->setLayoutDirection(Qt::LeftToRight);

        gridLayoutRayCastingMode->addWidget(radioButtonFeature, 0, 3, 1, 1);


        verticalLayoutRayCasting->addWidget(widgetRayCastingMode);

        widgetRayCastingObject = new QWidget(tabRayCasting);
        widgetRayCastingObject->setObjectName(QString::fromUtf8("widgetRayCastingObject"));
        widgetRayCastingObject->setMinimumSize(QSize(0, 0));
        widgetRayCastingObject->setMaximumSize(QSize(16777215, 32));
        gridLayoutRayCastingObject = new QGridLayout(widgetRayCastingObject);
        gridLayoutRayCastingObject->setContentsMargins(0, 0, 0, 0);
        gridLayoutRayCastingObject->setObjectName(QString::fromUtf8("gridLayoutRayCastingObject"));
        gridLayoutRayCastingObject->setHorizontalSpacing(24);
        gridLayoutRayCastingObject->setVerticalSpacing(0);
        labelRayCastingObject = new QLabel(widgetRayCastingObject);
        labelRayCastingObject->setObjectName(QString::fromUtf8("labelRayCastingObject"));
        labelRayCastingObject->setMinimumSize(QSize(75, 0));
        labelRayCastingObject->setMaximumSize(QSize(75, 16777215));
        labelRayCastingObject->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutRayCastingObject->addWidget(labelRayCastingObject, 0, 0, 1, 1);

        radioButtonRayCastingObjectAll = new QRadioButton(widgetRayCastingObject);
        radioButtonRayCastingObjectAll->setObjectName(QString::fromUtf8("radioButtonRayCastingObjectAll"));
        radioButtonRayCastingObjectAll->setMinimumSize(QSize(30, 0));
        radioButtonRayCastingObjectAll->setMaximumSize(QSize(30, 16777215));
        radioButtonRayCastingObjectAll->setChecked(true);

        gridLayoutRayCastingObject->addWidget(radioButtonRayCastingObjectAll, 0, 1, 1, 1);

        radioButtonRayCastingObjectFore = new QRadioButton(widgetRayCastingObject);
        radioButtonRayCastingObjectFore->setObjectName(QString::fromUtf8("radioButtonRayCastingObjectFore"));
        radioButtonRayCastingObjectFore->setMinimumSize(QSize(30, 0));
        radioButtonRayCastingObjectFore->setMaximumSize(QSize(30, 16777215));
        radioButtonRayCastingObjectFore->setChecked(false);

        gridLayoutRayCastingObject->addWidget(radioButtonRayCastingObjectFore, 0, 2, 1, 1);

        radioButtonRayCastingObjectBack = new QRadioButton(widgetRayCastingObject);
        radioButtonRayCastingObjectBack->setObjectName(QString::fromUtf8("radioButtonRayCastingObjectBack"));
        radioButtonRayCastingObjectBack->setMinimumSize(QSize(30, 0));
        radioButtonRayCastingObjectBack->setMaximumSize(QSize(30, 16777215));

        gridLayoutRayCastingObject->addWidget(radioButtonRayCastingObjectBack, 0, 3, 1, 1);

        radioButtonRayCastingObjectTag = new QRadioButton(widgetRayCastingObject);
        radioButtonRayCastingObjectTag->setObjectName(QString::fromUtf8("radioButtonRayCastingObjectTag"));
        radioButtonRayCastingObjectTag->setMinimumSize(QSize(30, 0));
        radioButtonRayCastingObjectTag->setMaximumSize(QSize(30, 16777215));
        radioButtonRayCastingObjectTag->setChecked(false);

        gridLayoutRayCastingObject->addWidget(radioButtonRayCastingObjectTag, 0, 6, 1, 1);

        radioButtonRayCastingObjectCut = new QRadioButton(widgetRayCastingObject);
        radioButtonRayCastingObjectCut->setObjectName(QString::fromUtf8("radioButtonRayCastingObjectCut"));
        radioButtonRayCastingObjectCut->setMinimumSize(QSize(30, 0));
        radioButtonRayCastingObjectCut->setMaximumSize(QSize(30, 16777215));
        radioButtonRayCastingObjectCut->setChecked(false);

        gridLayoutRayCastingObject->addWidget(radioButtonRayCastingObjectCut, 0, 5, 1, 1);

        horizontalSpacerRayCastingObject = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutRayCastingObject->addItem(horizontalSpacerRayCastingObject, 0, 7, 1, 1);


        verticalLayoutRayCasting->addWidget(widgetRayCastingObject);

        widgetRayCastingSampleApproximation = new QWidget(tabRayCasting);
        widgetRayCastingSampleApproximation->setObjectName(QString::fromUtf8("widgetRayCastingSampleApproximation"));
        widgetRayCastingSampleApproximation->setMinimumSize(QSize(0, 0));
        widgetRayCastingSampleApproximation->setMaximumSize(QSize(16777215, 32));
        gridLayoutRayCastingSampleApproximation = new QGridLayout(widgetRayCastingSampleApproximation);
        gridLayoutRayCastingSampleApproximation->setObjectName(QString::fromUtf8("gridLayoutRayCastingSampleApproximation"));
        gridLayoutRayCastingSampleApproximation->setHorizontalSpacing(24);
        gridLayoutRayCastingSampleApproximation->setVerticalSpacing(0);
        gridLayoutRayCastingSampleApproximation->setContentsMargins(0, 0, 12, 0);
        labelSampleApproximation = new QLabel(widgetRayCastingSampleApproximation);
        labelSampleApproximation->setObjectName(QString::fromUtf8("labelSampleApproximation"));
        labelSampleApproximation->setMinimumSize(QSize(75, 0));
        labelSampleApproximation->setMaximumSize(QSize(75, 16777215));
        labelSampleApproximation->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutRayCastingSampleApproximation->addWidget(labelSampleApproximation, 0, 0, 1, 1);

        labelSampleRatio = new QLabel(widgetRayCastingSampleApproximation);
        labelSampleRatio->setObjectName(QString::fromUtf8("labelSampleRatio"));
        labelSampleRatio->setMinimumSize(QSize(45, 0));
        labelSampleRatio->setMaximumSize(QSize(45, 16777215));
        labelSampleRatio->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutRayCastingSampleApproximation->addWidget(labelSampleRatio, 0, 5, 1, 1);

        spinBoxSampleScale = new QSpinBox(widgetRayCastingSampleApproximation);
        spinBoxSampleScale->setObjectName(QString::fromUtf8("spinBoxSampleScale"));
        spinBoxSampleScale->setMinimumSize(QSize(60, 0));
        spinBoxSampleScale->setMaximumSize(QSize(60, 16777215));
        spinBoxSampleScale->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxSampleScale->setMinimum(64);
        spinBoxSampleScale->setMaximum(4096);
        spinBoxSampleScale->setSingleStep(50);
        spinBoxSampleScale->setValue(128);

        gridLayoutRayCastingSampleApproximation->addWidget(spinBoxSampleScale, 0, 4, 1, 1);

        doubleSpinBoxSampleRatio = new QDoubleSpinBox(widgetRayCastingSampleApproximation);
        doubleSpinBoxSampleRatio->setObjectName(QString::fromUtf8("doubleSpinBoxSampleRatio"));
        doubleSpinBoxSampleRatio->setMinimumSize(QSize(60, 0));
        doubleSpinBoxSampleRatio->setMaximumSize(QSize(60, 16777215));
        doubleSpinBoxSampleRatio->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxSampleRatio->setDecimals(2);
        doubleSpinBoxSampleRatio->setMinimum(0.01);
        doubleSpinBoxSampleRatio->setMaximum(1);
        doubleSpinBoxSampleRatio->setSingleStep(0.05);
        doubleSpinBoxSampleRatio->setValue(1);

        gridLayoutRayCastingSampleApproximation->addWidget(doubleSpinBoxSampleRatio, 0, 6, 1, 1);

        horizontalSpacerSampleApproximation = new QSpacerItem(24, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutRayCastingSampleApproximation->addItem(horizontalSpacerSampleApproximation, 0, 1, 1, 1);

        labelSampleScale = new QLabel(widgetRayCastingSampleApproximation);
        labelSampleScale->setObjectName(QString::fromUtf8("labelSampleScale"));
        labelSampleScale->setMinimumSize(QSize(45, 0));
        labelSampleScale->setMaximumSize(QSize(45, 16777215));
        labelSampleScale->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutRayCastingSampleApproximation->addWidget(labelSampleScale, 0, 3, 1, 1);


        verticalLayoutRayCasting->addWidget(widgetRayCastingSampleApproximation);

        widgetRayCastingSampleNumber = new QWidget(tabRayCasting);
        widgetRayCastingSampleNumber->setObjectName(QString::fromUtf8("widgetRayCastingSampleNumber"));
        widgetRayCastingSampleNumber->setMinimumSize(QSize(0, 0));
        widgetRayCastingSampleNumber->setMaximumSize(QSize(16777215, 32));
        gridLayoutRayCastingSampleNumber = new QGridLayout(widgetRayCastingSampleNumber);
        gridLayoutRayCastingSampleNumber->setObjectName(QString::fromUtf8("gridLayoutRayCastingSampleNumber"));
        gridLayoutRayCastingSampleNumber->setHorizontalSpacing(24);
        gridLayoutRayCastingSampleNumber->setVerticalSpacing(0);
        gridLayoutRayCastingSampleNumber->setContentsMargins(0, 0, 12, 0);
        labelSampleNumber = new QLabel(widgetRayCastingSampleNumber);
        labelSampleNumber->setObjectName(QString::fromUtf8("labelSampleNumber"));
        labelSampleNumber->setMinimumSize(QSize(75, 0));
        labelSampleNumber->setMaximumSize(QSize(75, 16777215));
        labelSampleNumber->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutRayCastingSampleNumber->addWidget(labelSampleNumber, 0, 0, 1, 1);

        spinBoxSampleNumber = new QSpinBox(widgetRayCastingSampleNumber);
        spinBoxSampleNumber->setObjectName(QString::fromUtf8("spinBoxSampleNumber"));
        spinBoxSampleNumber->setMinimumSize(QSize(45, 0));
        spinBoxSampleNumber->setMaximumSize(QSize(45, 16777215));
        spinBoxSampleNumber->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxSampleNumber->setMinimum(64);
        spinBoxSampleNumber->setMaximum(4096);
        spinBoxSampleNumber->setSingleStep(50);
        spinBoxSampleNumber->setValue(512);

        gridLayoutRayCastingSampleNumber->addWidget(spinBoxSampleNumber, 0, 2, 1, 1);

        horizontalSliderSampleNumber = new QSlider(widgetRayCastingSampleNumber);
        horizontalSliderSampleNumber->setObjectName(QString::fromUtf8("horizontalSliderSampleNumber"));
        horizontalSliderSampleNumber->setMinimum(64);
        horizontalSliderSampleNumber->setMaximum(4096);
        horizontalSliderSampleNumber->setSingleStep(1);
        horizontalSliderSampleNumber->setPageStep(50);
        horizontalSliderSampleNumber->setValue(512);
        horizontalSliderSampleNumber->setOrientation(Qt::Horizontal);

        gridLayoutRayCastingSampleNumber->addWidget(horizontalSliderSampleNumber, 0, 1, 1, 1);


        verticalLayoutRayCasting->addWidget(widgetRayCastingSampleNumber);

        tabWidgetSettings->addTab(tabRayCasting, QString());
        tabPreIntegration = new QProfile();
        tabPreIntegration->setObjectName(QString::fromUtf8("tabPreIntegration"));
        verticalLayoutPreIntegration = new QVBoxLayout(tabPreIntegration);
        verticalLayoutPreIntegration->setObjectName(QString::fromUtf8("verticalLayoutPreIntegration"));
        verticalLayoutPreIntegration->setContentsMargins(-1, 12, -1, 12);
        widgetPreIntegrationBias = new QWidget(tabPreIntegration);
        widgetPreIntegrationBias->setObjectName(QString::fromUtf8("widgetPreIntegrationBias"));
        widgetPreIntegrationBias->setMinimumSize(QSize(0, 0));
        widgetPreIntegrationBias->setMaximumSize(QSize(16777215, 32));
        gridLayoutPreIntegrationBias = new QGridLayout(widgetPreIntegrationBias);
        gridLayoutPreIntegrationBias->setObjectName(QString::fromUtf8("gridLayoutPreIntegrationBias"));
        gridLayoutPreIntegrationBias->setHorizontalSpacing(24);
        gridLayoutPreIntegrationBias->setVerticalSpacing(0);
        gridLayoutPreIntegrationBias->setContentsMargins(0, 0, 12, 0);
        spinBoxPreIntegrationBias = new QSpinBox(widgetPreIntegrationBias);
        spinBoxPreIntegrationBias->setObjectName(QString::fromUtf8("spinBoxPreIntegrationBias"));
        spinBoxPreIntegrationBias->setMinimumSize(QSize(60, 0));
        spinBoxPreIntegrationBias->setMaximumSize(QSize(60, 16777215));
        spinBoxPreIntegrationBias->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxPreIntegrationBias->setMinimum(4);
        spinBoxPreIntegrationBias->setMaximum(32);
        spinBoxPreIntegrationBias->setSingleStep(2);

        gridLayoutPreIntegrationBias->addWidget(spinBoxPreIntegrationBias, 0, 2, 1, 1);

        horizontalSliderPreIntegrationBias = new QSlider(widgetPreIntegrationBias);
        horizontalSliderPreIntegrationBias->setObjectName(QString::fromUtf8("horizontalSliderPreIntegrationBias"));
        horizontalSliderPreIntegrationBias->setMinimum(4);
        horizontalSliderPreIntegrationBias->setMaximum(32);
        horizontalSliderPreIntegrationBias->setSingleStep(1);
        horizontalSliderPreIntegrationBias->setPageStep(2);
        horizontalSliderPreIntegrationBias->setValue(4);
        horizontalSliderPreIntegrationBias->setSliderPosition(4);
        horizontalSliderPreIntegrationBias->setOrientation(Qt::Horizontal);

        gridLayoutPreIntegrationBias->addWidget(horizontalSliderPreIntegrationBias, 0, 1, 1, 1);

        labelPreIntegrationBias = new QLabel(widgetPreIntegrationBias);
        labelPreIntegrationBias->setObjectName(QString::fromUtf8("labelPreIntegrationBias"));
        labelPreIntegrationBias->setMinimumSize(QSize(60, 0));
        labelPreIntegrationBias->setMaximumSize(QSize(60, 16777215));
        labelPreIntegrationBias->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutPreIntegrationBias->addWidget(labelPreIntegrationBias, 0, 0, 1, 1);


        verticalLayoutPreIntegration->addWidget(widgetPreIntegrationBias);

        widgetPreIntegrationScale = new QWidget(tabPreIntegration);
        widgetPreIntegrationScale->setObjectName(QString::fromUtf8("widgetPreIntegrationScale"));
        widgetPreIntegrationScale->setMinimumSize(QSize(0, 0));
        widgetPreIntegrationScale->setMaximumSize(QSize(16777215, 32));
        gridLayoutPreIntegrationScale = new QGridLayout(widgetPreIntegrationScale);
        gridLayoutPreIntegrationScale->setObjectName(QString::fromUtf8("gridLayoutPreIntegrationScale"));
        gridLayoutPreIntegrationScale->setHorizontalSpacing(24);
        gridLayoutPreIntegrationScale->setVerticalSpacing(0);
        gridLayoutPreIntegrationScale->setContentsMargins(0, 0, 12, 0);
        horizontalSliderPreIntegrationScale = new QSlider(widgetPreIntegrationScale);
        horizontalSliderPreIntegrationScale->setObjectName(QString::fromUtf8("horizontalSliderPreIntegrationScale"));
        horizontalSliderPreIntegrationScale->setMinimum(16);
        horizontalSliderPreIntegrationScale->setMaximum(1024);
        horizontalSliderPreIntegrationScale->setSingleStep(1);
        horizontalSliderPreIntegrationScale->setPageStep(50);
        horizontalSliderPreIntegrationScale->setValue(256);
        horizontalSliderPreIntegrationScale->setOrientation(Qt::Horizontal);

        gridLayoutPreIntegrationScale->addWidget(horizontalSliderPreIntegrationScale, 0, 1, 1, 1);

        labelPreIntegrationScale = new QLabel(widgetPreIntegrationScale);
        labelPreIntegrationScale->setObjectName(QString::fromUtf8("labelPreIntegrationScale"));
        labelPreIntegrationScale->setMinimumSize(QSize(60, 0));
        labelPreIntegrationScale->setMaximumSize(QSize(60, 16777215));
        labelPreIntegrationScale->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutPreIntegrationScale->addWidget(labelPreIntegrationScale, 0, 0, 1, 1);

        spinBoxPreIntegrationScale = new QSpinBox(widgetPreIntegrationScale);
        spinBoxPreIntegrationScale->setObjectName(QString::fromUtf8("spinBoxPreIntegrationScale"));
        spinBoxPreIntegrationScale->setMinimumSize(QSize(60, 0));
        spinBoxPreIntegrationScale->setMaximumSize(QSize(60, 16777215));
        spinBoxPreIntegrationScale->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxPreIntegrationScale->setMinimum(16);
        spinBoxPreIntegrationScale->setMaximum(1024);
        spinBoxPreIntegrationScale->setSingleStep(50);
        spinBoxPreIntegrationScale->setValue(256);

        gridLayoutPreIntegrationScale->addWidget(spinBoxPreIntegrationScale, 0, 2, 1, 1);


        verticalLayoutPreIntegration->addWidget(widgetPreIntegrationScale);

        tabWidgetSettings->addTab(tabPreIntegration, QString());

        gridLayoutRendering->addWidget(tabWidgetSettings, 0, 0, 1, 1);

        splitter->addWidget(groupBoxRendering);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(QGCPanel);
        QObject::connect(verticalSliderWindowWidth, SIGNAL(valueChanged(int)), labelWindowWidth, SLOT(setNum(int)));
        QObject::connect(verticalSliderWindowLevel, SIGNAL(valueChanged(int)), labelWindowLevel, SLOT(setNum(int)));
        QObject::connect(horizontalSliderOrthogonal, SIGNAL(valueChanged(int)), spinBoxOrthogonal, SLOT(setValue(int)));
        QObject::connect(spinBoxOrthogonal, SIGNAL(valueChanged(int)), horizontalSliderOrthogonal, SLOT(setValue(int)));
        QObject::connect(horizontalSliderFOVY, SIGNAL(valueChanged(int)), spinBoxFOVY, SLOT(setValue(int)));
        QObject::connect(spinBoxFOVY, SIGNAL(valueChanged(int)), horizontalSliderFOVY, SLOT(setValue(int)));
        QObject::connect(doubleSpinBoxSampleRatio, SIGNAL(valueChanged(double)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonRayCastingObjectAll, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonRayCastingObjectFore, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonRayCastingObjectBack, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonRayCastingObjectCut, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonNormal, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonPreIntegration, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonFeature, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(horizontalSliderSampleNumber, SIGNAL(valueChanged(int)), spinBoxSampleNumber, SLOT(setValue(int)));
        QObject::connect(spinBoxSampleNumber, SIGNAL(valueChanged(int)), horizontalSliderSampleNumber, SLOT(setValue(int)));
        QObject::connect(doubleSpinBoxZNear, SIGNAL(valueChanged(double)), widgetRender, SLOT(update()));
        QObject::connect(doubleSpinBoxZFar, SIGNAL(valueChanged(double)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonPerspective, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonOrthogonal, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(spinBoxSampleScale, SIGNAL(valueChanged(int)), widgetRender, SLOT(update()));
        QObject::connect(spinBoxSampleNumber, SIGNAL(valueChanged(int)), widgetRender, SLOT(update()));
        QObject::connect(spinBoxFOVY, SIGNAL(valueChanged(int)), widgetRender, SLOT(update()));
        QObject::connect(spinBoxOrthogonal, SIGNAL(valueChanged(int)), widgetRender, SLOT(update()));
        QObject::connect(groupBoxWindow, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(verticalSliderWindowLevel, SIGNAL(valueChanged(int)), widgetRender, SLOT(update()));
        QObject::connect(horizontalSliderPreIntegrationBias, SIGNAL(valueChanged(int)), spinBoxPreIntegrationBias, SLOT(setValue(int)));
        QObject::connect(spinBoxPreIntegrationBias, SIGNAL(valueChanged(int)), horizontalSliderPreIntegrationBias, SLOT(setValue(int)));
        QObject::connect(horizontalSliderPreIntegrationScale, SIGNAL(valueChanged(int)), spinBoxPreIntegrationScale, SLOT(setValue(int)));
        QObject::connect(spinBoxPreIntegrationScale, SIGNAL(valueChanged(int)), horizontalSliderPreIntegrationScale, SLOT(setValue(int)));
        QObject::connect(spinBoxPreIntegrationBias, SIGNAL(valueChanged(int)), widgetRender, SLOT(update()));
        QObject::connect(spinBoxPreIntegrationScale, SIGNAL(valueChanged(int)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonInterpolationLinear, SIGNAL(clicked(bool)), widgetEditor, SLOT(update()));
        QObject::connect(radioButtonInterpolationCubic, SIGNAL(clicked(bool)), widgetEditor, SLOT(update()));
        QObject::connect(radioButtonColorSpaceRGB, SIGNAL(clicked(bool)), widgetEditor, SLOT(update()));
        QObject::connect(radioButtonColorSpaceLUV, SIGNAL(clicked(bool)), widgetEditor, SLOT(update()));
        QObject::connect(radioButtonColorSpaceHSL, SIGNAL(clicked(bool)), widgetEditor, SLOT(update()));
        QObject::connect(radioButtonLayoutNormal, SIGNAL(clicked(bool)), widgetEditor, SLOT(update()));
        QObject::connect(radioButtonLayoutVertical, SIGNAL(clicked(bool)), widgetEditor, SLOT(update()));
        QObject::connect(radioButtonLayoutWave, SIGNAL(clicked(bool)), widgetEditor, SLOT(update()));
        QObject::connect(spinBoxSize, SIGNAL(valueChanged(int)), horizontalSliderSize, SLOT(setValue(int)));
        QObject::connect(horizontalSliderColorBack, SIGNAL(valueChanged(int)), spinBoxColorBack, SLOT(setValue(int)));
        QObject::connect(horizontalSliderColorCut, SIGNAL(valueChanged(int)), spinBoxColorCut, SLOT(setValue(int)));
        QObject::connect(spinBoxOpacity, SIGNAL(valueChanged(int)), horizontalSliderOpacity, SLOT(setValue(int)));
        QObject::connect(radioButtonModeNormal, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonModeBrush, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonModeEraser, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(horizontalSliderSize, SIGNAL(valueChanged(int)), spinBoxSize, SLOT(setValue(int)));
        QObject::connect(spinBoxColorCut, SIGNAL(valueChanged(int)), horizontalSliderColorCut, SLOT(setValue(int)));
        QObject::connect(horizontalSliderColorFore, SIGNAL(valueChanged(int)), spinBoxColorFore, SLOT(setValue(int)));
        QObject::connect(horizontalSliderOpacity, SIGNAL(valueChanged(int)), spinBoxOpacity, SLOT(setValue(int)));
        QObject::connect(spinBoxColorFore, SIGNAL(valueChanged(int)), horizontalSliderColorFore, SLOT(setValue(int)));
        QObject::connect(spinBoxColorBack, SIGNAL(valueChanged(int)), horizontalSliderColorBack, SLOT(setValue(int)));
        QObject::connect(spinBoxColorCut, SIGNAL(valueChanged(int)), widgetRender, SLOT(update()));
        QObject::connect(spinBoxOpacity, SIGNAL(valueChanged(int)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonShapeCross, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonBrushingObjectCut, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(pushButtonColorCut, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(pushButtonColorFore, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(spinBoxColorBack, SIGNAL(valueChanged(int)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonShapeCircle, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonShapeSquare, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(pushButtonColorBack, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(spinBoxSize, SIGNAL(valueChanged(int)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonBrushingObjectBack, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(pushButtonClear, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(spinBoxColorFore, SIGNAL(valueChanged(int)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonBrushingObjectFore, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(horizontalSliderColorTag, SIGNAL(valueChanged(int)), spinBoxColorTag, SLOT(setValue(int)));
        QObject::connect(spinBoxColorTag, SIGNAL(valueChanged(int)), horizontalSliderColorTag, SLOT(setValue(int)));
        QObject::connect(pushButtonColorTag, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(spinBoxColorTag, SIGNAL(valueChanged(int)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonBrushingObjectTag, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));
        QObject::connect(radioButtonRayCastingObjectTag, SIGNAL(clicked(bool)), widgetRender, SLOT(update()));

        tabWidgetBackStage->setCurrentIndex(2);
        tabWidgetFrontStage->setCurrentIndex(3);
        tabWidgetSettings->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(QGCPanel);
    } // setupUi

    void retranslateUi(QWidget *QGCPanel)
    {
        QGCPanel->setWindowTitle(QApplication::translate("QGCPanel", "Control Panel", 0, QApplication::UnicodeUTF8));
        groupBoxVolumeRendering->setTitle(QApplication::translate("QGCPanel", "Volume Rendering", 0, QApplication::UnicodeUTF8));
        groupBoxGraphCut->setTitle(QApplication::translate("QGCPanel", "Graph Cut", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabWidgetBackStage->setToolTip(QApplication::translate("QGCPanel", "Convergence", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        tabAlgorithm->setToolTip(QApplication::translate("QGCPanel", "Algorithm", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHeightField->setText(QApplication::translate("QGCPanel", "Height Field", 0, QApplication::UnicodeUTF8));
        radioButtonGlobalRelabel->setText(QApplication::translate("QGCPanel", "Global R", 0, QApplication::UnicodeUTF8));
        radioButtonNone->setText(QApplication::translate("QGCPanel", "None", 0, QApplication::UnicodeUTF8));
        pushButtonExport->setText(QApplication::translate("QGCPanel", "Export", 0, QApplication::UnicodeUTF8));
        radioButtonCutMethodFastCut->setText(QApplication::translate("QGCPanel", "Fast", 0, QApplication::UnicodeUTF8));
        labelCutMethod->setText(QApplication::translate("QGCPanel", "Method", 0, QApplication::UnicodeUTF8));
        radioButtonCutMethodJFCut->setText(QApplication::translate("QGCPanel", "JF", 0, QApplication::UnicodeUTF8));
        pushButtonCutAlgorithm->setText(QApplication::translate("QGCPanel", "Cut", 0, QApplication::UnicodeUTF8));
        labelTile2D->setText(QApplication::translate("QGCPanel", "Tile 2D", 0, QApplication::UnicodeUTF8));
        labelTile3D->setText(QApplication::translate("QGCPanel", "Tile 3D", 0, QApplication::UnicodeUTF8));
        tabWidgetBackStage->setTabText(tabWidgetBackStage->indexOf(tabAlgorithm), QApplication::translate("QGCPanel", "Algorithm", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabModeling->setToolTip(QApplication::translate("QGCPanel", "Modeling", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelModelingMethod->setText(QApplication::translate("QGCPanel", "Method", 0, QApplication::UnicodeUTF8));
        pushButtonCutModeling->setText(QApplication::translate("QGCPanel", "Cut", 0, QApplication::UnicodeUTF8));
        radioButtonBK->setText(QApplication::translate("QGCPanel", "BK", 0, QApplication::UnicodeUTF8));
        radioButtonLazySnapping->setText(QApplication::translate("QGCPanel", "Lazy ", 0, QApplication::UnicodeUTF8));
        labelKMeans->setText(QApplication::translate("QGCPanel", "K-Means", 0, QApplication::UnicodeUTF8));
        labelKMeansIterations->setText(QApplication::translate("QGCPanel", "Max-Itr", 0, QApplication::UnicodeUTF8));
        labelClustering->setText(QApplication::translate("QGCPanel", "Clustering", 0, QApplication::UnicodeUTF8));
        labelLazyTerminal->setText(QApplication::translate("QGCPanel", "Terminal", 0, QApplication::UnicodeUTF8));
        labelLazyNeighbor->setText(QApplication::translate("QGCPanel", "Neighbor", 0, QApplication::UnicodeUTF8));
        labelLazyCapacity->setText(QApplication::translate("QGCPanel", "Lazy Cap", 0, QApplication::UnicodeUTF8));
        labelBKCapacity->setText(QApplication::translate("QGCPanel", "BK Cap", 0, QApplication::UnicodeUTF8));
        labelBKNeighbor->setText(QApplication::translate("QGCPanel", "Neighbor", 0, QApplication::UnicodeUTF8));
        labelBKTerminal->setText(QApplication::translate("QGCPanel", "Terminal", 0, QApplication::UnicodeUTF8));
        tabWidgetBackStage->setTabText(tabWidgetBackStage->indexOf(tabModeling), QApplication::translate("QGCPanel", "Modeling", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabConvergence->setToolTip(QApplication::translate("QGCPanel", "Convergence", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        checkBoxPrint->setText(QApplication::translate("QGCPanel", "Print", 0, QApplication::UnicodeUTF8));
        pushButtonCut->setText(QApplication::translate("QGCPanel", "Cut", 0, QApplication::UnicodeUTF8));
        labelLaunch->setText(QApplication::translate("QGCPanel", "Launch", 0, QApplication::UnicodeUTF8));
        checkBoxEnergy->setText(QApplication::translate("QGCPanel", "Energy", 0, QApplication::UnicodeUTF8));
        checkBoxComputeTag->setText(QApplication::translate("QGCPanel", "Tag", 0, QApplication::UnicodeUTF8));
        labelUpdate->setText(QApplication::translate("QGCPanel", "Update", 0, QApplication::UnicodeUTF8));
        labelCountIterations->setText(QApplication::translate("QGCPanel", "Count-Itr", 0, QApplication::UnicodeUTF8));
        labelCutIterations->setText(QApplication::translate("QGCPanel", "Cut-Itr", 0, QApplication::UnicodeUTF8));
        labelOther->setText(QApplication::translate("QGCPanel", "Update", 0, QApplication::UnicodeUTF8));
        labelTotalIterations->setText(QApplication::translate("QGCPanel", "Total-Itr", 0, QApplication::UnicodeUTF8));
        labelPrintIterations->setText(QApplication::translate("QGCPanel", "Pri-Itr", 0, QApplication::UnicodeUTF8));
        tabWidgetBackStage->setTabText(tabWidgetBackStage->indexOf(tabConvergence), QApplication::translate("QGCPanel", "Convergence", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabFeature->setToolTip(QApplication::translate("QGCPanel", "Feature", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelWeight->setText(QApplication::translate("QGCPanel", "Weight", 0, QApplication::UnicodeUTF8));
        labelWeightZ->setText(QApplication::translate("QGCPanel", "Z", 0, QApplication::UnicodeUTF8));
        labelWeightW->setText(QApplication::translate("QGCPanel", "W", 0, QApplication::UnicodeUTF8));
        labelWeightX->setText(QApplication::translate("QGCPanel", "X", 0, QApplication::UnicodeUTF8));
        labelWeightY->setText(QApplication::translate("QGCPanel", "Y", 0, QApplication::UnicodeUTF8));
        tabWidgetBackStage->setTabText(tabWidgetBackStage->indexOf(tabFeature), QApplication::translate("QGCPanel", "Feature", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabOpenCL->setToolTip(QApplication::translate("QGCPanel", "OpenCL", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelMaxGroup->setText(QApplication::translate("QGCPanel", "Max Group", 0, QApplication::UnicodeUTF8));
        labelLocalSize1DX->setText(QApplication::translate("QGCPanel", "Local 1D", 0, QApplication::UnicodeUTF8));
        labelLocalSize2D->setText(QApplication::translate("QGCPanel", "Local 2D", 0, QApplication::UnicodeUTF8));
        labelLocalSize3D->setText(QApplication::translate("QGCPanel", "Local 3D", 0, QApplication::UnicodeUTF8));
        tabWidgetBackStage->setTabText(tabWidgetBackStage->indexOf(tabOpenCL), QApplication::translate("QGCPanel", "OpenCL", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabBrushing->setToolTip(QApplication::translate("QGCPanel", "Brushing", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelOpacity->setText(QApplication::translate("QGCPanel", "Opacity", 0, QApplication::UnicodeUTF8));
        labelSize->setText(QApplication::translate("QGCPanel", "Size", 0, QApplication::UnicodeUTF8));
        radioButtonShapeSquare->setText(QApplication::translate("QGCPanel", "Square", 0, QApplication::UnicodeUTF8));
        labelShape->setText(QApplication::translate("QGCPanel", "Shape", 0, QApplication::UnicodeUTF8));
        radioButtonShapeCross->setText(QApplication::translate("QGCPanel", "Cross", 0, QApplication::UnicodeUTF8));
        radioButtonShapeCircle->setText(QApplication::translate("QGCPanel", "Circle", 0, QApplication::UnicodeUTF8));
        tabWidgetFrontStage->setTabText(tabWidgetFrontStage->indexOf(tabBrushing), QApplication::translate("QGCPanel", "Brushing", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabMode->setToolTip(QApplication::translate("QGCPanel", "Mode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelType->setText(QApplication::translate("QGCPanel", "Type", 0, QApplication::UnicodeUTF8));
        radioButtonModeBrush->setText(QApplication::translate("QGCPanel", "Brush", 0, QApplication::UnicodeUTF8));
        radioButtonModeNormal->setText(QApplication::translate("QGCPanel", "Normal", 0, QApplication::UnicodeUTF8));
        radioButtonModeEraser->setText(QApplication::translate("QGCPanel", "Eraser", 0, QApplication::UnicodeUTF8));
        labelBrushingObject->setText(QApplication::translate("QGCPanel", "Object", 0, QApplication::UnicodeUTF8));
        radioButtonBrushingObjectBack->setText(QApplication::translate("QGCPanel", "Back", 0, QApplication::UnicodeUTF8));
        radioButtonBrushingObjectCut->setText(QApplication::translate("QGCPanel", "Cut", 0, QApplication::UnicodeUTF8));
        radioButtonBrushingObjectFore->setText(QApplication::translate("QGCPanel", "Fore", 0, QApplication::UnicodeUTF8));
        radioButtonBrushingObjectTag->setText(QApplication::translate("QGCPanel", "Tag", 0, QApplication::UnicodeUTF8));
        pushButtonClear->setText(QApplication::translate("QGCPanel", "Clear", 0, QApplication::UnicodeUTF8));
        labelModeEdit->setText(QApplication::translate("QGCPanel", "Edit", 0, QApplication::UnicodeUTF8));
        pushButtonUndo->setText(QApplication::translate("QGCPanel", "Undo", 0, QApplication::UnicodeUTF8));
        pushButtonRedo->setText(QApplication::translate("QGCPanel", "Redo", 0, QApplication::UnicodeUTF8));
        tabWidgetFrontStage->setTabText(tabWidgetFrontStage->indexOf(tabMode), QApplication::translate("QGCPanel", "Mode", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabColor->setToolTip(QApplication::translate("QGCPanel", "Color", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pushButtonColorFore->setToolTip(QApplication::translate("QGCPanel", "255, 127, 127", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonColorFore->setText(QString());
        labelColorForeNote->setText(QApplication::translate("QGCPanel", "Fore", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonColorBack->setToolTip(QApplication::translate("QGCPanel", "127, 255, 127", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonColorBack->setText(QString());
        labelColorBackNote->setText(QApplication::translate("QGCPanel", "Back", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonColorCut->setToolTip(QApplication::translate("QGCPanel", "127, 127, 225", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonColorCut->setText(QString());
        labelColorCutNote->setText(QApplication::translate("QGCPanel", "Cut", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonColorTag->setToolTip(QApplication::translate("QGCPanel", "255, 127, 225", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonColorTag->setText(QString());
        labelColorTagNote->setText(QApplication::translate("QGCPanel", "Tag", 0, QApplication::UnicodeUTF8));
        tabWidgetFrontStage->setTabText(tabWidgetFrontStage->indexOf(tabColor), QApplication::translate("QGCPanel", "Color", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabTexture->setToolTip(QApplication::translate("QGCPanel", "Texture", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonSaveGraph->setText(QApplication::translate("QGCPanel", "Save", 0, QApplication::UnicodeUTF8));
        pushButtonLoadGraph->setText(QApplication::translate("QGCPanel", "Load", 0, QApplication::UnicodeUTF8));
        labelGraph->setText(QApplication::translate("QGCPanel", "Graph", 0, QApplication::UnicodeUTF8));
        checkBoxGraph->setText(QApplication::translate("QGCPanel", "Auto", 0, QApplication::UnicodeUTF8));
        pushButtonLoadGradient->setText(QApplication::translate("QGCPanel", "Load", 0, QApplication::UnicodeUTF8));
        pushButtonSaveGradient->setText(QApplication::translate("QGCPanel", "Save", 0, QApplication::UnicodeUTF8));
        labelGradient->setText(QApplication::translate("QGCPanel", "Gradient", 0, QApplication::UnicodeUTF8));
        checkBoxGradient->setText(QApplication::translate("QGCPanel", "Auto", 0, QApplication::UnicodeUTF8));
        pushButtonLoadFeature->setText(QApplication::translate("QGCPanel", "Load", 0, QApplication::UnicodeUTF8));
        pushButtonSaveFeature->setText(QApplication::translate("QGCPanel", "Save", 0, QApplication::UnicodeUTF8));
        labelFeature->setText(QApplication::translate("QGCPanel", "Feature", 0, QApplication::UnicodeUTF8));
        checkBoxFeature->setText(QApplication::translate("QGCPanel", "Auto", 0, QApplication::UnicodeUTF8));
        checkBoxCut->setText(QApplication::translate("QGCPanel", "Auto", 0, QApplication::UnicodeUTF8));
        pushButtonSaveCut->setText(QApplication::translate("QGCPanel", "Save", 0, QApplication::UnicodeUTF8));
        pushButtonLoadCut->setText(QApplication::translate("QGCPanel", "Load", 0, QApplication::UnicodeUTF8));
        labelCut->setText(QApplication::translate("QGCPanel", "Cut", 0, QApplication::UnicodeUTF8));
        tabWidgetFrontStage->setTabText(tabWidgetFrontStage->indexOf(tabTexture), QApplication::translate("QGCPanel", "Texture", 0, QApplication::UnicodeUTF8));
        groupBoxRendering->setTitle(QApplication::translate("QGCPanel", "Rendering", 0, QApplication::UnicodeUTF8));
        groupBoxTransferFunctionEditor->setTitle(QApplication::translate("QGCPanel", "Transfer Function Editor", 0, QApplication::UnicodeUTF8));
        groupBoxWindow->setTitle(QApplication::translate("QGCPanel", "Window", 0, QApplication::UnicodeUTF8));
        labelWindowWidth->setText(QApplication::translate("QGCPanel", "65535", 0, QApplication::UnicodeUTF8));
        labelWindowLevel->setText(QApplication::translate("QGCPanel", "65535", 0, QApplication::UnicodeUTF8));
        labelWindowLevelNote->setText(QApplication::translate("QGCPanel", "Lvl", 0, QApplication::UnicodeUTF8));
        labelWindowWidthNote->setText(QApplication::translate("QGCPanel", "W", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabTransferFunction->setToolTip(QApplication::translate("QGCPanel", "Transfer Function", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonLoadTransferFunction->setText(QApplication::translate("QGCPanel", "Load", 0, QApplication::UnicodeUTF8));
        pushButtonSaveTransferFunction->setText(QApplication::translate("QGCPanel", "Save", 0, QApplication::UnicodeUTF8));
        radioButtonInterpolationLinear->setText(QApplication::translate("QGCPanel", "Linear", 0, QApplication::UnicodeUTF8));
        labelInterpolation->setText(QApplication::translate("QGCPanel", "Interpolation", 0, QApplication::UnicodeUTF8));
        radioButtonInterpolationCubic->setText(QApplication::translate("QGCPanel", "Cubic", 0, QApplication::UnicodeUTF8));
        labelPointNumber->setText(QApplication::translate("QGCPanel", "Point Number", 0, QApplication::UnicodeUTF8));
        radioButtonPointNumber4->setText(QApplication::translate("QGCPanel", "4", 0, QApplication::UnicodeUTF8));
        radioButtonPointNumber8->setText(QApplication::translate("QGCPanel", "8", 0, QApplication::UnicodeUTF8));
        radioButtonPointNumber16->setText(QApplication::translate("QGCPanel", "16", 0, QApplication::UnicodeUTF8));
        labelLayout->setText(QApplication::translate("QGCPanel", "Layout", 0, QApplication::UnicodeUTF8));
        radioButtonLayoutNormal->setText(QApplication::translate("QGCPanel", "Normal", 0, QApplication::UnicodeUTF8));
        radioButtonLayoutVertical->setText(QApplication::translate("QGCPanel", "Vertical", 0, QApplication::UnicodeUTF8));
        radioButtonLayoutWave->setText(QApplication::translate("QGCPanel", "Wave", 0, QApplication::UnicodeUTF8));
        radioButtonColorSpaceLUV->setText(QApplication::translate("QGCPanel", "LUV", 0, QApplication::UnicodeUTF8));
        radioButtonColorSpaceRGB->setText(QApplication::translate("QGCPanel", "RGB", 0, QApplication::UnicodeUTF8));
        labelColorSpace->setText(QApplication::translate("QGCPanel", "Space", 0, QApplication::UnicodeUTF8));
        radioButtonColorSpaceHSL->setText(QApplication::translate("QGCPanel", "HSL", 0, QApplication::UnicodeUTF8));
        tabWidgetSettings->setTabText(tabWidgetSettings->indexOf(tabTransferFunction), QApplication::translate("QGCPanel", "Transfer Function", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabView->setToolTip(QApplication::translate("QGCPanel", "View", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelViewTranslation->setText(QApplication::translate("QGCPanel", "Translation", 0, QApplication::UnicodeUTF8));
        labelViewRotation->setText(QApplication::translate("QGCPanel", "Rotation", 0, QApplication::UnicodeUTF8));
        labelRotationZ->setText(QApplication::translate("QGCPanel", "Z", 0, QApplication::UnicodeUTF8));
        labelRotationW->setText(QApplication::translate("QGCPanel", "W", 0, QApplication::UnicodeUTF8));
        labelRotationY->setText(QApplication::translate("QGCPanel", "Y", 0, QApplication::UnicodeUTF8));
        labelRotationX->setText(QApplication::translate("QGCPanel", "X", 0, QApplication::UnicodeUTF8));
        labelSizeY->setText(QApplication::translate("QGCPanel", "Y", 0, QApplication::UnicodeUTF8));
        labelViewSize->setText(QApplication::translate("QGCPanel", "Size", 0, QApplication::UnicodeUTF8));
        labelSizeX->setText(QApplication::translate("QGCPanel", "X", 0, QApplication::UnicodeUTF8));
        tabWidgetSettings->setTabText(tabWidgetSettings->indexOf(tabView), QApplication::translate("QGCPanel", "View", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabProjection->setToolTip(QApplication::translate("QGCPanel", "Projection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButtonPerspective->setText(QApplication::translate("QGCPanel", "Perspective", 0, QApplication::UnicodeUTF8));
        radioButtonOrthogonal->setText(QApplication::translate("QGCPanel", "Orthogonal", 0, QApplication::UnicodeUTF8));
        labelProjectionMode->setText(QApplication::translate("QGCPanel", "Mode", 0, QApplication::UnicodeUTF8));
        labelPerspective->setText(QApplication::translate("QGCPanel", "Perspective", 0, QApplication::UnicodeUTF8));
        labelZNear->setText(QApplication::translate("QGCPanel", "Z-Near", 0, QApplication::UnicodeUTF8));
        labelZFar->setText(QApplication::translate("QGCPanel", "Z-Far", 0, QApplication::UnicodeUTF8));
        labelFOVY->setText(QApplication::translate("QGCPanel", "FOV - Y", 0, QApplication::UnicodeUTF8));
        labelOrthogonal->setText(QApplication::translate("QGCPanel", "Orthogonal", 0, QApplication::UnicodeUTF8));
        tabWidgetSettings->setTabText(tabWidgetSettings->indexOf(tabProjection), QApplication::translate("QGCPanel", "Projection", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabRayCasting->setToolTip(QApplication::translate("QGCPanel", "Ray Casting", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButtonNormal->setText(QApplication::translate("QGCPanel", "Normal", 0, QApplication::UnicodeUTF8));
        radioButtonPreIntegration->setText(QApplication::translate("QGCPanel", "PreInt", 0, QApplication::UnicodeUTF8));
        labelRayCastingMode->setText(QApplication::translate("QGCPanel", "Mode", 0, QApplication::UnicodeUTF8));
        radioButtonFeature->setText(QApplication::translate("QGCPanel", "Feature", 0, QApplication::UnicodeUTF8));
        labelRayCastingObject->setText(QApplication::translate("QGCPanel", "Object", 0, QApplication::UnicodeUTF8));
        radioButtonRayCastingObjectAll->setText(QApplication::translate("QGCPanel", "A", 0, QApplication::UnicodeUTF8));
        radioButtonRayCastingObjectFore->setText(QApplication::translate("QGCPanel", "F", 0, QApplication::UnicodeUTF8));
        radioButtonRayCastingObjectBack->setText(QApplication::translate("QGCPanel", "B", 0, QApplication::UnicodeUTF8));
        radioButtonRayCastingObjectTag->setText(QApplication::translate("QGCPanel", "T", 0, QApplication::UnicodeUTF8));
        radioButtonRayCastingObjectCut->setText(QApplication::translate("QGCPanel", "C", 0, QApplication::UnicodeUTF8));
        labelSampleApproximation->setText(QApplication::translate("QGCPanel", "Sample Apr", 0, QApplication::UnicodeUTF8));
        labelSampleRatio->setText(QApplication::translate("QGCPanel", "Ratio", 0, QApplication::UnicodeUTF8));
        labelSampleScale->setText(QApplication::translate("QGCPanel", "Scale", 0, QApplication::UnicodeUTF8));
        labelSampleNumber->setText(QApplication::translate("QGCPanel", "Sample Num", 0, QApplication::UnicodeUTF8));
        tabWidgetSettings->setTabText(tabWidgetSettings->indexOf(tabRayCasting), QApplication::translate("QGCPanel", "Ray Casting", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabPreIntegration->setToolTip(QApplication::translate("QGCPanel", "Pre-Integration", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelPreIntegrationBias->setText(QApplication::translate("QGCPanel", "Bias", 0, QApplication::UnicodeUTF8));
        labelPreIntegrationScale->setText(QApplication::translate("QGCPanel", "Scale", 0, QApplication::UnicodeUTF8));
        tabWidgetSettings->setTabText(tabWidgetSettings->indexOf(tabPreIntegration), QApplication::translate("QGCPanel", "Pre-Integration", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QGCPanel: public Ui_QGCPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGCPANEL_H
