#ifndef MAP_H
#define MAP_H
#include"Shop.h"
#include"Object.h"
#include<QGraphicsSceneDragDropEvent>
#include<QMimeData>


class MapBlock:public Object
{
    Q_OBJECT

    //note:地图需要尺寸；格子类别，所有路径；特别的路径特点及buff为自由发挥
public:
        MapBlock();
        Shop * myshop;
       // void Create_Map();

        void setshop(Shop* shop);
        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void advance(int phase) override;
        void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
        void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
        void dropEvent(QGraphicsSceneDragDropEvent *event) override;


};







#endif // MAP_H
