#include"Hero.h"
#include"Enemy.h"
#include"tools.h"
#include<cmath>
extern QVector<Hero*>MyHero;
extern QVector<Enemy*>MyEnemy;

Enemy::Enemy(double x,double y,int hpmax, int itemType)
    :Object(x,y,hpmax,itemType)
{
    sharp_or_not=false;
    blood_or_not=false;
    cross_or_not=false;
    being_ATK=0;
    atk_flag=false;
    this->myliving=true;
    setZValue(5);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(),walkingMoive->currentImage());
    if(being_ATK>0)
    {
        QFont font;
        font.setPointSizeF(12);
        font.setBold(true);
        QString val = "Enemy Attacked! -"+QString::number(being_ATK,10);
        painter->setPen(Qt::blue);
        painter->drawText(boundingRect(),val);

        being_ATK=0;
    }

    if(blood_or_not)
    {
        QFont font;
        font.setPointSizeF(12);
        font.setBold(true);
        QString val = "\n Healed! +3";
        painter->setPen(Qt::green);
        painter->drawText(boundingRect(),val);

        blood_or_not=false;
    }
    if(sharp_or_not)
    {
        QFont font;
        font.setPointSizeF(12);
        font.setBold(true);
        QString val = "\n\n\n pricked! -1";
        painter->setPen(Qt::red);
        painter->drawText(boundingRect(),val);

        sharp_or_not=false;
    }
}

bool Enemy::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    return other->x()>x()&&other->y()==y();
}

QRectF Enemy::boundingRect() const
{
    return QRectF(this->x0*100,this->y0*50-10,180,200);
}

ChaiDog::ChaiDog(double x,double y)
    :Enemy(x,y,HP_CHAIDOG,CHAIDOG)
{
    is_atking=false;
    Enemy_type=ENEMY_Land;
    atk_cur=ATK_CHAIDOG;
    atk_range=1;
    SetWalkingMoive(":/ChaiDog/data-Other_Run1.gif");
}

void ChaiDog::Move()
{
    if(!atk_flag)
    {
        if(this->hp_cur>=this->hp_max/2)
            Set_X(x0-0.1);
        else
            Set_X(x0-0.25);
    }
}

void ChaiDog::advance(int phase)
{
    if(hp_cur==0)
    {
        scene()->removeItem(this);
    }
    if(phase==0) //ready to update
    {
        Move();
       if(!is_atking)
       {
                if(this->hp_cur>=this->hp_max/2)
                    SetWalkingMoive(":/ChaiDog/data-Other_Run1.gif");
                else SetWalkingMoive(":/ChaiDog/data-Othe_No_Angry_Run.gif");
       }

        Attack();
    }
    else{
        //qDebug()<<being_ATK;
        this->QGraphicsItem::update();

    }
}

void ChaiDog::Attack()
{
    atk_flag=false;
    if(IsLivingOrNot())
    {
        int flag = 0;
    for(int i=0;i<MyHero.size();i++)
    {
        if(MyHero[i]->Hero_type==HERO_Close)
        {
        if(abs(MyHero[i]->x0-x0)<=2&&MyHero[i]->y0==y0&&MyHero[i]->IsLivingOrNot())
        {
            flag++;
            atk_flag=true;
            is_atking=true;
            qDebug()<<"柴犬开始攻击了！";
            MyHero[i]->GetAttacked(ATK_CHAIDOG);
        }
        }
    }
    if(is_atking==true)
    {
       if(this->hp_cur>=this->hp_max/2)
           {
                SetWalkingMoive(":/ChaiDog/data-S2.gif");
           }
       else
       {
           SetWalkingMoive(":/ChaiDog/data-Other_No_Throw.gif");
       }
    }
    if(flag==0)
    {
    is_atking=false;
    }
    }
}

QRectF ChaiDog::boundingRect() const
{
    return QRectF(this->x0*100,this->y0*50-10,160,180);
}

//小偷普吉
Theif::Theif(double x,double y)
    :Enemy(x,y,HP_Theif,THIEF)
{
    is_atking=false;
    Enemy_type=ENEMY_Land;
    atk_cur=ATK_Theif;
    atk_range=2;
    SetWalkingMoive(":/Theif/data-Run1.gif");
    //walkingMoive->start();
}

