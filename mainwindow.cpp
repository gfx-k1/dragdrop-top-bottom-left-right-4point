#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,680,640);
    view = new QGraphicsView(scene);
    setCentralWidget(view);

    QRectF rect(0,0,80,50);
    QBrush myBrush(Qt::darkGray, Qt::Dense5Pattern);

    for(int e = 400; e<550; e = e +80)
    {
        for(int i = 100; i<250; i = i +50)
        {

            QGraphicsRectItem *rItem1 = new QGraphicsRectItem(rect);
            scene->addItem(rItem1);
            rItem1->setPos(e,i);
            rItem1->setBrush(myBrush);
        }
    }

    for(int e = 160; e<550; e = e +80)
    {
        for(int i = 250; i<550; i = i +50)
        {

            QGraphicsRectItem *rItem1 = new QGraphicsRectItem(rect);
            scene->addItem(rItem1);
            rItem1->setPos(e,i);
            rItem1->setBrush(myBrush);
        }
    }




    DraggableRectItem* dItem = new DraggableRectItem();
    scene->addItem(dItem);
    dItem->setRect(rect);
    dItem->setPos(30,100);
    //dItem->setBrush(QBrush(QColor("#ffa07a")));
    dItem->setAnchorPoint(dItem->pos());


    connect(dItem, &DraggableRectItem::emitpoint, this, &MainWindow::loadpoint);

}

void MainWindow::loadpoint(QPointF p)
{
    qDebug() << "questopunto:...." << p;
}

