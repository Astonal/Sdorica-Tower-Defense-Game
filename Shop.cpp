#include"Shop.h"
extern QVector<Hero*>MyHero;


Shop::Shop()
{
    stones=500;
    img= new QImage(":/Heroset/Heroset.png");
    setPos(50,900);
    item_type= SHOP;
}

QRectF Shop::boundingRect() const
{
    return QRectF(0,0,1380,199);
}

void Shop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFont font;
    font.setPointSizeF(12);
    painter->drawImage(boundingRect(),*img);
    painter->setFont(font);
    painter->setPen(Qt::white);
    //painter->drawText(QRectF(50, 915, 65, 22), Qt::AlignCenter, QString::number(stones));
    //painter->drawPoint(75, 0);

    painter->drawText(55,182,QString().sprintf("%3d",stones));
}

void Shop::advance(int phase)
{
    if(phase==1)
        update();
}

void Shop::CreateSet()
{
    Heroset* h1 = new Heroset(240,930,":/small_item/anjie_Icon.png",ANJIE);
    Heroset* h2 = new Heroset(420,930,":/small_item/lawsp_icon.png",LAWSP);
    Heroset* h3 = new Heroset(590,930,":/small_item/pang_Icon.png",PANG);
    Heroset* h4 = new Heroset(770,930,":/small_item/sophie_icon.png",SOPHIESP);
    Heroset* h5 = new Heroset(945,930,":/small_item/yimu_icon.png",YIMU);
    Heroset* h6 = new Heroset(1120,930,":/small_item/liusp_icon.png",LIUSP);
    Heroset* h7 = new Heroset(70,910,":/small_item/gashponTicket1.png",FUHUN);
    Heroset* h8 = new Heroset(1290,930,":/Yaxin/h0191s5_icon.png",YAXIN);
    scene()->addItem(h1);herolist.append(h1);
    scene()->addItem(h2);herolist.append(h2);
    scene()->addItem(h3);herolist.append(h3);
    scene()->addItem(h4);herolist.append(h4);
    scene()->addItem(h5);herolist.append(h5);
    scene()->addItem(h6);herolist.append(h6);
    scene()->addItem(h7);herolist.append(h7);
    scene()->addItem(h8);herolist.append(h8);
}

void Shop::Create_LawSP(double x0,double y0)
{
    LawSP * p = new LawSP(x0,y0);
    scene()->addItem(p);
    MyHero.push_back(p);
    stones-=getMoney(LAWSP);
}

void Shop::Create_AnJie(double x0,double y0)
{
    AnJie * p = new AnJie(x0,y0);
    scene()->addItem(p);
    MyHero.push_back(p);
    stones-=getMoney(ANJIE);
}

void Shop::Create_Pang(double x0,double y0)
{
    Pang * p = new Pang(x0,y0);
    scene()->addItem(p);
    MyHero.push_back(p);
    stones-=getMoney(PANG);
}

void Shop::Create_LiuSP(double x0,double y0)
{
    LiuSP * p = new LiuSP(x0,y0);
    scene()->addItem(p);
    MyHero.push_back(p);
    stones-=getMoney(LIUSP);
}

void Shop::Create_YiMu(double x0,double y0)
{
    YiMu * p = new YiMu(x0,y0);
    scene()->addItem(p);
    MyHero.push_back(p);
    stones-=getMoney(YIMU);
}

void Shop::Create_Sophie(double x0,double y0)
{
    SophieSP * p = new SophieSP(x0,y0);
    scene()->addItem(p);
    MyHero.push_back(p);
    stones-=getMoney(SOPHIESP);
}

void Shop::Create_Yaxin(double x0,double y0)
{
    Yaxin * p = new Yaxin(x0,y0);
    scene()->addItem(p);
    MyHero.push_back(p);
    stones-=getMoney(YAXIN);
}

void Shop::CreateHero(int x1, int y1, int herotype)
{
    if((herotype>=10&&herotype<=13)||herotype==17)
    {
        if((y1>=545&&y1<616)||(y1>=170&&y1<265)||(y1>800))
            return;

    }
    else if(herotype==14||herotype==15)
    {
        if((y1>=265&&y1<545)||(y1>=616&&y1<800))
            return;
        if(y1>=170&&y1<265)
        {
            if(x1>=900||x1<780)
                return;
        }
        else if(y1>=545&&y1<616)
        {
            if(x1>=1030||x1<900)
                return;
        }
        else{
            if(x1<650||x1>=780)
                return;
        }
    }
    else{
        herotype=getRandomHero();
    }

    double map_x=0;
    double map_y=0;

    if(x1>280&&x1<400)
        map_x=2.8;
    else if(x1>=400&&x1<530)
        map_x=4;
    else if(x1>=520&&x1<650)
        map_x=5.1;
    else if(x1>=650&&x1<780)
        map_x=6.3;
    else if(x1>=780&&x1<900)
        map_x=7.8;
    else if(x1>=900&&x1<1030)
        map_x=9;
    else if(x1>=1030&&x1<1145)
        map_x=10;
    else if(x1>=1145&&x1<1265)
        map_x=11;
    else map_x =0;

    if(y1>=170&&y1<265)
        map_y=1.2;
    else if(y1>=265&&y1<360)
        map_y=3;
    else if(y1>=360&&y1<455)
        map_y=5;
    else if(y1>=455&&y1<545)
        map_y=7;
    else if(y1>=545&&y1<616)
        map_y=8.7;
    else if(y1>=616&&y1<700)
        map_y=10.5;
    else if(y1>=700&y1<=800)
        map_y=12.3;
    else if(y1>800&&y1<=900)
        map_y=14;
    else map_y=0;

    if(map_x==0||map_y==0)
        return;

    for(int k=0;k<MyHero.size();k++)
    {
        qDebug()<<MyHero[k]->x0<<MyHero[k]->y0;
        if(MyHero[k]->x0==map_x&&MyHero[k]->y0==map_y)
        {

            return;
        }
    }

    herolist[herotype-10]->Cooling();

    switch(herotype)
    {
    case ANJIE:
       //qDebug()<<x1<<y1;
        Create_AnJie(map_x,map_y);
        break;
    case LAWSP:
        Create_LawSP(map_x,map_y);
        break;
    case PANG:
        Create_Pang(map_x,map_y);
        break;
    case SOPHIESP:
        Create_Sophie(map_x,map_y);
        break;
    case YIMU:
        Create_YiMu(map_x,map_y);
        break;
    case LIUSP:
        Create_LiuSP(map_x,map_y);
        break;
    case YAXIN:
        Create_Yaxin(map_x,map_y);
        break;
    default:
        //Create_Fuhun(map_x,map_y);
        break;

    }
    return;
}