void Theif::Move()
{
    if(!atk_flag)
    {
    Set_X(x0-0.1);
    }
}

void Theif::advance(int phase)
{
    if(hp_cur==0)
       { scene()->removeItem(this);return;}
    if(hp_cur>0)
    {
    if(phase==0) //ready to update
    {
        Move();
        if(!is_atking)
        {
                SetWalkingMoive(":/Theif/data-Run1.gif");
        }
        Attack();
    }
    else{
        this->QGraphicsItem::update();
    }
    }
}

void Theif::Attack()
{
    interval_of_atk++;
    atk_flag=false;
    if(IsLivingOrNot())
    {
        int flag=0;
    for(int i=0;i<MyHero.size();i++)
    {
        if(MyHero[i]->Hero_type==HERO_Close)
        {
            if(abs(MyHero[i]->x0-x0)<=4&&MyHero[i]->y0==y0&&MyHero[i]->IsLivingOrNot())
            {
                flag++;
                is_atking=true;
            atk_flag=true;
            qDebug()<<"小偷普吉开始攻击近战英雄了！";
           // MyHero[i]->GetAttacked(ATK_Theif);
            if(interval_of_atk%5==0)
            {
            Coin * coin = new Coin(x0,y0);
            scene()->addItem(coin);
            }

            if(MyHero[i]->hp_cur<=ATK_PuJi)
            {
                Faces * face1= new Faces(x0,y0);
                scene()->addItem(face1);
            }

            }
        }
    }
    if(is_atking)
    {
        SetWalkingMoive(":/Theif/data-A2.gif");
    }
    if(flag==0)
    {
        is_atking=false;
    }
}
}

QRectF Theif::boundingRect() const
{
    return QRectF(this->x0*100,this->y0*50+10,125,150);
}

//飞龙
Dragon::Dragon(double x,double y)
    :Enemy(x,y,HP_Dragon,DRAGON)
{
    is_atking=false;
    Enemy_type=ENEMY_Air;
    atk_cur=ATK_Dragon;
    atk_range=2;
    SetWalkingMoive(":/dragon/data-Run1.gif");
    //walkingMoive->start();
}

void Dragon::Move()
{
    if(!atk_flag)
    {
    Set_X(x0-0.1);
    }
    // qDebug()<<"leave:"<<this->x0;

}

void Dragon::advance(int phase)
{
    if(hp_cur==0)
       { scene()->removeItem(this);return;}
    if(hp_cur>0)
    {
    if(phase==0) //ready to update
    {
        Move();
        if(!is_atking)
            SetWalkingMoive(":/dragon/data-Run1.gif");
        Attack();
    }
    else{
        this->QGraphicsItem::update();

    }
    }
}

void Dragon::Attack()
{
    atk_flag=false;
    if(IsLivingOrNot())
    {
        int flag=0;
    //qDebug()<<"Baozi Enter atk, x:"<<this->x0<<"y:"<<this->y0;
    for(int i=0;i<MyHero.size();i++)
    {
        if(MyHero[i]->Hero_type==HERO_Close)
        {
            if(abs(MyHero[i]->x0-x0)<=2&&abs(MyHero[i]->y0-y0)<=2&&MyHero[i]->IsLivingOrNot())
            {
            atk_flag=true;
            is_atking=true;
            flag++;
            qDebug()<<"飞龙开始攻击近战英雄了！";
            MyHero[i]->GetAttacked(ATK_Dragon);
            }
        }
        else if(MyHero[i]->Hero_type==HERO_Far)
        {
            if(abs(MyHero[i]->x0-x0)<=2&&MyHero[i]->IsLivingOrNot())
            {
            atk_flag=true;
            is_atking=true;
            flag++;
            qDebug()<<"飞龙开始攻击远程英雄了！";
            MyHero[i]->GetAttacked(ATK_Dragon);
            }
        }
    }
    if(is_atking)
        SetWalkingMoive(":/dragon/data-S1.gif");
    if(flag==0)
        is_atking=false;

    }
}

Bird::Bird(double x,double y)
    :Enemy(x,y,HP_Bird,BIRD)
{
    is_atking=false;
    Enemy_type=ENEMY_Air;
    atk_cur=ATK_Bird;
    atk_range=2;
    SetWalkingMoive(":/Bird/data-Run1.gif");
    //walkingMoive->start();
}

