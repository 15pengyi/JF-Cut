/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <fstream>

#include <QtXml/QDomDocument>

#include "../utilities/QIO.h"
#include "QHoverPoints.h"

QHoverPoints::QHoverPoints(QWidget *widget, PointShape shape)
    : QObject(widget),
    m_connectionType(CurveConnection), m_sortType(NoSort), m_shape(shape),
    m_pointPen(QColor(255, 255, 255, 191), 1), m_connectionPen(QColor(255, 255, 255, 127), 2), m_pointBrush(QColor(191, 191, 191, 127)),
    m_pointSize(11, 11), m_currentIndex(-1),
    m_editable(true), m_enabled(true)
{
    m_widget = widget;
    widget->installEventFilter(this);
    widget->setAttribute(Qt::WA_AcceptTouchEvents);

    connect(this, SIGNAL(signalPointsChanged(QPolygonF)),
        m_widget, SLOT(update()));
}


void QHoverPoints::setEnabled(bool enabled)
{
    if (m_enabled != enabled) {
        m_enabled = enabled;
        m_widget->update();
    }
}


bool QHoverPoints::eventFilter(QObject *object, QEvent *event)
{
    if (object == m_widget && m_enabled) {
        switch (event->type()) {

    case QEvent::MouseButtonDblClick:
        {
            if (!m_fingerPointMapping.isEmpty())
                return true;
            QMouseEvent *me = (QMouseEvent *) event;

            QPointF clickPos = me->pos();
            int index = -1;
            for (int i=0; i<m_points.size(); ++i) {
                QPainterPath path;
                if (m_shape == CircleShape)
                    path.addEllipse(pointBoundingRect(i));
                else
                    path.addRect(pointBoundingRect(i));

                if (path.contains(clickPos)) {
                    index = i;
                    break;
                }
            }

            if (me->button() == Qt::LeftButton) {

                if (index != -1) 
                    m_currentIndex = index;
                else
                    return true;
            }

            QColorDialog* dlg = new QColorDialog(m_colors[m_currentIndex]);
            if (dlg->exec())
            {
                QColor color = dlg->selectedColor();
                color.setAlpha(200);
                m_colors[m_currentIndex] = color;
                emit signalPointsChanged();
            }
        }
        break;

    case QEvent::MouseButtonPress:
        {
            if (!m_fingerPointMapping.isEmpty())
                return true;
            QMouseEvent *me = (QMouseEvent *) event;

            QPointF clickPos = me->pos();
            int index = -1;
            for (int i=0; i<m_points.size(); ++i) {
                QPainterPath path;
                if (m_shape == CircleShape)
                    path.addEllipse(pointBoundingRect(i));
                else
                    path.addRect(pointBoundingRect(i));

                if (path.contains(clickPos)) {
                    index = i;
                    break;
                }
            }

            if (me->button() == Qt::LeftButton) {

                if (index == -1) {
                    if (!m_editable)
                        return false;
                    int pos = 0;
                    // Insert sort for x or y
                    if (m_sortType == XSort) {
                        for (int i=0; i<m_points.size(); ++i)
                            if (m_points[i].x() > clickPos.x()) {
                                pos = i;
                                break;
                            }
                    } else if (m_sortType == YSort) {
                        for (int i=0; i<m_points.size(); ++i)
                            if (m_points[i].y() > clickPos.y()) {
                                pos = i;
                                break;
                            }
                    }
                    
                    m_points.insert(pos, clickPos);
                    m_locks.insert(pos, 0);

                    qreal colorRatio(0.5), alphaRatio(0.5);
                    if (m_sortType == XSort) {
                        colorRatio = clickPos.x() / m_widget->width();
                        alphaRatio = clickPos.y() / m_widget->height();
                    } else if (m_sortType == YSort) {
                        colorRatio = clickPos.y() / m_widget->height();
                        alphaRatio = clickPos.x() / m_widget->width();
                    }
                    
                    m_colors.insert(pos, QColor(255 * colorRatio, 255 * colorRatio, 255 * colorRatio, alphaRatio));
                    m_currentIndex = pos;
                    firePointChange();

                    emit signalPointsChanged();
                } else {
                    m_currentIndex = index;
                }
                return true;

            } else if (me->button() == Qt::RightButton) {
                if (index >= 0 && m_editable) {
                    if (m_locks[index] == 0) {
                        m_locks.remove(index);
                        m_colors.remove(index);
                        m_points.remove(index);
                        emit signalPointsChanged();
                    }
                    firePointChange();
                    return true;
                }
            }

        }
        break;

    case QEvent::MouseButtonRelease:
        if (!m_fingerPointMapping.isEmpty())
            return true;
        m_currentIndex = -1;
        break;

    case QEvent::MouseMove:
        if (!m_fingerPointMapping.isEmpty())
            return true;
        if (m_currentIndex >= 0)
        {
            movePoint(m_currentIndex, ((QMouseEvent *)event)->pos());
            emit signalPointsChanged();
        }
        break;
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
        {
            const QTouchEvent *const touchEvent = static_cast<const QTouchEvent*>(event);
            const QList<QTouchEvent::TouchPoint> points = touchEvent->touchPoints();
            const qreal pointSize = qMax(m_pointSize.width(), m_pointSize.height());
            foreach (const QTouchEvent::TouchPoint &touchPoint, points) {
                const int id = touchPoint.id();
                switch (touchPoint.state()) {
    case Qt::TouchPointPressed:
        {
            // find the point, move it
            QSet<int> activePoints = QSet<int>::fromList(m_fingerPointMapping.values());
            int activePoint = -1;
            qreal distance = -1;
            const int pointsCount = m_points.size();
            const int activePointCount = activePoints.size();
            if (pointsCount == 2 && activePointCount == 1) { // only two points
                activePoint = activePoints.contains(0) ? 1 : 0;
            } else {
                for (int i=0; i<pointsCount; ++i) {
                    if (activePoints.contains(i))
                        continue;

                    qreal d = QLineF(touchPoint.pos(), m_points[i]).length();
                    if ((distance < 0 && d < 12 * pointSize) || d < distance) {
                        distance = d;
                        activePoint = i;
                    }

                }
            }
            if (activePoint != -1) {
                m_fingerPointMapping.insert(touchPoint.id(), activePoint);
                movePoint(activePoint, touchPoint.pos());
            }
        }
        break;
    case Qt::TouchPointReleased:
        {
            // move the point and release
            QHash<int,int>::iterator it = m_fingerPointMapping.find(id);
            movePoint(it.value(), touchPoint.pos());
            m_fingerPointMapping.erase(it);
        }
        break;
    case Qt::TouchPointMoved:
        {
            // move the point
            const int pointIdx = m_fingerPointMapping.value(id, -1);
            if (pointIdx >= 0) // do we track this point?
                movePoint(pointIdx, touchPoint.pos());
        }
        break;
    default:
        break;
                }
            }
            if (m_fingerPointMapping.isEmpty()) {
                event->ignore();
                return false;
            } else {
                return true;
            }
        }
        break;
    case QEvent::TouchEnd:
        if (m_fingerPointMapping.isEmpty()) {
            event->ignore();
            return false;
        }
        return true;
        break;

    case QEvent::Resize:
        {
            QResizeEvent *e = (QResizeEvent *) event;
            if (e->oldSize().width() == 0 || e->oldSize().height() == 0)
                break;
            qreal stretch_x = e->size().width() / qreal(e->oldSize().width());
            qreal stretch_y = e->size().height() / qreal(e->oldSize().height());
            if (e->oldSize().width() == -1 || e->oldSize().width() == -1)
            {
                stretch_x = e->size().width() / 100.0;
                stretch_y = e->size().height() / 30.0;
            }
            for (int i=0; i<m_points.size(); ++i) {
                QPointF p = m_points[i];
                movePoint(i, QPointF(p.x() * stretch_x, p.y() * stretch_y), false);
            }

            firePointChange();
            break;
        }

    case QEvent::Paint:
        {
            QWidget *that_widget = m_widget;
            m_widget = 0;
            QApplication::sendEvent(object, event);
            m_widget = that_widget;
            paintPoints();
#ifdef QT_OPENGL_SUPPORT
            ArthurFrame *af = qobject_cast<ArthurFrame *>(that_widget);
            if (af && af->usesOpenGL())
                af->glWidget()->swapBuffers();
#endif
            return true;
        }
    default:
        break;
        }
    }

    return false;
}


