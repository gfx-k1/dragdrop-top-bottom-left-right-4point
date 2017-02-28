#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "draggablerectitem.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget* parent = 0);
private:
    QGraphicsView* view;
    QGraphicsScene* scene;
};

#endif // MAINWINDOW_H
