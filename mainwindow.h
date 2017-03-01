#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>
#include "draggablerectitem.h"

#include <QToolBar>
#include "scene.h"
#include <QAction>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DraggableRectItem* dItem;
    Scene* scene;
    QGraphicsRectItem* itr1;
    QGraphicsRectItem* itr2;
public slots:
    void loadpoint(QPointF p);
    void line();
    void cancel();
    void selection();
    void rect1();
    void rect2();
    void test();
    void makecopy(QPointF pp);


};

#endif // MAINWINDOW_H
