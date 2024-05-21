#ifndef OBJECT_H
#define OBJECT_H

#include<QObject>
#include<QGraphicsItem>
#include<QGraphicsScene>
#include<QMovie>
#include<QString>
#include<QPainter>
#include"tools.h"

class coordinate
{
public:
    double xc,yc;
    coordinate(double x1,double y1):xc(x1),yc(y1){}
    coordinate(const coordinate* a){xc=a->xc;yc=a->yc;}


};


class Object:public QObject , public QGraphicsItem
{
        Q_OBJECT
public:
    Object();
    Object(double x,double y)
    {
        SetLocation(x,y);
    }
    Object(double x,double y,int hp,int item_type);

    ~Object();

//坐标函数
    void SetLocation(double x,double y);
    void Set_X(double x1){x0=x1;this->setPos(x0,y0);}
    void Set_Y(double y1){y0=y1;this->setPos(x0,y0);}
    int getX(){return x0;}
    int getY(){return y0;}
    void SetCor(const coordinate* m){x0=m->xc;y0=m->yc;this->setPos(x0,y0);}
    coordinate getXY(){return coordinate(x0,y0); }

//
    void setType(int t){item_type=t;}
    int getItemType(){return item_type;}
    bool isHeroOrNot();
    bool isEnemyOrNot();
    bool isMapOrNot();

//

    bool WalkingEndOrNot(){return walkingMoive->frameCount()==walkingMoive->currentFrameNumber();}

    void SetWalkingMoive(QString path1);


    bool IsWalkingEnd()
    {
        return walkingMoive->frameCount()-1==walkingMoive->currentFrameNumber();
    }

    bool IsLivingOrNot(){return myliving;}
    void DeleteItem()
    {
        if(!IsLivingOrNot())
            scene()->removeItem(this);
    }

    QString GetItemName();

    void GetAttacked(int atk0);



//参数们
    double x0,y0;//坐标
    int item_type;//种类
    bool myliving;//生命
    bool is_atking;
    //bool being_atked;
    int being_ATK;
    //生物
    int hp_cur,hp_max;//血量
    int atk_cur;//攻击值
    int atk_range;//攻击范围


    QMovie *walkingMoive;
    QMovie *dyingMoive;
    QString path_1;



 };





#endif // OBJECT_H
