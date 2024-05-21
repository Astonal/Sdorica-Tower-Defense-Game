#ifndef BULLET_H
#define BULLET_H
#include"Object.h"

class Bullet: public Object
{
    Q_OBJECT
public:
    Bullet(double x,double y,int HP,int itemtype);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    QRectF boundingRect() const override;

    bool shoot_or_not;


};

class Coin:public Bullet{
     Q_OBJECT
public:
    int coin_type;
    Coin(double x,double y);
    void advance(int phase)override;
    void Attack();
    void Move();
    QRectF boundingRect() const override;
protected:

private:

};


class Faces:public Bullet
{
    Q_OBJECT
public:
    Faces(double x,double y);
    void advance(int phase)override;
    QRectF boundingRect() const override;
    void Move();
    int face_interval;

};

class Magic:public Bullet
{
    Q_OBJECT
public:
   Magic(double x,double y);
   void advance(int phase)override;
   QRectF boundingRect() const override;
   void Move();
   void Attack();
};






#endif // BULLET_H
