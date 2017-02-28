#include "draggablerectitem.h"
#include <algorithm>
#include <math.h>
#include <QVector>

DraggableRectItem::DraggableRectItem(QGraphicsItem* parent):
    QGraphicsRectItem(parent), m_dragged(false)
{
    setFlags(QGraphicsItem::ItemIsSelectable|
             QGraphicsItem::ItemIsMovable);
}

QPointF DraggableRectItem::movepos(0,0);

void DraggableRectItem::setAnchorPoint(const QPointF &anchorPoint){
    this->anchorPoint = anchorPoint;
}

void DraggableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    m_dragged = true;
    movepos.setX(event->scenePos().x());
    movepos.setY(event->scenePos().y());
    QGraphicsRectItem::mouseMoveEvent(event);
}

void DraggableRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    QLineF line;
    QLineF linetl;
    QLineF linetr;
    QLineF linebl;
    QLineF linebr;
    QVector<double> list1;
    int positiochooser = 0;

    if(m_dragged){
        QList<QGraphicsItem*> colItems = collidingItems();
        if(colItems.isEmpty())
            this->setPos(anchorPoint);
        else {
            QGraphicsItem* closestItem = colItems.at(0);
            qreal shortestDist = 100000;
            foreach(QGraphicsItem* item, colItems){

                linetl = QLineF(item->sceneBoundingRect().topLeft(), movepos);
                linetr = QLineF(item->sceneBoundingRect().topRight(), movepos);
                linebl = QLineF(item->sceneBoundingRect().bottomLeft(), movepos);
                linebr = QLineF(item->sceneBoundingRect().bottomRight(), movepos);
                line = QLineF(item->sceneBoundingRect().center(), this->sceneBoundingRect().center());

                //l = std::fmin(std::fmin((std::fmin(linetl.length(), linetr.length())), linebl.length()), linebr.length());

                if(line.length() < shortestDist){
                    shortestDist = line.length();
                    closestItem = item;
                    list1.append(double(linetl.length()));
                    list1.append(double(linetr.length()));
                    list1.append(double(linebl.length()));
                    list1.append(double(linebr.length()));
                    double min = *std::min_element(list1.constBegin(), list1.constEnd());
                    if(min == double(linetl.length())){positiochooser = 1;}
                    else if(min == double(linetr.length())){positiochooser = 2;}
                    else if(min == double(linebl.length())){positiochooser = 3;}
                    else if(min == double(linebr.length())){positiochooser = 4;}
                    else if((movepos.x() == 0) && (movepos.y()==0)){positiochooser = 0;}
                    list1.clear();
                }


            }
            switch (positiochooser) {
            case 1:
                this->setPos(QPointF(closestItem->scenePos().x()-50, closestItem->scenePos().y()-50));
                break;
            case 2:
                this->setPos(QPointF(closestItem->scenePos().x()+50, closestItem->scenePos().y()-50));
                break;
            case 3:
                this->setPos(QPointF(closestItem->scenePos().x()-50, closestItem->scenePos().y()+50));
                break;
            case 4:
                this->setPos(QPointF(closestItem->scenePos().x()+50, closestItem->scenePos().y()+50));
                break;
            default:
                this->setPos(anchorPoint);
                break;
            }
            /*if(l==linetl.length()){
                this->setPos(QPointF(closestItem->scenePos().x()-50, closestItem->scenePos().y()-50));
            }
            else if(l==linetr.length()){
                this->setPos(QPointF(closestItem->scenePos().x()+50, closestItem->scenePos().y()-50));
            }
            else if(l==linebl.length()){
                this->setPos(QPointF(closestItem->scenePos().x()-50, closestItem->scenePos().y()+50));
            }
            else if(l==linebr.length()){
                this->setPos(QPointF(closestItem->scenePos().x()+50, closestItem->scenePos().y()+50));
            }*/
            //this->setPos(QPointF(closestItem->scenePos().x()+50, closestItem->scenePos().y()+50));
            //this->setPos(QPointF(closestItem->scenePos().x()-50, closestItem->scenePos().y()-50));
            //this->setPos(QPointF(closestItem->scenePos().x()+50, closestItem->scenePos().y()-50));
            //this->setPos(QPointF(closestItem->scenePos().x()-50, closestItem->scenePos().y()+50));

        }
        m_dragged = false;
    }
    QGraphicsRectItem::mouseReleaseEvent(event);
}
