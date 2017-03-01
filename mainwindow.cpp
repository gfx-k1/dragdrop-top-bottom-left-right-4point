#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    scene->setSceneRect(ui->gView->rect());
    ui->gView->setScene(scene);

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




    dItem = new DraggableRectItem();
    scene->addItem(dItem);
    dItem->setRect(rect);
    dItem->setPos(30,100);
    //dItem->setBrush(QBrush(QColor("#ffa07a")));
    dItem->setAnchorPoint(dItem->pos());

    connect(scene, SIGNAL(selectionChanged()), this, SLOT(test()));




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadpoint(QPointF p)
{
    qDebug() << "questopunto:...." << p;
}

void MainWindow::test()
{
    qDebug() << "mainwindow stupid point:...." << dItem->lastPoint();
}