void Bird::Move()
{
    Set_X(x0-0.1);
}

void Bird::advance(int phase)
{
    if(hp_cur==0)
    {scene()->removeItem(this);return;}
    if(hp_cur>0)
    {
    if(phase==0) //ready to update
    {
        Move();
        if(!is_atking)
          SetWalkingMoive(":/Bird/data-Run1.gif");
        Attack();
    }
    else{
        this->QGraphicsItem::update();

    }
    }
}

void Bird::Attack()
{
    atk_flag=false;
    if(IsLivingOrNot())
    {
        int flag=0;
    //qDebug()<<"Baozi Enter atk, x:"<<this->x0<<"y:"<<this->y0;
    for(int i=0;i<MyHero.size();i++)
    {
        if(MyHero[i]->Hero_type==HERO_Close)
        {
                if(abs(MyHero[i]->y0-y0)<=2&&abs(MyHero[i]->x0-x0)<=2&&MyHero[i]->IsLivingOrNot())
                {
                atk_flag=true;
                is_atking=true;
                flag++;
                qDebug()<<"神殿鸟开始攻击近战英雄了！";
                MyHero[i]->GetAttacked(ATK_Dragon);
                }
        }
        else if(MyHero[i]->Hero_type==HERO_Far)
        {
            if(abs(MyHero[i]->x0-x0)<=2&&MyHero[i]->IsLivingOrNot())
            {
                is_atking=true;
                        flag++;
            atk_flag=true;
            qDebug()<<"神殿开始攻击远程英雄了！";
            MyHero[i]->GetAttacked(ATK_Dragon);
            }
        }
    }
    if(is_atking)
        SetWalkingMoive(":/Bird/data-S1.gif");
    if(flag==0)
        is_atking=false;
    }
}

Believer::Believer(double x,double y)
    :Enemy(x,y,HP_Believer,BELIEVER)
{
    is_atking=false;
    Enemy_type=ENEMY_Land;
    atk_cur=ATK_CHAIDOG;
    atk_range=1;
    SetWalkingMoive(":/Believer/data-Walk.gif");
    //walkingMoive->start();
}

void Believer::Move()
{
    if(!atk_flag)
    {
    Set_X(x0-0.1);
    }
}

void Believer::advance(int phase)
{
    if(hp_cur==0)
    {
        scene()->removeItem(this);
    }
    if(phase==0) //ready to update
    {
        Move();
       if(!is_atking)
       {
            SetWalkingMoive(":/Believer/data-Walk.gif");
       }
        Attack();
    }
    else{
        this->QGraphicsItem::update();
    }
}

void Believer::Attack()
{
    interval_of_atk++;
    atk_flag=false;
    if(IsLivingOrNot())
    {
        int flag = 0;
    //qDebug()<<"Baozi Enter atk, x:"<<this->x0<<"y:"<<this->y0;
    for(int i=0;i<MyEnemy.size();i++)
    {
        if(MyEnemy[i]==this) continue;
        if(MyEnemy[i]->x0-x0>=-2&&MyEnemy[i]->x0-x0<=0&&MyEnemy[i]->y0==y0&&MyEnemy[i]->IsLivingOrNot())
        {
            flag++;
            atk_flag=true;
            is_atking=true;

            if(interval_of_atk%5==0)
            {
           Magic * magi = new Magic(x0,y0);
            scene()->addItem(magi);
            }

        }
    }
    for(int i=0;i<MyHero.size();i++)
    {
        if(MyHero[i]->Hero_type==HERO_Close)
        {
        if(MyHero[i]->x0-x0<=0&&MyHero[i]->x0-x0>=-2&&MyHero[i]->y0==y0&&MyHero[i]->IsLivingOrNot())
        {
            flag++;
            atk_flag=true;
            is_atking=true;
            qDebug()<<"龙神教徒开始攻击近战英雄了！";
            MyHero[i]->GetAttacked(ATK_Believer);
        }
        }
    }

    if(is_atking==true)
    {
           SetWalkingMoive(":/Believer/data-Other_S2.gif");
    }
    if(flag==0)
    {
    is_atking=false;
    }
    }
}

QRectF Believer::boundingRect() const
{
    return QRectF(this->x0*100,this->y0*50-10,160,180);
}
