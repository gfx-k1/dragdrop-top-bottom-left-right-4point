#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,680,640);
    view = new QGraphicsView(scene);
    setCentralWidget(view);

    QRectF rect(0,0,50,50);
    QBrush myBrush(Qt::darkGray, Qt::Dense5Pattern);


    for(int e = 150; e<500; e = e +55)
    {
        for(int i = 100; i<500; i = i +55)
        {

            QGraphicsRectItem *rItem1 = new QGraphicsRectItem(rect);
            scene->addItem(rItem1);
            rItem1->setPos(e,i);
            rItem1->setBrush(myBrush);
        }
    }




    DraggableRectItem* dItem = new DraggableRectItem;
    scene->addItem(dItem);
    dItem->setRect(rect);
    dItem->setPos(30,100);
    dItem->setBrush(QBrush(QColor("#ffa07a")));
    dItem->setAnchorPoint(dItem->pos());
}
