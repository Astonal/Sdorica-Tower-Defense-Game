#ifndef TOOLS_H
#define TOOLS_H




//const int 区
//block-size
const int LENGTH=100;
const int WIDTH=50;
//hero_type
const int HERO_Close=1;
const int HERO_Far=2;
const int HERO_Unencounter=3;
//enemy_type
const int ENEMY_Land=1;
const int ENEMY_Air=2;
//血量
//hero
const int HP_LawSP=130;
const int HP_Pang=20;
const int HP_PuJi=115;
const int HP_AnJie=10;
const int HP_LiuSP=130;
const int HP_YiMu=125;
const int HP_SophieSP=300;
const int HP_Yaxin=114514;
//enemy
const int HP_CHAIDOG=150;
const int HP_Dragon=500;
const int HP_Theif=60;
const int HP_Bird=300;
const int HP_Believer=300;
//atk
//hero
const int ATK_PuJi=2;
const int ATK_AnJie=25;
const int ATK_LAWSP =7;
const int ATK_LiuSP=1;
const int ATK_Pang=5;
const int ATK_YiMu=6;
const int ATK_SophieSP=0;
const int ATK_Yaxin=1;
//enemy
const int ATK_CHAIDOG =2;
const int ATK_Dragon=8;
const int ATK_Theif=8;
const int ATK_Bird=10;
const int ATK_Believer=1;
//speed
//const int SPEED_BAOZI=10;
//const int SPEED_Dragon=10;
//const int SPEED_Theif=10;

enum item_type
{
    NONE=0,
    LAND=1,//陆地，放置近战、敌人，飞行敌人也可在
    WOOD=2,//木板摇摇欲坠，只能放置远程
    MUD=3,//沙子，飞行敌人的区域，我方单位都不能放置的格子
    SAND=4,//地图背景，不能部署任何东西
    SHOP=5,
    //note:近战单位需要部署在路径所在的格子上。近战单位可以阻挡一定数量的敌方单位跨过自己所
    //在的格子, 也可以主动攻击自己攻击范围内的敌方单位
    //note:远程单位不能部署在路径所在的格子上, 但需要部署在路径的附近
    //hero:
    ANJIE=10,//近战, 攻击2-3格内地面单位
    LAWSP=11,//近战，在血量归零时往前滚去，每个减一定HP//extra
    PANG=12,//近战，阻挡数为0，加buff//extra
    SOPHIESP=13,//近战，能攻击飞行单位和地面单位
    YIMU=14,//远程，能攻击飞行单位和地面单位
    LIUSP=15,//近战，攻击力为0，阻拦数严格大于0//extra
    FUHUN=16,//随机生成一种符合条件的，抽卡//extra
    YAXIN=17,
    //enemy:
    BIRD=20,//飞行单位，攻击范围严格大于一格，畏战
    THIEF=21,//远程攻击，丢珠子，范围>1
    CHAIDOG=22,//近程攻击，攻击范围自己的格子
   // RABBIT=23,//加buff的地面单位
    DRAGON=24,//飞行单位，攻击范围>1，恋战
   // JIAOTU=25,//可以攻击近战单位和远程单位
    BELIEVER=25,
    COIN=30,
    POWDER=31,
    STONE=32
};

double getRandomNumber();

int getMoney(int herotype);

int getRandomHero();

int getRandomBullet();
#endif // TOOLS_H

