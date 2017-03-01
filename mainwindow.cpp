#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Scene();
    scene->setSceneRect(ui->gView->rect());
    ui->gView->setScene(scene);

    ui->gView->setRenderHint(QPainter::Antialiasing);

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


    ui->gView->setRenderHint(QPainter::Antialiasing);
    QGraphicsRectItem* itr = new QGraphicsRectItem();
    itr->setRect(20,20,100,100);
    itr->setZValue(10);
    itr1 = new QGraphicsRectItem();
    itr2 = new QGraphicsRectItem();
    itr1->setRect(20,80,100,100);
    itr1->setZValue(50);
    scene->addItem(itr);
    scene->addItem(itr1);

    rect1();
    rect2();





    connect(ui->line, SIGNAL(pressed()), this, SLOT(line()));
    connect(ui->selection, SIGNAL(pressed()), this, SLOT(selection()));
    connect(ui->cancel, SIGNAL(pressed()), this, SLOT(cancel()));






    dItem = new DraggableRectItem();
    scene->addItem(dItem);
    dItem->setRect(rect);
    dItem->setPos(30,100);
    //dItem->setBrush(QBrush(QColor("#ffa07a")));
    dItem->setAnchorPoint(dItem->pos());

    //connect(scene, SIGNAL(selectionChanged()), this, SLOT(test()));
    connect(scene, SIGNAL(copySender()), this, SLOT(test()));
    connect(scene, SIGNAL(quoteSenders(QPointF)), this, SLOT(loadpoint(QPointF)));
    connect(dItem, SIGNAL(emitpoint(QPointF)), this, SLOT(makecopy(QPointF)));




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadpoint(QPointF p)
{
    qDebug() << "on quotesenders point:...." << p;
}

void MainWindow::test()
{
    qDebug() << "mainwindow on copysender:...." << dItem->lastPoint();
}

void MainWindow::makecopy(QPointF pp)
{
    qDebug() << "mainwindow on dItem:...." << pp;
}

void MainWindow::selection()
{
    //scene->setMode(Scene::SelectObject);
    scene->setSender(true);
}

void MainWindow::line()
{
     //scene->setMode(Scene::DrawLine);
     scene->setEmitter(true);
}

void MainWindow::cancel()
{
    QList<QGraphicsItem* > item = scene->items();
    for(int e = 0; e < item.size(); e++)
    {
        if((item[e]->zValue() > 45) && (item[e]->zValue() < 55))
        {
            scene->removeItem(item[e]);
        }

    }
}

void MainWindow::rect1()
{
    for ( int i = 0; i<30; i++)
    {
        //QGraphicsRectItem* itr2 = new QGraphicsRectItem();

        itr2 = scene->addRect((5*i),(6*i),30,30);
        itr2->setRect((5*i),(6*i),30,30);
        itr2->setZValue(50);
        //scene->addItem(itr2);
    }
}

void MainWindow::rect2()
{
    QGraphicsRectItem* itra = new QGraphicsRectItem();
    itra->setRect(-50,30,100,100);
    itra->setZValue(50);
    QGraphicsRectItem* itra1 = new QGraphicsRectItem();
    itra1->setRect(-100,400,100,100);
    itra1->setZValue(50);
    scene->addItem(itra);
    scene->addItem(itra1);
}



