/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QTransferFunction1D.h
 * @brief   QTransferFunction1D class definition.
 * 
 * This file defines a widget which can be used to design the transfer functions.
 *     The background of the widget shows the intensity histogram of the volume data,
 *     A hover point with a color (the opacity is defined by its height) 
 *          corresponds to a control point in transfer function design.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2012/02/07
 */

#ifndef QTRANSFERFUNCTION1D_H
#define QTRANSFERFUNCTION1D_H

#include <vector>

#include <QWidget>

class QHoverPoints;

class QTransferFunction1D : public QWidget
{
    Q_OBJECT
public:
    QTransferFunction1D(QWidget *parent);

    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
    void showEvent(QShowEvent*);

    QHoverPoints *getHoverPoints() const { return hoverPoints; }
    void setAlpha();

signals:
    void signalControlPointsChanged();

public slots:
    void slotSetPartition(::size_t partitionSize, float *partiionData);
    void slotInsertHistogram(::size_t histogramSize, float *histogramData);
    void slotUpdateHistogram(int histogramID, float *histogramData);
    void slotUpdateTransferFunction();
    void slotClearHistogram();

    void load(const std::string& name);
    void save(const std::string& name);

public:
    float alphaBase;
private:
    std::vector<::size_t> histogramSize;
    std::vector<float*> histogramData;
    ::size_t partitionSize;
    float* partitionData;
    QHoverPoints *hoverPoints;

    void drawHistogram();
    void drawColorBar();
};

#endif  // QTRANSFERFUNCTION1D_H