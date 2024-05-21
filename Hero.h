#ifndef HERO_H
#define HERO_H

#include<QPainter>
#include<QStyleOptionGraphicsItem>
#include<QWidget>
#include"Object.h"
#include"tools.h"
#include<QDebug>

extern int stones;
class Hero:public Object
{
    Q_OBJECT
public:
    Hero(double x,double y,int hp,int itemtype);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    QRectF boundingRect() const override;
    bool is_clicked;
    int Hero_type;

   // QString HeroType();
};

//note:LAWSP=10,近战, 攻击2-3格内地面单位
//PANG=11,近战，在血量归零时往前滚去，每个减一定HP//extra
//ANJIE=12,近战，阻挡数为0，加buff//extra
//YIMU=13,近战，能攻击飞行单位和地面单位
//LIUSP=14,远程，能攻击飞行单位和地面单位
//FENGGUO=15,近战，发小刀攻击1排地面单位
//DILAN=16,近战，攻击力为0，阻拦数严格大于0//extra
//FUHUN=17,随机生成一种符合条件的，抽卡//extra
//QIONGAN=18,远程，只攻击地面单位
//LITTLEPANG=19,近战，阻挡数为0，产透晶石
class LawSP:public Hero{
    Q_OBJECT
public:
        LawSP(double x,double y);
        void advance(int phase)override;
        void Attack();
};

class Pang:public Hero{
    Q_OBJECT
public:
    Pang(double x,double y);
    void advance(int phase)override;
    void Attack();
    QRectF boundingRect() const override;
    bool roll;
};

class SophieSP:public Hero{
    Q_OBJECT
public:
    SophieSP(double x,double y);
    void advance(int phase)override;
    void Check();

};

class AnJie:public Hero{
    Q_OBJECT
public:
    int interval_of_stone;
    AnJie(double x,double y);
    void advance(int phase)override;
    void Attack();
    QRectF boundingRect() const override;
};

class YiMu:public Hero{
    Q_OBJECT
public:
    YiMu(double x,double y);
    void advance(int phase)override;
    void Attack();
    QRectF boundingRect() const override;
};

class LiuSP:public Hero{
    Q_OBJECT
public:
    LiuSP(double x,double y);
    void advance(int phase)override;
    void Attack();
    QRectF boundingRect() const override;

};

class Yaxin:public Hero{
    Q_OBJECT
public:
    Yaxin(double x,double y);
    void advance(int phase)override;
    void Attack();
    QRectF boundingRect() const override;

};


#endif // HERO_H
