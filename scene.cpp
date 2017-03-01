#include "scene.h"

Scene::Scene(QObject* parent): QGraphicsScene(parent)
{
    sceneMode = NoMode;
    itemToDraw = 0;
}

bool Scene::enableEmitter = false;
bool Scene::enableSender = false;

void Scene::setMode(Mode mode){
    sceneMode = mode;
    QGraphicsView::DragMode vMode =
            QGraphicsView::NoDrag;
    if(mode == DrawLine){
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
    }
    else if(mode == SelectObject){
        makeItemsControllable(true);
        vMode = QGraphicsView::RubberBandDrag;
    }
    QGraphicsView* mView = views().at(0);
    if(mView)
        mView->setDragMode(vMode);
}

void Scene::setEmitter(bool se)
{
    enableEmitter = se;
    setMode(DrawLine);
}

void Scene::setSender(bool ss)
{
    enableSender = ss;
    setMode(SelectObject);
}

void Scene::makeItemsControllable(bool areControllable){
    foreach(QGraphicsItem* item, items()){
        item->setFlag(QGraphicsItem::ItemIsSelectable,
                      areControllable);
        //item->setFlag(QGraphicsItem::ItemIsMovable, areControllable);
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(sceneMode == DrawLine)
        origPoint = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(sceneMode == DrawLine){
        if(!itemToDraw){
            itemToDraw = new QGraphicsLineItem;
            this->addItem(itemToDraw);
            itemToDraw->setPen(QPen(Qt::black, 3, Qt::SolidLine));
            itemToDraw->setPos(origPoint);
        }
        itemToDraw->setLine(0,0,
                            event->scenePos().x() - origPoint.x(),
                            event->scenePos().y() - origPoint.y());
        itemToDraw->setZValue(50);
    }
    else
        QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    itemToDraw = 0;

    if(Scene::enableEmitter){emit quoteSenders(event->scenePos());}
    if(Scene::enableSender){emit copySender();}

    QGraphicsScene::mouseReleaseEvent(event);
    setSender(false);
    setEmitter(false);
}

void Scene::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete)
        foreach(QGraphicsItem* item, selectedItems()){
            removeItem(item);
            delete item;
        }
    else
        QGraphicsScene::keyPressEvent(event);
}
