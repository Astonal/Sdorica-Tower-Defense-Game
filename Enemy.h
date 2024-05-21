#ifndef ENEMY_H
#define ENEMY_H

#include<QPainter>
#include<QStyleOptionGraphicsItem>
#include<QWidget>
#include"Object.h"
#include"tools.h"
#include<QDebug>
#include"Bullet.h"

class Enemy:public Object
{
    Q_OBJECT
public:
    Enemy(double x,double y,int hp,int itemtype);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    QRectF boundingRect() const override;

    bool atk_flag;
    int Enemy_type;
    bool cross_or_not;
    bool blood_or_not;
    bool sharp_or_not;
};

class ChaiDog:public Enemy{
     Q_OBJECT
public:
        ChaiDog(double x,double y);
        void advance(int phase)override;
        void Attack();
        void Move();
        QRectF boundingRect() const override;
protected:

private:

};

class Theif:public Enemy{
     Q_OBJECT
public:
    int interval_of_atk;
        Theif(double x,double y);
        void advance(int phase)override;
        void Attack();
        void Move();
        QRectF boundingRect() const override;
protected:

private:

};

class Dragon:public Enemy{
    Q_OBJECT
public:
       Dragon(double x,double y);
       void advance(int phase)override;
       void Attack();
       void Move();
protected:

private:



};

class Bird:public Enemy{
    Q_OBJECT
public:
       Bird(double x,double y);
       void advance(int phase)override;
       void Attack();
       void Move();
protected:

private:

};

class Believer: public Enemy
{
    Q_OBJECT
public:
    int interval_of_atk;
    Believer(double x,double y);
    void advance(int phase)override;
    void Attack();
    void Move();
    QRectF boundingRect() const override;
protected:

private:
};

#endif // ENEMY_H