void QHoverPoints::paintPoints()
{
    QPainter p;
#ifdef QT_OPENGL_SUPPORT
    ArthurFrame *af = qobject_cast<ArthurFrame *>(m_widget);
    if (af && af->usesOpenGL())
        p.begin(af->glWidget());
    else
        p.begin(m_widget);
#else
    p.begin(m_widget);
#endif

    p.setRenderHint(QPainter::Antialiasing);

    if (m_connectionPen.style() != Qt::NoPen && m_connectionType != NoConnection) {
        p.setPen(m_connectionPen);

        if (m_connectionType == CurveConnection) {
            QPainterPath path;
            path.moveTo(m_points[0]);
            for (int i=1; i<m_points.size(); ++i) {
                QPointF p1 = m_points[i-1];
                QPointF p2 = m_points[i];
                qreal distance = p2.x() - p1.x();

                path.cubicTo(p1.x() + distance / 2, p1.y(),
                    p1.x() + distance / 2, p2.y(),
                    p2.x(), p2.y());
            }
            p.drawPath(path);
        } else {
            p.drawPolyline(m_points);
        }
    }

    p.setPen(m_pointPen);
    p.setBrush(m_pointBrush);

    for (int i=0; i<m_points.size(); ++i) {
        QRectF bounds = pointBoundingRect(i);
        if (m_shape == CircleShape)
            p.drawEllipse(bounds);
        else
            p.drawRect(bounds);
    }
}

