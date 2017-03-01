#ifndef DRAGGABLERECTITEM_H
#define DRAGGABLERECTITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QObject>


class DraggableRectItem : public QObject, public QGraphicsItem
{
   Q_OBJECT
   Q_INTERFACES(QGraphicsItem)

public:
    DraggableRectItem(QGraphicsItem* parent = 0);

    void setAnchorPoint(const QPointF &anchorPoint);
    static QPointF movepos;
    static QPointF enterpos;
    static bool firstpos;
    QRectF boundingRect() const { return rect; }
    QPointF lastPoint() { return m_p; }
    void setRect(QRectF r) {rect = r;}
    void getPos(QPointF pf){ m_p.setX(pf.x()); m_p.setY(pf.y());}
public slots:

    //void loadppoint(QPointF);


protected slots:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF rect;
    QPointF anchorPoint;
    bool m_dragged;
    QPen m_pen;
    QBrush m_brush;
    QPoint m_p;
    //void getPos(QPointF pf){ m_p = pf;}

signals:

   void emitpoint(QPointF);

};

#endif // DRAGGABLERECTITEM_H
