/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    QUtilityUI.cpp
 * @brief   QUtilityUI class declaration.
 * 
 * This file declares the most commonly used methods defined in QUtilityUI.h.
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail  15pengyi@gmail.com
 * @date    2013/07/25
 */

#include <vector>

#include <QtXml/QDomDocument>
#include <QPolygonF>
#include <QColor>
#include <QImage>

#include "../infrastructures/QStructure.h"
#include "../infrastructures/QHoverPoints.h"
#include "QUtilityUI.h"
#include "QIO.h"

QUtilityUI::QUtilityUI()
{}

QUtilityUI::~QUtilityUI()
{}

glm::vec4 QUtilityUI::getColor(const QString& rgb, unsigned char alpha)
{
    glm::vec4 color = glm::vec4((float)alpha / std::numeric_limits<unsigned char>::max());

    float* c = (float*)&color;
    foreach(QString s, rgb.split(','))
        *(c++) *= (float)s.toInt() / std::numeric_limits<unsigned char>::max();

    return color;
}

void QUtilityUI::generateLinearGradient(QLinearGradient &linearGradient, int width, QHoverPoints* hoverPoints, float alpha)
{
    const QPolygonF& points = hoverPoints->points();
    const QVector<QColor>& colors = hoverPoints->colors();
    unsigned char max = std::numeric_limits<unsigned char>::max();
    for (QVector<QPointF>::const_iterator i = points.begin();  i != points.end(); i++)
    {
        const QColor& color = colors.at(i - points.begin());
        linearGradient.setColorAt(i->x() / width, QColor(
            color.red(), color.green(), color.blue(),
            (int)(color.alpha() * alpha + max * (1.0f - alpha) + 0.5f)
        ));
    }
}

void QUtilityUI::generateCubicGradient(QLinearGradient &linearGradient, int width, QHoverPoints* hoverPoints,
    int gradientSize, const std::vector<float>& positions, float alpha)
{
    const QVector<QColor>& orgColors = hoverPoints->colors();
    std::vector<glm::vec4> colors;
    for (QVector<QColor>::const_iterator i = orgColors.begin(); i != orgColors.end(); i++)
        colors.push_back(glm::vec4(i->redF(), i->greenF(), i->blueF(), i->alphaF()));

    int index(0);
    unsigned char max = std::numeric_limits<unsigned char>::max();
    for (int i = 0; i < gradientSize; i++)
    {
        float x = (float)i / (gradientSize - 1);
        while (positions[index + 1] < x) index++;
        float ratio = positions[index + 1] == positions[index] ? 0.0f : float(x - positions[index]) / (positions[index + 1] - positions[index]);
        glm::vec4 color = QUtilityUITemplate<glm::vec4>::cubicTo(ratio, colors[index], colors[index + 1]);
        linearGradient.setColorAt(x, QColor(
            (int)(color.r * max + 0.5f),
            (int)(color.g * max + 0.5f),
            (int)(color.b * max + 0.5f),
            (int)((color.a * alpha + (1.0f - alpha)) * max + 0.5f)
        ));
    }
}