static QPointF bound_point(const QPointF &point, const QRectF &bounds, int lock)
{
    QPointF p = point;

    qreal left = bounds.left();
    qreal right = bounds.right();
    qreal top = bounds.top();
    qreal bottom = bounds.bottom();

    if (p.x() < left || (lock & QHoverPoints::LockToLeft)) p.setX(left);
    else if (p.x() > right || (lock & QHoverPoints::LockToRight)) p.setX(right);

    if (p.y() < top || (lock & QHoverPoints::LockToTop)) p.setY(top);
    else if (p.y() > bottom || (lock & QHoverPoints::LockToBottom)) p.setY(bottom);

    return p;
}

void QHoverPoints::setPoints(const QPolygonF &points)
{
    if (points.size() != m_points.size())
        m_fingerPointMapping.clear();
    m_points.clear();
    for (int i = 0; i < points.size(); ++i)
        m_points << bound_point(points[i], boundingRect(), 0);

    m_locks.clear();
    if (m_points.size() > 0) {
        m_locks.resize(m_points.size());
        m_locks.fill(0);
        m_colors.resize(m_points.size());
        m_colors.fill(QColor(255, 255, 255, 200));
    }
}

void QHoverPoints::setColors(const QVector<QColor> &colors)
{
    m_colors.clear();
    for (int i = 0; i < colors.size(); ++i)
        m_colors << colors[i];
}

void QHoverPoints::movePoint(int index, const QPointF &point, bool emitUpdate)
{
    m_points[index] = bound_point(point, boundingRect(), m_locks[index]);
    if (emitUpdate)
        firePointChange();
}


inline static bool x_less_than(const QPointF &p1, const QPointF &p2)
{
    return p1.x() < p2.x();
}


inline static bool y_less_than(const QPointF &p1, const QPointF &p2)
{
    return p1.y() < p2.y();
}

void QHoverPoints::firePointChange()
{
    if (m_sortType != NoSort) {

        QPointF oldCurrent;
        if (m_currentIndex != -1) {
            oldCurrent = m_points[m_currentIndex];
        }

        if (m_sortType == XSort)
            qSort(m_points.begin(), m_points.end(), x_less_than);
        else if (m_sortType == YSort)
            qSort(m_points.begin(), m_points.end(), y_less_than);

        // Compensate for changed order...
        if (m_currentIndex != -1) {
            for (int i=0; i<m_points.size(); ++i) {
                if (m_points[i] == oldCurrent) {
                    m_currentIndex = i;
                    break;
                }
            }
        }
    }
    
    emit signalPointsChanged(m_points);
}

void QHoverPoints::load(const std::string &filePath, const QSize &size)
{
    std::string content;
    std::string fileName("Transfer Function");
    if (!QIO::getFileContent(filePath + fileName + std::string(".settings"), content)) return;

    QDomDocument document;
    if (!document.setContent(QString(content.c_str()))) return;

    QDomElement root = document.firstChildElement("QHoverPoints");
    if (root.isNull()) return;

    QDomElement node = root.firstChildElement("QPolygonF");
    if (node.isNull()) return;

    int s = node.attribute("Size").toInt();
    int t = node.attribute("ConnectionType").toInt();
    if (s < 2) return;

    QPolygonF points;
    QVector<QColor> colors;
    for (QDomElement point = node.firstChildElement("QPointF"); !point.isNull(); point = point.nextSiblingElement())
    {
        points.push_back(QPointF(point.attribute("X").toFloat() * size.width(), point.attribute("Y").toFloat() * size.height()));
        colors.push_back(QColor(point.attribute("R").toInt(), point.attribute("G").toInt(), point.attribute("B").toInt()));
    }
    if (points.size() < s) return;
    
    setPoints(points);
    setColors(colors);
    setPointLock(0, QHoverPoints::LockToLeft);
    setPointLock(s - 1, QHoverPoints::LockToRight);
    setSortType(QHoverPoints::XSort);
    setConnectionType(t ? CurveConnection : LineConnection);

    emit signalPointsChanged();
}

void QHoverPoints::save(const std::string &filePath, const QSize &size)
{
    QDomDocument document;

    QDomProcessingInstruction instruction = document.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    document.appendChild(instruction);

    QDomElement root = document.createElement("QHoverPoints");
    document.appendChild(root);

    QDomElement node = document.createElement("QPolygonF");
    node.setAttribute("Size", m_points.size());
    node.setAttribute("ConnectionType", m_connectionType == CurveConnection ? 1 : 0);
    root.appendChild(node);

    for (int i = 0; i < m_points.size(); i++)
    {
        QDomElement point = document.createElement("QPointF");
        point.setAttribute("X", m_points[i].x() / size.width());
        point.setAttribute("Y", m_points[i].y() / size.height());
        point.setAttribute("R", m_colors[i].red());
        point.setAttribute("G", m_colors[i].green());
        point.setAttribute("B", m_colors[i].blue());
        node.appendChild(point);
    }
    
    std::string content(document.toString().toLocal8Bit());
    std::string fileName("Transfer Function");
    QIO::saveFileContent(filePath + fileName + std::string(".settings"), content);
}