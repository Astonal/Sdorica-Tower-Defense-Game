#include"Bullet.h"
#include"Hero.h"
#include"Enemy.h"
#include"tools.h"
#include<QImage>
#include<QMovie>

extern QVector<Hero*>MyHero;
extern QVector<Enemy*>MyEnemy;

Bullet::Bullet(double x,double y,int HP,int bulltype):Object(x,y,HP,bulltype)
{
    shoot_or_not = false;
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(),walkingMoive->currentImage());

}

bool Bullet::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    return other->x()>x()&&other->y()==y();
}

QRectF Bullet::boundingRect() const
{
    return QRectF(this->x0*100,this->y0*50-10,50,50);
}

Coin::Coin(double x,double y)
    :Bullet(x,y,HP_CHAIDOG,COIN)
{
    atk_cur=ATK_PuJi;
    coin_type=getRandomBullet();
    switch (coin_type) {
    case 0:
        this->walkingMoive= new QMovie(":/small_item/gashponTicket.png");
        break;
    case 1:
        this->walkingMoive = new QMovie(":/small_item/mineralPowder.png");
        break;
    case 2:
        this->walkingMoive = new QMovie(":/small_item/coin1.png");
        break;
    default:
        this->walkingMoive = new QMovie(":/small_item/gem1.png");
        break;
    }
    walkingMoive->start();
}

void Coin::Move()
{
    Set_X(x0- 0.5);

}

void Coin::advance(int phase)
{

    if(phase==0) //ready to update
    {
        Move();
       if(is_atking)
       {
                scene()->removeItem(this);
       }
        Attack();
    }
    else{
        this->QGraphicsItem::update();

    }
}

void Coin::Attack()
{
   // int flag = 0;
    for(int i=0;i<MyHero.size();i++)
    {
        if(abs(MyHero[i]->x0-x0)<=0.6&&MyHero[i]->y0==y0&&MyHero[i]->IsLivingOrNot())
        {
            //flag++;

            is_atking=true;
            qDebug()<<"盗贼普吉开始攻击了！造成了"<<ATK_PuJi<<"点伤害！";
            MyHero[i]->GetAttacked(ATK_PuJi);
            return;
        }
    }

//    if(flag==0)
//    {
//    is_atking=false;
//    }

}

QRectF Coin::boundingRect() const
{
    return QRectF(this->x0*100,this->y0*50+30,50,50);
}

Faces::Faces(double x,double y)
    :Bullet(x,y,HP_CHAIDOG,COIN)
{
    face_interval=0;
    atk_cur=ATK_PuJi;
    this->walkingMoive = new QMovie(":/small_item/puggi_icon_R_cool.png");
    walkingMoive->start();
}


void Faces::advance(int phase)
{
    face_interval++;
    if(phase==0) //ready to update
    {
       if(face_interval>=5)
       {
           scene()->removeItem(this);
       }
    }
    else{
        this->QGraphicsItem::update();
    }
}
void Faces::Move()
{
    Set_X(x0-0.1);
}


QRectF Faces::boundingRect() const
{
    return QRectF(this->x0*100+50,this->y0*50,100,100);
}

Magic::Magic(double x,double y)
    :Bullet(x,y,HP_CHAIDOG,COIN)
{
    this->walkingMoive = new QMovie(":/Believer/EF_spray05_20.png");
    walkingMoive->start();
}

void Magic::Move()
{
    Set_X(x0- 0.5);

}

void Magic::advance(int phase)
{

    if(phase==0) //ready to update
    {
        Move();
       if(is_atking)
       {
        scene()->removeItem(this);
       }
        Attack();
    }
    else{
        this->QGraphicsItem::update();

    }
}

void Magic::Attack()
{
   // int flag = 0;
    for(int i=0;i<MyEnemy.size();i++)
    {
        if(abs(MyEnemy[i]->x0-x0)<=0.6&&MyEnemy[i]->y0==y0&&MyEnemy[i]->IsLivingOrNot())
        {
            is_atking=true;
            qDebug()<<"龙神教徒开始治愈了！造成了3点回复！";
            MyEnemy[i]->blood_or_not=true;
            MyEnemy[i]->hp_cur+=3;
            return;
        }
    }
}

QRectF Magic::boundingRect() const
{
    return QRectF(this->x0*100,this->y0*50+50,70,70);
}
