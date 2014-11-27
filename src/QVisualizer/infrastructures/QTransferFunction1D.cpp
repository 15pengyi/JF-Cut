/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QTransferFunction1D.cpp
 * @brief   QTransferFunction1D class declaration.
 * 
 * This file declares the methods of the widget defined in QTransferFunction1D.h.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2012/02/07
 */

#include <gl/glew.h>

#include "../infrastructures/QHoverPoints.h"
#include "../utilities/QUtilityUI.h"
#include "../utilities/QUtilityData.h"
#include "QTransferFunction1D.h"
#include "QSetting.h"

QTransferFunction1D::QTransferFunction1D(QWidget *parent) : QWidget(parent),
    alphaBase(10.0f),
    histogramData(0), histogramSize(0),
    partitionData(NULL), partitionSize(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QPolygonF points(0);
    points.push_back(QPointF(0.0, this->height()));
    points.push_back(QPointF(this->width(), 0.0));

    hoverPoints = new QHoverPoints(this, QHoverPoints::CircleShape);
    hoverPoints->setConnectionType(QHoverPoints::CurveConnection);
    hoverPoints->setPoints(points);
    hoverPoints->setPointLock(0, QHoverPoints::LockToLeft);
    hoverPoints->setPointLock(1, QHoverPoints::LockToRight);
    hoverPoints->setSortType(QHoverPoints::XSort);

    QVector<QColor> colors(0);
    colors.push_back(QColor::fromRgbF(0.75f, 0.75f, 0.75f));
    colors.push_back(QColor::fromRgbF(1.00f, 1.00f, 1.00f));
    hoverPoints->setColors(colors);

    connect(hoverPoints, SIGNAL(signalPointsChanged()), this, SLOT(slotUpdateTransferFunction()));
}

void QTransferFunction1D::drawHistogram()
{
    auto data = histogramData.begin();
    for (auto size = histogramSize.begin(); size != histogramSize.end(); size++, data++)
    {
        ::size_t histogramSize = *size;
        float* histogramData = *data;
        if (!histogramData) continue;

        // Generate the histogram path
        qreal scale = this->height() * 0.6f;
        qreal offset = this->height() * 0.8f;

        QPainterPath* histogramPath = new QPainterPath();
        histogramPath->moveTo(0.0, 0.0);
        histogramPath->lineTo(0.0, offset);
        
        // transform point position
        std::vector<float> positions;
        QUtilityData::computeHistogramPositions(histogramSize, this->width(), positions, partitionSize, partitionData);

        histogramPath->lineTo(QPointF(positions[0], offset - histogramData[0] * scale));
        for (int i = 1; i < histogramSize; i++)
        {
            QPointF p1 = QPointF(positions[i - 1], offset - histogramData[i - 1] * scale);
            QPointF p2 = QPointF(positions[i], offset - histogramData[i] * scale);
            qreal distance = p2.x() - p1.x();
            histogramPath->cubicTo(p1.x() + distance / 2, p1.y(),
                p1.x() + distance / 2, p2.y(),
                p2.x(), p2.y());
        }
        histogramPath->lineTo(this->width(), offset);
        histogramPath->lineTo(this->width(), 0.0);

        QPainter painter(this);
        QColor color(127, 127, 127, 0);
        painter.setBrush(color);
        painter.setPen(Qt::gray);
        painter.setRenderHints(QPainter::Antialiasing);
        painter.drawPath(*histogramPath);
        painter.end();
    }
}

void QTransferFunction1D::drawColorBar()
{
    // compute painter path
    QLinearGradient gradient(0, 0, this->width(), 0);
    QPolygonF *points = &hoverPoints->points();
    QPainterPath* hoverPointPath = new QPainterPath();
    hoverPointPath->moveTo(0.0f, this->height());
    switch (hoverPoints->connectionType())
    {
    case QHoverPoints::LineConnection:
        for (auto i = points->begin();  i != points->end(); i++)
            hoverPointPath->lineTo(*i);
        QUtilityUI::generateLinearGradient(gradient, this->width(), hoverPoints, 0.5f);
        break;
    case QHoverPoints::CurveConnection:
        hoverPointPath->lineTo(points->at(0));
        for (int i = 1; i < points->size(); i++)
        {
            QPointF p1 = points->at(i-1);
            QPointF p2 = points->at(i);
            qreal distance = p2.x() - p1.x();
            hoverPointPath->cubicTo(p1.x() + distance / 2, p1.y(),
                p1.x() + distance / 2, p2.y(),
                p2.x(), p2.y());
        }
        std::vector<float> positions;
        QUtilityData::computePartitionPositions(hoverPoints, this->width(), positions, partitionSize, partitionData);
        QUtilityUI::generateCubicGradient(gradient, this->width(), hoverPoints, QSetting::sizeTransferFunction1D, positions, 0.5f);
        break;
    }
    hoverPointPath->lineTo(this->width(), this->height());

    QPainter painter(this);
    painter.setBrush(gradient);
    painter.setPen(Qt::darkGray);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.drawPath(*hoverPointPath);
    painter.end();
}

void QTransferFunction1D::slotClearHistogram()
{
    setAlpha();
    this->histogramSize.clear();
    this->histogramData.clear();
}

void QTransferFunction1D::slotInsertHistogram(::size_t histogramSize, float *histogramData)
{
    this->histogramSize.push_back(histogramSize);
    this->histogramData.push_back(histogramData);
    update();
}

void QTransferFunction1D::slotSetPartition(::size_t partitionSize, float *partiionData)
{
    this->partitionSize = partitionSize;
    this->partitionData = partiionData;
    update();
}

void QTransferFunction1D::slotUpdateHistogram(int histogramID, float *histogramData)
{
    if (histogramID >= 0 && histogramID < this->histogramData.size() && histogramData)
        this->histogramData[histogramID] = histogramData;
    update();
}

void QTransferFunction1D::load(const std::string& name)
{
    hoverPoints->load(name, this->size());
    update();
}

void QTransferFunction1D::save(const std::string& name)
{
    hoverPoints->save(name, this->size());
    update();
}

void QTransferFunction1D::paintEvent(QPaintEvent *e)
{
    drawHistogram();
    drawColorBar();

    e->accept();
}

void QTransferFunction1D::resizeEvent(QResizeEvent *e)
{
    emit signalControlPointsChanged();
    
    e->accept();
}

void QTransferFunction1D::showEvent(QShowEvent *e)
{
    emit signalControlPointsChanged();

    e->accept();
}

void QTransferFunction1D::setAlpha()
{
    float scaleAlpha = 1.0 / (alphaBase - 1.0f);
    QPolygonF *points = &hoverPoints->points();
    QVector<QColor> *colors = &hoverPoints->colors();
    QVector<QPointF>::iterator point = points->begin();
    for (auto i = colors->begin(); i != colors->end(); i++)
    {
        float ratio = 1.0f - (point++)->y() / this->height();
        i->setAlphaF(std::min<float>((std::pow(alphaBase, ratio) - 1.0f) * scaleAlpha, 1.0f));
    }
}

void QTransferFunction1D::slotUpdateTransferFunction()
{
    setAlpha();
    emit signalControlPointsChanged();
}