#include"Object.h"
#include<QDebug>

Object::Object()
{
    x0=0;y0=0;
}

Object::Object(double x0,double y0,int hpmax, int itemType)
{
    hp_max=hpmax;
    hp_cur=hpmax;
    item_type=itemType;
    SetLocation(x0,y0);
}

Object::~Object()
{

}

void Object::SetLocation(double x1,double y1)
{
    x0=x1;y0=y1;
}

bool Object::isMapOrNot()
{
    if(item_type>0&&item_type<10)
        return true;
    else return false;
}

bool Object::isHeroOrNot()
{
    if(item_type>9&&item_type<20)
        return true;
    else return false;
}

bool Object::isEnemyOrNot()
{
    if(item_type>19&&item_type<30)
        return true;
    else return false;
}

QString Object::GetItemName()
{
        QString name;
        switch (this->item_type) {
        case(11):
            name = "洛SP";
            break;
        case(12):
            name = "庞";
            break;
        case(10):
            name="安洁莉亚";
            break;
        case(14):
            name="汀朵伊姆";
            break;
        case(15):
            name="琉SP";
            break;
        case(13):
            name="苏菲SP";
            break;
        case(16):
            name="时光书签";
            break;
        case(20):
            name="神殿鸟";
            break;
        case(21):
            name="盗贼普吉";
            break;
        case(22):
            name="柴犬";
            break;
        case(23):
            name="兔女郎";
            break;
        case(24):
            name="长翼飞龙";
            break;
        case(25):
            name="龙神教徒";
            break;
        }
        return name;
}

void Object::GetAttacked(int atk0)
{
    this->being_ATK=atk0;
    //qDebug()<<being_ATK;
        if(hp_cur>atk0)
       {
            this->hp_cur-=atk0;
            qDebug()<<GetItemName()<<"受到了"<<atk0<<"点伤害！还剩下"<<hp_cur<<"点血量！";
        }
        else {
            this->hp_cur=0;
            qDebug()<<GetItemName()<<"受到了致命一击！";
            this->myliving=false;
            //scene()->removeItem(this);
        }
}

void Object::SetWalkingMoive(QString path1)
{
    //qDebug()<<"get into";
    if(path1==path_1)
        return;

    //qDebug()<<"get here!";
    this->walkingMoive = new QMovie(path1);
    path_1=path1;
    walkingMoive->start();
}

