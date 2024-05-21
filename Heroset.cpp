#include"Heroset.h"
#include"tools.h"
#include<QDebug>
#include"Hero.h"

Heroset::Heroset(int x0,int y0,QString path,int itemtype)
{
    hero_path=path;
    hero_type=itemtype;
    img_hero =new QImage(path);
    //qDebug()<<path;
    coolingTime=25;
    setPos(x0,y0);
}

QRectF Heroset::boundingRect() const
{
    return QRectF(0,0,128,128);
}

void Heroset::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->drawPixmap(QRect(0,1000,174,199),QPixmap(":/Heroset/HeroBack.png"));
    painter->drawImage(boundingRect(),*img_hero);
    painter->setPen(Qt::red);
    QFont font;
    font.setPointSizeF(12);
    painter->setFont(font);
    if(hero_type!=16)
    {
    int cost = getMoney(hero_type);
    painter->drawText(0,128,QString().sprintf("%3d",cost));
    }
    else
    {
        QString val="Try luck?";
        painter->drawText(0,128,val);
    }
    if (coolingTime>0){

        QBrush brush(QColor(0, 0, 0, 200));
        painter->setBrush(brush);
        painter->drawRect(QRectF(0, 0, 128, 128 * (coolingTime /25.0)));
    }
}

void Heroset::advance(int phase)
{
    if(phase==0)
    {
        if(coolingTime>0)
        {
            coolingTime--;
            ableBuyOrNot=false;
        }
        if(getMoney(hero_type)>stones)
        {
            ableBuyOrNot=false;
        }
        else ableBuyOrNot=true;
    }
    else update();

}

void Heroset::mousePressEvent(QGraphicsSceneMouseEvent *event){
   // qDebug()<<"按鼠标";
    if(coolingTime>0)
    {
        ableBuyOrNot=false;
    }
    if(getMoney(hero_type)>stones)
    {
        ableBuyOrNot=false;
    }
    if (!ableBuyOrNot){ event->ignore();return;}
    QDrag* drag = new QDrag(this);
    QMimeData* mime = new QMimeData;
    QImage image(hero_path);
    mime->setText(QString().sprintf("%d", hero_type));
    drag->setHotSpot(QPoint(35, 35));
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(image));
    drag->exec();
}
