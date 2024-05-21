#include"Hero.h"
#include"Enemy.h"
#include"tools.h"
#include<QImage>
#include<QMovie>
#include<cmath>

int stones;
extern QVector<Enemy*>MyEnemy;
extern QVector<Hero*>MyHero;
//extern int stones;


Hero:: Hero(double x,double y, int hp, int item_type)
    :Object(x,y,hp,item_type)
{
    is_clicked=false;
    being_ATK=0;
    this->myliving=true;
    setZValue(5);

    //qDebug()<<"Hero constructor";
}

void Hero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->drawImage(boundingRect(),walkingMoive->currentImage());
  if(being_ATK>0)
  {
      QFont font;
      font.setPointSizeF(12);
      font.setBold(true);
      QString val = "Hero Attacked! -"+QString::number(being_ATK,10);
      painter->setPen(Qt::yellow);
      painter->drawText(boundingRect(),val);
      being_ATK=0;
  }

  if(is_clicked&&IsLivingOrNot())
  {
      QFont font;
      font.setPointSizeF(12);
      font.setBold(true);
      //QString val = "Hero Attacked! -"+QString::number(being_ATK,10);
      painter->setPen(Qt::yellow);
     if(this->item_type==11||this->item_type==12)
      painter->drawRect(this->x0*100,this->y0*50+90,250,100);
    else if(this->item_type==10||this->item_type==17||this->item_type==13)
         painter->drawRect(this->x0*100+20,this->y0*50+90,115,100);

  }

  if(this->item_type==14||this->item_type==15)
  {
      if(is_atking)
      {
          if(item_type==15)
          {
              for(int m=0;m<MyEnemy.size();m++)
              {
                  if(MyEnemy[m]->Enemy_type==ENEMY_Air)
                  {
                      if(this->y0==1.2){
                      //qDebug()<<x0<<y0<<MyEnemy[m]->x0;
                      painter->drawLine(x0*100+50,y0*100+50,MyEnemy[m]->x0*100+200,MyEnemy[m]->y0*100+50);}
                      else
                          painter->drawLine(x0*100-500,y0*100,MyEnemy[m]->x0*100-200,MyEnemy[m]->y0*100);
                  }
              }
          }
          else
          {
              //qDebug()<<"enetering";
              for(int i=0;i<MyEnemy.size();i++)
              {
                  if(MyEnemy[i]->Enemy_type==ENEMY_Land)
                  {
                      if(abs(MyEnemy[i]->x0-x0)<=1&&abs(MyEnemy[i]->y0-y0)<=4&&MyEnemy[i]->IsLivingOrNot())
                      {
                           if(this->y0==1.2){
                          painter->drawLine(x0*100+50,y0*100+50,MyEnemy[i]->x0*100+100,MyEnemy[i]->y0*100);}
                           else
                               painter->drawLine(x0*100-500,y0*100,MyEnemy[i]->x0*100-200,MyEnemy[i]->y0*100);
                      }
                  }
                  else
                  {
                      if(abs(MyEnemy[i]->y0-y0)<=10&&abs(MyEnemy[i]->x0-x0)<=4&&MyEnemy[i]->IsLivingOrNot())
                      {
                           if(this->y0==14){
                         painter->drawLine(x0*100+50,y0*100+50,MyEnemy[i]->x0*100+100,MyEnemy[i]->y0*100);}
                           else
                               painter->drawLine(x0*100-500,y0*100,MyEnemy[i]->x0*100-200,MyEnemy[i]->y0*100);
                      }
                  }
              }
          }
      }

  }



}

bool Hero::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    return other->x()>x()&&other->y()==y();

}

QRectF Hero::boundingRect() const
{
    return QRectF(this->x0*100,this->y0*50-10,250,200);
}

LawSP::LawSP(double x,double y)
    :Hero(x,y,HP_LawSP,LAWSP)
{
    Hero_type=HERO_Close;
    atk_cur=ATK_LAWSP;
    atk_range=2;
    is_atking=false;
   //this->walkingMoive=new QMovie(":/LawSP/data-Idle1.gif");
    //walkingMoive->start();
   // path_1=":/LawSP/data-Idle1.gif";
   // path_2=":/LawSP/data-Die1.gif";
    SetWalkingMoive(":/LawSP/data-Idle1.gif");
    //SetDyingMoive(path_2);
}


