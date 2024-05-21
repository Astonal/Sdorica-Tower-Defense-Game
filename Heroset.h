#ifndef HEROSET_H
#define HEROSET_H

#include"Object.h"
#include<QGraphicsSceneMouseEvent>
#include<QDrag>
#include<QMimeData>
#include<QImage>

class Heroset:public Object
{
public:

    Heroset(int x,int y,QString path,int itemtype);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override{}
    void Cooling(){coolingTime=25;}

    QImage* img_hero;
    QString hero_path;
    int coolingTime;
    int hero_type;
    bool ableBuyOrNot;



};















#endif // HEROSET_H
