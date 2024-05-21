#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMovie>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QTimer>
#include<QDebug>
#include<QMouseEvent>
#include<QGraphicsView>
#include<QPainter>
#include<QVector>
#include"Hero.h"
#include"Enemy.h"
#include"tools.h"
#include<QPushButton>
#include<QGraphicsProxyWidget>
#include<QLabel>
#include"Map.h"
#include<QMessageBox>
//100*50

QVector<QVector<int*>>MyMap;
QVector<Enemy*>MyEnemy;
QVector<Hero*>MyHero;

int interval_enemy=0;//创建敌人的间隙
int level = 3;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this-> timer=new QTimer;
    timer->start(150);
    this->shop=new Shop;
    this->resize(2000,1000);
    this->mapblock = new MapBlock;

    this->scene=new QGraphicsScene(0,0,1478,1167,this);
    this->view=new QGraphicsView(scene,this);
    this->setFixedSize(1478,1265);
    view->resize(1480,1169);
    view->setBackgroundBrush(QPixmap(":/bg/bg-start_00.png"));
    scene->addItem(shop);
    scene->addItem(mapblock);
    shop->CreateSet();
    mapblock->setshop(shop);

    //有关速度
    game_state=true;
    cross_enemy=0;
    ui->Button1->setText("暂停");
    ui->Button1->show();

    ui->Button2->setText("加速");
    ui->Button2->show();

    //初始的英雄
    LawSP* law= new LawSP(9,5);
    MyHero.push_back(law);
    scene->addItem(law);
    Pang* pang= new Pang(9,10.5);
    MyHero.push_back(pang);
    scene->addItem(pang);
    AnJie* anjie1 = new AnJie(2.8,3);
    AnJie* anjie2 = new AnJie(2.8,5);
    AnJie* anjie3 = new AnJie(2.8,7);
    MyHero.push_back(anjie1);
    scene->addItem(anjie1);
    MyHero.push_back(anjie2);
    scene->addItem(anjie2);
    MyHero.push_back(anjie3);
    scene->addItem(anjie3);
    view->show();

    backsound = new QSound(":/sound/All Set!.wav");
    backsound->play();

    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    connect(timer,&QTimer::timeout,scene,&QGraphicsScene::advance);
    //connect(timer,&QTimer::timeout,this,&MainWindow::Check_level);
    connect(timer,&QTimer::timeout,this,&MainWindow::Create_enemy);
    connect(timer,&QTimer::timeout,this,&MainWindow::Check_game);

    ui->Button1->setCheckable(true);
    ui->Button2->setCheckable(true);
    connect(ui->Button1,&QPushButton::clicked,this,[&](){
        if(game_state)
        {
        if(ui->Button1->isChecked())
        {
            timer->stop();
            backsound->stop();
        }
        else{
            timer->start(150);
            backsound->play();
        }
        }
    });

    connect(ui->Button2,&QPushButton::clicked,this,[&](){
        if(game_state)
        {
        if(ui->Button2->isChecked())
        {
            timer->start(75);
        }
        else{
            timer->start(150);
        }
        }
    });

    //ui->label3->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Check_game()//看是否结束
{
    QString val="※小试牛刀 ratio：1  cross nums："+QString::number(cross_enemy);
    QString val2="※在劫难逃 ratio：2  cross nums："+QString::number(cross_enemy);
    QString val3="※摇摇欲坠 ratio：3  cross nums："+QString::number(cross_enemy);

    if(interval_enemy<=150)
    ui->label2->setText(val);
    else if(interval_enemy<=300)
    {
        level=2;
        ui->label2->setText(val2);
    }
        else {level=3;ui->label2->setText(val3);}

    for(int g=0;g<MyEnemy.size();g++)
    {
        if(MyEnemy[g]->x0<=2&&!MyEnemy[g]->cross_or_not)
        {
            MyEnemy[g]->cross_or_not=true;
            cross_enemy++;
            if(interval_enemy<=400)
            ui->label2->setText(val);
            else if(interval_enemy<=800)
            {
                level=2;
                ui->label2->setText(val2);
            }
                else {level=3;ui->label2->setText(val3);}
        }
    }
    if(cross_enemy==10)
    {
        game_state=false;
        timer->stop();
        QMessageBox::information(this,"游戏结束","敢杀东方联邦的马？");
        backsound->stop();
    }


}

void MainWindow::mousePressEvent(QMouseEvent *ev)//显示信息
{
    //qDebug()<<ev->x()<<" "<<ev->y();
    int x1=ev->x();
    int y1=ev->y();
    double map_x;
    double map_y;

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

    for(int p=0;p<MyHero.size();p++)
        MyHero[p]->is_clicked=false;

    for(int g=0;g<MyHero.size();g++)
    {
        if(MyHero[g]->x0==map_x&&MyHero[g]->y0==map_y)
        {
            MyHero[g]->is_clicked=true;
            QString type;
            QString name;
                    switch (MyHero[g]->item_type) {
                    case(11):
                        name = "洛SP";
                        type="近战英雄(带普通攻击）";
                        break;
                    case(12):
                        name = "庞";
                        type = "近战英雄（带普通攻击与死亡一击）";
                        break;
                    case(10):
                        name="安洁莉亚";
                        type="近战英雄（无攻击）";
                        break;
                    case(14):
                        name="汀朵伊姆";
                        type="远程英雄";
                        break;
                    case(15):
                        name="琉SP";
                        type="远程英雄";
                        break;
                    case(13):
                        name="苏菲SP";
                        type="近战英雄（无攻击）";
                        break;
                    case(17):
                        name="雅辛托斯";
                        type="近战英雄（无阻拦）";
                        break;
                    case(16):
                        name="时光书签";
                        break;
                    }
            QFont font;
            font.setPointSizeF(12);
            font.setBold(true);
            QString val1 = "    当前血量："+QString::number(MyHero[g]->hp_cur,10);
            QString val2="英雄："+name+"   英雄类型："+type+val1;
            //QString val3=val2+val1;
            ui->label->setText(val2);

        }
    }


}

void MainWindow::Create_enemy()
{
    interval_enemy++;
    if(interval_enemy%(31*level)==0)
    {
        ChaiDog * chaidog1 = new ChaiDog(13,getRandomNumber());
        MyEnemy.push_back(chaidog1);
        scene->addItem(chaidog1);
    }
    if(interval_enemy%(41*level)==0)
    {
        Theif * theif=new Theif(13,getRandomNumber());
        MyEnemy.push_back(theif);
        scene->addItem(theif);
    }
    if(interval_enemy%(51*level)==0)
    {
        Dragon * dragon = new Dragon(13,8.7);
        MyEnemy.push_back(dragon);
        scene->addItem(dragon);
    }
    if(interval_enemy%(64*level)==0)
    {
        Bird * bird = new Bird(13,8.7);
        MyEnemy.push_back(bird);
        scene->addItem(bird);
    }
    if(interval_enemy%(21*level)==0)
    {
        Believer * believer1 = new Believer(13,getRandomNumber());
        MyEnemy.push_back(believer1);
        scene->addItem(believer1);
    }

}
