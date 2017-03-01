#include "draggablerectitem.h"
#include <algorithm>
#include <math.h>
#include <QVector>
#include <QtGlobal>
#include <QDebug>

int positiochooser = 0;
int colourchooser = 0;

DraggableRectItem::DraggableRectItem(QGraphicsItem *parent):
    QGraphicsItem(parent), m_dragged(false)
{
    setFlags(QGraphicsItem::ItemIsSelectable|
             QGraphicsItem::ItemIsMovable);

    //connect(this, SIGNAL(emitpoint(QPointF)), this, SLOT(loadppoint(QPointF)));

}

QPointF DraggableRectItem::movepos(0,0);
QPointF DraggableRectItem::enterpos(0,0);
bool DraggableRectItem::firstpos = false;

void DraggableRectItem::setAnchorPoint(const QPointF &anchorPoint){
    this->anchorPoint = anchorPoint;
}

QPointF DraggableRectItem::lastPoint()
{
    return m_p;
    qDebug() << "chiamata ...:" << m_p;
}

void DraggableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    enterpos.setX(event->pos().x());
    enterpos.setY(event->pos().y());


    QVector<double> list2;

    QLineF linemtl = QLineF(boundingRect().topLeft(), enterpos);
    QLineF linemtr = QLineF(boundingRect().topRight(), enterpos);
    QLineF linembl = QLineF(boundingRect().bottomLeft(), enterpos);
    QLineF linembr = QLineF(boundingRect().bottomRight(), enterpos);

    list2.append(double(linemtl.length()));
    list2.append(double(linemtr.length()));
    list2.append(double(linembl.length()));
    list2.append(double(linembr.length()));
    double minM = *std::min_element(list2.constBegin(), list2.constEnd());
    if(minM == double(linemtl.length())){colourchooser = 1;}
    else if(minM == double(linemtr.length())){colourchooser = 2;}
    else if(minM == double(linembl.length())){colourchooser = 3;}
    else if(minM == double(linembr.length())){colourchooser = 4;}
    else if((enterpos.x() == 0) && (enterpos.y()==0)){positiochooser = 0; colourchooser = 0;}
    list2.clear();
    QGraphicsItem::mousePressEvent(event);
}


void DraggableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    m_dragged = true;
    movepos.setX(event->scenePos().x());
    movepos.setY(event->scenePos().y());

    QGraphicsItem::mouseMoveEvent(event);
}

void DraggableRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){


    positiochooser = 0;
    qreal min = 0;
    qreal mis1 = 0;
    qreal mis2 = 0;
    qreal mis3 = 0;
    QPointF p;
    p.setX(event->scenePos().x());
    p.setY(event->scenePos().y());



    if(m_dragged){
        QList<QGraphicsItem*> colItems = collidingItems();
        if(colItems.isEmpty())
            this->setPos(anchorPoint);
        else {
            QGraphicsItem* closestItem = colItems.at(0);
            qreal shortestDist = 100000;
            foreach(QGraphicsItem* item, colItems){
               // if(closestItem->contains(movepos))
                //{
                    switch (colourchooser) {
                    case 1:
                        if(item->sceneBoundingRect().contains(p)){
                        mis1 = QLineF(item->sceneBoundingRect().topRight(),  p).length();
                        mis2 = QLineF(item->sceneBoundingRect().bottomRight(),  p).length();
                        mis3 = QLineF(item->sceneBoundingRect().bottomLeft(),  p).length();
                        if((mis1 < mis2) && (mis1 < mis3)){min = mis1;}else{if(mis3 < mis2){min = mis3;}else{min = mis2;}}

                        if(min < shortestDist){
                            shortestDist = min;
                            closestItem = item;
                        }
                        if(min == mis1)
                        {
                            this->setPos(QPointF(closestItem->scenePos().x()+80, closestItem->scenePos().y()));
                        }
                        if(min == mis2)
                        {
                            this->setPos(QPointF(closestItem->scenePos().x()+80, closestItem->scenePos().y()+50));
                        }
                        if(min == mis3)
                        {
                            this->setPos(QPointF(closestItem->scenePos().x(), closestItem->scenePos().y()+50));
                        }
                        //qDebug() << "1 topright/topleft:  " << mis1;
                        //qDebug() << "1 Bottomright/topleft:  " << mis2;
                        //firstpos = true;
                        }
                        break;
                    case 2:
                        if(item->sceneBoundingRect().contains(p)){
                        mis1 = QLineF(item->sceneBoundingRect().topLeft(), p).length();
                        mis2 = QLineF(item->sceneBoundingRect().bottomLeft(), p).length();
                        mis3 = QLineF(item->sceneBoundingRect().bottomRight(),  p).length();
                        if((mis1 < mis2) && (mis1 < mis3)){min = mis1;}else{if(mis3 < mis2){min = mis3;}else{min = mis2;}}
                        if(min < shortestDist){
                            shortestDist = min;
                            closestItem = item;
                        }
                        if(min == mis1)
                        {
                            this->setPos(QPointF(closestItem->scenePos().x()-80, closestItem->scenePos().y()));
                        }
                        if(min == mis2)
                        {
                            this->setPos(QPointF(closestItem->scenePos().x()-80, closestItem->scenePos().y()+50));
                        }
                        if(min == mis3)
                        {
                            this->setPos(QPointF(closestItem->scenePos().x(), closestItem->scenePos().y()+50));
                        }
                        //qDebug() << "2 topLeft/topRight:  " << mis1;
                        //qDebug() << "2 bottomLeft/topRight:  " << mis2;
                        //firstpos = true;
                        }
                        break;
                    case 3:
                        if(item->sceneBoundingRect().contains(p)){
                        mis1 = QLineF(item->sceneBoundingRect().topRight(), p).length();
                        mis2 = QLineF(item->sceneBoundingRect().bottomRight(), p).length();
                        mis3 = QLineF(item->sceneBoundingRect().topLeft(),  p).length();
                        if((mis1 < mis2) && (mis1 < mis3)){min = mis1;}else{if(mis3 < mis2){min = mis3;}else{min = mis2;}}
                        if(min < shortestDist){
                            shortestDist = min;
                            closestItem = item;
                        }
                        if(min == mis1)
                        {
                            this->setPos(QPointF(closestItem->scenePos().x()+80, closestItem->scenePos().y()-50));
                        }
                        if(min == mis2)
                        {
                            this->setPos(QPointF(closestItem->scenePos().x()+80, closestItem->scenePos().y()));
                        }
                        if(min == mis3)
                        {
                            this->setPos(QPointF(closestItem->scenePos().x(), closestItem->scenePos().y()-50));
                        }
                        //qDebug() << "3 topright/bottomLeft:  " << mis1;
                        //qDebug() << "3 bottomright/bottomLeft:  " << mis2;
                        //firstpos = true;
                        }
                        break;
                    case 4:
                        if(item->sceneBoundingRect().contains(p)){
                        mis1 = QLineF(item->sceneBoundingRect().topLeft(), p).length();
                        mis2 = QLineF(item->sceneBoundingRect().bottomLeft(), p).length();
                        mis3 = QLineF(item->sceneBoundingRect().topRight(),  p).length();
                        if((mis1 < mis2) && (mis1 < mis3)){min = mis1;}else{if(mis3 < mis2){min = mis3;}else{min = mis2;}}
                        if(min < shortestDist){
                            shortestDist = min;
                            closestItem = item;
                        }
                        if(min == mis1)
                        {
                            this->setPos(QPointF(closestItem->scenePos().x()-80, closestItem->scenePos().y()-50));
                        }
                        if(min == mis2)
                        {
                            this->setPos(QPointF(closestItem->scenePos().x()-80, closestItem->scenePos().y()));
                        }
                        if(min == mis3)
                        {
                            this->setPos(QPointF(closestItem->scenePos().x(), closestItem->scenePos().y()-50));
                        }
                        //qDebug() << "4 topLeft/bottomright:  " << mis1;
                        //qDebug() << "4 bottomLeft/bottomright:  " << mis2;
                        //firstpos = true;
                        }
                        break;
                    default:
                        this->setPos(anchorPoint);
                        break;
                    }

                    //qDebug() << "debugpos ....." << this->pos();



            }
            //getPos(this->pos());
            m_p.setX(this->pos().x());
            m_p.setY(this->pos().y());
            emit emitpoint(m_p);
            qDebug() << "mystupid pos ....." << m_p;

        }
        enterpos.setX(0);
        enterpos.setY(0);
        colourchooser = 0;
        m_dragged = false;
        firstpos = false;
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

void DraggableRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //option Q_UNUSED;
    //widget Q_UNUSED;
    painter->setBrush(QBrush(Qt::NoBrush));
    painter->drawRect(boundingRect().topLeft().x(), boundingRect().topLeft().y(), 80,50);


    switch (colourchooser) {
    case 1:
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        painter->drawRect(boundingRect().topLeft().x(), boundingRect().topLeft().y(), 20,20);
        painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        painter->drawRect(boundingRect().topRight().x(), boundingRect().topRight().y(), -20,20);
        painter->drawRect(boundingRect().bottomLeft().x(), boundingRect().bottomLeft().y(), 20,-20);
        painter->drawRect(boundingRect().bottomRight().x(), boundingRect().bottomRight().y(), -20,-20);
        break;
    case 2:
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        painter->drawRect(boundingRect().topRight().x(), boundingRect().topRight().y(), -20,20);
        painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        painter->drawRect(boundingRect().topLeft().x(), boundingRect().topLeft().y(), 20,20);
        painter->drawRect(boundingRect().bottomLeft().x(), boundingRect().bottomLeft().y(), 20,-20);
        painter->drawRect(boundingRect().bottomRight().x(), boundingRect().bottomRight().y(), -20,-20);
        break;
    case 3:
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        painter->drawRect(boundingRect().bottomLeft().x(), boundingRect().bottomLeft().y(), 20,-20);
        painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        painter->drawRect(boundingRect().topLeft().x(), boundingRect().topLeft().y(), 20,20);
        painter->drawRect(boundingRect().topRight().x(), boundingRect().topRight().y(), -20,20);
        painter->drawRect(boundingRect().bottomRight().x(), boundingRect().bottomRight().y(), -20,-20);
        break;
    case 4:
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        painter->drawRect(boundingRect().bottomRight().x(), boundingRect().bottomRight().y(), -20,-20);
        painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        painter->drawRect(boundingRect().topLeft().x(), boundingRect().topLeft().y(), 20,20);
        painter->drawRect(boundingRect().topRight().x(), boundingRect().topRight().y(), -20,20);
        painter->drawRect(boundingRect().bottomLeft().x(), boundingRect().bottomLeft().y(), 20,-20);
        break;
    default:
        painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        painter->drawRect(boundingRect().topLeft().x(), boundingRect().topLeft().y(), 20,20);
        painter->drawRect(boundingRect().topRight().x(), boundingRect().topRight().y(), -20,20);
        painter->drawRect(boundingRect().bottomLeft().x(), boundingRect().bottomLeft().y(), 20,-20);
        painter->drawRect(boundingRect().bottomRight().x(), boundingRect().bottomRight().y(), -20,-20);
        break;
    }

    update();
}

/*void DraggableRectItem::loadppoint(QPointF)
{

}*/
