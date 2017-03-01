#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QAction>
#include <QGraphicsView>
#include <QKeyEvent>#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QObject>


class Scene : public QGraphicsScene
{
   Q_OBJECT

public:
    enum Mode {NoMode, SelectObject, DrawLine};
    Scene(QObject* parent = 0);
    void setMode(Mode mode);
    static bool enableEmitter;
    static bool enableSender;

public slots:
    void setEmitter(bool se);
    void setSender(bool ss);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    Mode sceneMode;
    QPointF origPoint;
    QGraphicsLineItem* itemToDraw;
    void makeItemsControllable(bool areControllable);

signals:
    void quoteSenders(QPointF);
    void trytomake();
    void copySender();


};

#endif // SCENE_H