void LawSP::advance(int phase)
{
    if(hp_cur==0)
    {
        SetWalkingMoive(":/LawSP/data-Die1.gif");
        if(IsWalkingEnd())
       {
//            for(int i=0;i<MyHero.size();i++)
//            {
//                if(MyHero[i]==this)
//                    MyHero.erase(MyHero.begin()+i);
//            }
            scene()->removeItem(this);}
    }//qDebug()<<"enter advance";
    if(phase==0) //ready to update
    {
        if(is_atking==false)
        {
            if(IsWalkingEnd())
            {
                SetWalkingMoive(":/LawSP/data-Idle1.gif");
            }
        }

       // SetWalkingMoive(":/LawSP/data-Idle1.gif");
    }
    else{
        this->QGraphicsItem::update();
        Attack();
    }

}

void LawSP::Attack()
{
    if(IsLivingOrNot())
    {
    int flag = 0;
    for(int i=0;i<MyEnemy.size();i++)
    {
        if(MyEnemy[i]->Enemy_type==ENEMY_Land)
        {
            if(abs(MyEnemy[i]->x0-x0)<=2&&MyEnemy[i]->y0==y0&&MyEnemy[i]->IsLivingOrNot())
            {
            flag++;
            is_atking=true;
            SetWalkingMoive(":/LawSP/data-S2.gif");
            qDebug()<<"洛SP开始攻击了！";
            MyEnemy[i]->GetAttacked(ATK_LAWSP);
           // MyEnemy[i]->being_atked=true;
            }
        }
    }
    if(flag==0)
    {
        is_atking=false;
        //SetWalkingMoive(":/LawSP/data-Idle1.gif");
    }

    }
}

Pang::Pang(double x,double y)
    :Hero(x,y,HP_Pang,PANG)
{
    roll=true;
    Hero_type=HERO_Close;
    atk_cur=ATK_Pang;
    atk_range=2;
    SetWalkingMoive(":/Pang/data-idle.gif");
    //walkingMoive->start();
    is_atking=false;
}


void Pang::advance(int phase)
{
    if(hp_cur==0)
    {
        SetWalkingMoive(":/Pang/data-roll.gif");
        Set_X(x0+0.3);
//        if(x0>=12)
//        {
//            for(int i=0;i<MyHero.size();i++)
//            {
//                if(MyHero[i]==this)
//                    MyHero.erase(MyHero.begin()+i);
//            }
//            //scene()->removeItem(this);
//        }
        //scene()->removeItem(this);
    }
        //qDebug()<<"enter advance";
    if(phase==0) //ready to update
    {
        if(!is_atking)
        {
            if(IsWalkingEnd())
            {
                SetWalkingMoive(":/Pang/data-idle.gif");
            }
        }
    }
    else{
        this->QGraphicsItem::update();
        Attack();
    }

}



void Pang::Attack()
{
    if(hp_cur==0&&roll==true)
    {
        roll=false;
        for(int j=0;j<MyEnemy.size();j++)
        {
            if(MyEnemy[j]->Enemy_type==ENEMY_Land)
            {
                if(MyEnemy[j]->x0>=x0&&MyEnemy[j]->y0==y0)
                {
                    qDebug()<<"庞发动了滚动，开始攻击地面敌人了！";
                    MyEnemy[j]->GetAttacked(25);
                }
            }
        }
    }


    if(IsLivingOrNot())
    {
        int flag=0;
   // qDebug()<<"lawsp Enter atk, x:"<<this->x0<<"y:"<<this->y0;
    for(int i=0;i<MyEnemy.size();i++)
    {
        if(MyEnemy[i]->Enemy_type==ENEMY_Land)
        {
            if(abs(MyEnemy[i]->x0-x0)<=2&&MyEnemy[i]->y0==y0&&MyEnemy[i]->IsLivingOrNot())
            {
                is_atking=true;
                flag++;
            qDebug()<<"庞开始攻击地面敌人了！";
            MyEnemy[i]->GetAttacked(ATK_Pang);
            }
        }
        else
        {
            if(abs(MyEnemy[i]->y0-y0)<=3&&abs(MyEnemy[i]->x0-x0)<=1&&MyEnemy[i]->IsLivingOrNot())
            {
                is_atking = true;
                flag++;
            qDebug()<<"庞开始攻击飞行敌人了！";
            MyEnemy[i]->GetAttacked(ATK_Pang);
            }
        }

    }

    if(is_atking)
    {
        SetWalkingMoive(":/Pang/data-Tr_I1_I2.gif");
    }

    if(flag==0)
    {
        is_atking=false;
    }

    }
}

QRectF Pang::boundingRect() const
{
    return QRectF(this->x0*100-10,this->y0*50+10,190,170);
}