void QUtilityUI::loadWidget(const std::string& filePath, QWidget* widget)
{
    std::string content;
    std::string fileName(widget->toolTip().isEmpty() ? widget->objectName().toLocal8Bit() : widget->toolTip().toLocal8Bit());
    if (!QIO::getFileContent(filePath + fileName + std::string(".settings"), content)) return;

    QDomDocument document;
    if (!document.setContent(QString(content.c_str()))) return;
    
    QDomElement root = document.firstChildElement("QWidget");
    if (root.isNull()) return;

    for (QDomElement node = root.firstChildElement(); !node.isNull(); node = node.nextSiblingElement())
    {
        QDomNode child = node.firstChild();
        if (child.isNull() || !child.isText()) continue;
        
        QString name = node.nodeName();
        QString value = child.nodeValue();
        if (name.startsWith(QString("spinBox")))
        {
            QSpinBox* object = widget->findChild<QSpinBox*>(name);
            if (object && object->isEnabled()) object->setValue(value.toInt());
        }
        else if (name.startsWith("doubleSpinBox"))
        {
            QDoubleSpinBox* object = widget->findChild<QDoubleSpinBox*>(name);
            if (object && object->isEnabled()) object->setValue(value.toDouble());
        }
        else if (name.startsWith("comboBox"))
        {
            QComboBox* object = widget->findChild<QComboBox*>(name);
            if (object && object->isEnabled()) object->setCurrentIndex(value.toInt());
        }
        else if (name.startsWith("checkBox"))
        {
            QCheckBox* object = widget->findChild<QCheckBox*>(name);
            if (object && object->isEnabled()) object->setChecked(value.toInt());
        }
        else if (name.startsWith("radioButton"))
        {
            QRadioButton* object = widget->findChild<QRadioButton*>(name);
            if (object && object->isEnabled()) object->setChecked(value.toInt());
        }
        else if (name.startsWith("pushButton"))
        {
            QPushButton* object = widget->findChild<QPushButton*>(name);
            if (object && object->isEnabled())
            {
                object->setStyleSheet(node.attribute("styleSheet"));
                object->setToolTip(value);
            }
        }
    }
}

void QUtilityUI::saveWidget(const std::string& filePath, QWidget* widget)
{
    QDomDocument document;

    QDomProcessingInstruction instruction = document.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    document.appendChild(instruction);

    QDomElement root = document.createElement("QWidget");
    root.setAttribute("objectName", widget->objectName());
    root.setAttribute("toolTip", widget->toolTip());
    document.appendChild(root);
    
    foreach (const QWidget *child, widget->findChildren<QWidget*>())
    {
        foreach (const QSpinBox *grandchild, child->findChildren<QSpinBox*>())
        {
            QDomElement node = document.createElement(grandchild->objectName());
            QDomText text = document.createTextNode(QString::number(grandchild->value()));
            node.appendChild(text);
            root.appendChild(node);
        }

        foreach (const QDoubleSpinBox *grandchild, child->findChildren<QDoubleSpinBox*>())
        {
            QDomElement node = document.createElement(grandchild->objectName());
            QDomText text = document.createTextNode(QString::number(grandchild->value()));
            node.appendChild(text);
            root.appendChild(node);
        }

        foreach (const QComboBox *grandchild, child->findChildren<QComboBox*>())
        {
            QDomElement node = document.createElement(grandchild->objectName());
            QDomText text = document.createTextNode(QString::number(grandchild->currentIndex()));
            node.appendChild(text);
            root.appendChild(node);
        }

        foreach (const QCheckBox *grandchild, child->findChildren<QCheckBox*>())
        {
            QDomElement node = document.createElement(grandchild->objectName());
            QDomText text = document.createTextNode(QString::number(grandchild->isChecked() ? 1 : 0));
            node.appendChild(text);
            root.appendChild(node);
        }

        foreach (const QRadioButton *grandchild, child->findChildren<QRadioButton*>())
        {
            QDomElement node = document.createElement(grandchild->objectName());
            QDomText text = document.createTextNode(QString::number(grandchild->isChecked() ? 1 : 0));
            node.appendChild(text);
            root.appendChild(node);
        }

        foreach (const QPushButton *grandchild, child->findChildren<QPushButton*>())
        {
            if (!grandchild->styleSheet().isEmpty())
            {
                QDomElement node = document.createElement(grandchild->objectName());
                node.setAttribute("styleSheet", grandchild->styleSheet());
                QDomText text = document.createTextNode(grandchild->toolTip());
                node.appendChild(text);
                root.appendChild(node);
            }
        }
    }
    
    std::string content(document.toString().toLocal8Bit());
    std::string fileName(widget->toolTip().isEmpty() ? widget->objectName().toLocal8Bit() : widget->toolTip().toLocal8Bit());
    QIO::saveFileContent(filePath + fileName + std::string(".settings"), content);
}