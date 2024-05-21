#ifndef SHOP_H
#define SHOP_H
#include"Object.h"
#include<QImage>
#include"Heroset.h"
#include"Hero.h"



class Shop: public Object
{
public:

    QImage* img;
    QList<Heroset*>herolist;

    Shop();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    void CreateSet();
    void CreateHero(int x0,int y0,int herotype);
    //void GetStones(){stones+=50;}
    void Create_LawSP(double x0,double y0);
    void Create_AnJie(double x0,double y0);
    void Create_Pang(double x0,double y0);
    void Create_LiuSP(double x0,double y0);
    void Create_YiMu(double x0,double y0);
    void Create_Sophie(double x0,double y0);
    void Create_Yaxin(double x0,double y0);

};










#endif // SHOP_H