SophieSP::SophieSP(double x,double y)
    :Hero(x,y,HP_SophieSP,SOPHIESP)
{
    Hero_type=HERO_Close;
   SetWalkingMoive(":/SophieSP/data-Idle1.gif");
}


void SophieSP::advance(int phase)
{
    if(hp_cur==0)
    {
//        for(int i=0;i<MyHero.size();i++)
//        {
//            if(MyHero[i]==this)
//                MyHero.erase(MyHero.begin()+i);
//        }
//       SetWalkingMoive(":/SophieSP/data-Sick1.gif");
//       if(IsWalkingEnd())
        scene()->removeItem(this);
    }//qDebug()<<"enter advance";
    if(phase==0) //ready to update
    {
        //SetWalkingMoive(":/SophieSP/data-Idle1.gif");
        Check();
    }
    else{
        this->QGraphicsItem::update();
    }

}

void SophieSP::Check()
{
        //分别以2/3和1/3为分界，更换动画
        if(hp_cur>(2*hp_max/3))
        {
            SetWalkingMoive(":/SophieSP/data-Idle1.gif");
            //walkingMoive->start();
        }
        else if(hp_cur<(2*hp_max/3)&&hp_cur>=(hp_max/3)){
            SetWalkingMoive(":/SophieSP/data-S1_loop.gif");
           // walkingMoive->start();
        }
        else{
            SetWalkingMoive(":/SophieSP/data-S3_loop2.gif");
           // walkingMoive->start();
        }
}

AnJie::AnJie(double x,double y)
    :Hero(x,y,HP_AnJie,ANJIE)
{
    is_atking=false;
    interval_of_stone=0;
    Hero_type=HERO_Close;
    atk_cur=ATK_AnJie;
    atk_range=0;
    SetWalkingMoive(":/AnJie/data-Idle1.gif");
   // walkingMoive->start();
}


void AnJie::advance(int phase)
{
    if(hp_cur==0)
    {
        SetWalkingMoive(":/AnJie/data-Sick1.gif");
        if(IsWalkingEnd())
       {
//            for(int i=0;i<MyHero.size();i++)
//            {
//                if(MyHero[i]==this)
//                    MyHero.erase(MyHero.begin()+i);
//            }
            scene()->removeItem(this);}
    }//qDebug()<<"enter advance";
    if(phase==0) //ready to update
    {
        if(!is_atking)
        {
            if(IsWalkingEnd())
                SetWalkingMoive(":/AnJie/data-Idle1.gif");
        }
    }
    else{
        this->QGraphicsItem::update();
        Attack();
    }

}

void AnJie::Attack()
{
    interval_of_stone++;

    if(IsLivingOrNot())
    {
        int flag = 0;
        if(interval_of_stone%40==0)
        {
            flag=1;
            is_atking=true;
            stones+=50;
           // SetWalkingMoive(":/AnJie/data-S1.gif");
        }
    if(is_atking)
    {
        SetWalkingMoive(":/AnJie/data-S1.gif");
    }

    if(flag==0)
    {
        is_atking=false;
    }

    }

}

QRectF AnJie::boundingRect() const
{
    return QRectF(this->x0*100+15,this->y0*50+10,160,170);
}

LiuSP::LiuSP(double x,double y)
    :Hero(x,y,HP_LiuSP,LIUSP)
{
    is_atking=false;
    Hero_type=HERO_Far;
    atk_cur=ATK_LiuSP;
    atk_range=0;
    SetWalkingMoive(":/LiuSP/data-Idle1.gif");
    //walkingMoive->start();
}

void LiuSP::Attack()//只攻击飞行
{
    if(IsLivingOrNot())
    {
    int flag=0;
    for(int i=0;i<MyEnemy.size();i++)
    {
        if(MyEnemy[i]->Enemy_type==ENEMY_Air)
        {
            if(MyEnemy[i]->IsLivingOrNot())
            {
                flag++;
                is_atking=true;
            qDebug()<<"琉SP开始攻击全屏的飞行敌人了！";
            MyEnemy[i]->GetAttacked(ATK_LiuSP);
            }
        }
    }
    if(is_atking==true)
    {
        SetWalkingMoive(":/LiuSP/data-S2_down.gif");
    }

    if(flag==0)
    {
        is_atking=false;
    }
    }
}

void LiuSP::advance(int phase)
{
    if(hp_cur==0)
    {
        SetWalkingMoive(":/LiuSP/data-Sick1.gif");
        if(IsWalkingEnd())
        {
//            for(int i=0;i<MyHero.size();i++)
//            {
//                if(MyHero[i]==this)
//                    MyHero.erase(MyHero.begin()+i);
//            }
            scene()->removeItem(this);
        }
    }
    if(phase==0) //ready to update
    {
        if(is_atking==false)
        {
            if(IsWalkingEnd())
                SetWalkingMoive(":/LiuSP/data-Idle1.gif");
        }
    }
    else{
        this->QGraphicsItem::update();
        Attack();
    }

}

QRectF LiuSP::boundingRect() const
{
    return QRectF(this->x0*100,this->y0*50,200,170);
}

YiMu::YiMu(double x,double y)
    :Hero(x,y,HP_YiMu,YIMU)
{
    is_atking=false;
    Hero_type=HERO_Far;
    atk_cur=ATK_YiMu;
    atk_range=0;
    SetWalkingMoive(":/YiMu/data-Idle1.gif");
    //walkingMoive->start();
}

void YiMu::Attack()
{
    if(IsLivingOrNot())
    {
        int flag=0;
    for(int i=0;i<MyEnemy.size();i++)
    {
        if(MyEnemy[i]->Enemy_type==ENEMY_Land)
        {
            if(abs(MyEnemy[i]->x0-x0)<=1&&abs(MyEnemy[i]->y0-y0)<=4&&MyEnemy[i]->IsLivingOrNot())
            {
                flag++;
                is_atking=true;
            qDebug()<<"汀朵伊姆开始攻击地面敌人了！";
            MyEnemy[i]->GetAttacked(ATK_YiMu);
            }
        }
        else
        {
            if(abs(MyEnemy[i]->y0-y0)<=10&&abs(MyEnemy[i]->x0-x0)<=4&&MyEnemy[i]->IsLivingOrNot())
            {
                flag++;
                is_atking=true;
            qDebug()<<"汀朵伊姆开始攻击飞行敌人了！";
            MyEnemy[i]->GetAttacked(ATK_YiMu);
            }
        }
    }
    if(is_atking)
    {
        SetWalkingMoive(":/YiMu/data-S1_I1.gif");
    }
    if(flag==0)
    {
        is_atking=false;
    }
    }
}

void YiMu::advance(int phase)
{
    if(hp_cur==0)
    {
        SetWalkingMoive(":/YiMu/data-Die1.gif");
        if(IsWalkingEnd())
        {
//            for(int i=0;i<MyHero.size();i++)
//            {
//                if(MyHero[i]==this)
//                    MyHero.erase(MyHero.begin()+i);
//            }
            scene()->removeItem(this);
        }
    }//qDebug()<<"enter advance";
    if(phase==0) //ready to update
    {
        if(!is_atking)
        {
            if(IsWalkingEnd())
                SetWalkingMoive(":/YiMu/data-Idle1.gif");
        }
    }
    else{
        this->QGraphicsItem::update();
        Attack();
    }

}

QRectF YiMu::boundingRect() const
{
    return QRectF(this->x0*100+15,this->y0*50+15,150,170);
}

Yaxin::Yaxin(double x,double y)
    :Hero(x,y,HP_Yaxin,YAXIN)
{
    Hero_type=HERO_Unencounter;
    atk_cur=ATK_LAWSP;
    atk_range=2;
    is_atking=false;
    SetWalkingMoive(":/Yaxin/data-Idle1.gif");
}

void Yaxin::advance(int phase)
{
    if(phase==0) //ready to update
    {
        if(is_atking==false)
        {
            if(IsWalkingEnd())
            {
                SetWalkingMoive(":/Yaxin/data-Idle1.gif");
            }
        }
    }
    else{
        this->QGraphicsItem::update();
        Attack();
    }
}

void Yaxin::Attack()
{
    if(IsLivingOrNot())
    {
    int flag = 0;
    for(int i=0;i<MyEnemy.size();i++)
    {
        if(MyEnemy[i]->Enemy_type==ENEMY_Land)
        {
            if(MyEnemy[i]->x0-x0<=2&&MyEnemy[i]->x0-x0>=-0.5&&MyEnemy[i]->y0==y0&&MyEnemy[i]->IsLivingOrNot())
            {
            flag++;
            is_atking=true;
            SetWalkingMoive(":/Yaxin/data-S3_4clones.gif");
            qDebug()<<"雅辛托斯开始攻击了！";
            MyEnemy[i]->hp_cur-=ATK_Yaxin;
            MyEnemy[i]->sharp_or_not=true;
            }
        }
    }
    if(flag==0)
    {
        is_atking=false;
    }
    }
}

QRectF Yaxin::boundingRect() const
{
    return QRectF(this->x0*100+15,this->y0*50+10,160,170);
}
