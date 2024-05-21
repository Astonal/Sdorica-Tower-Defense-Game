#include"tools.h"
#include<QTime>

double getRandomNumber()
{
    //3, 5, 6.5 ,8, 10, 11.5

        double x=(double)(rand()/(double)RAND_MAX)*5;
        x=QString::number(x,'f',2).toDouble();
        int n1;
        double n;
        n1=(int)x;

        switch(n1)
        {
        case 0:
            n=3;
            break;
        case 1:
            n=5;
            break;
        case 2:
            n=7;
            break;
        case 3:
            n=10.5;
            break;
        case 4:
            n=12.3;
            break;
        default:
            n=7;
        }

        return n;

}

int getMoney(int herotype)
{
    {
        switch(herotype)
        {
        case 10:
            return 50;
        case 11:
            return 100;
        case 12:
            return 50;
        case 13:
            return 75;
        case 14:
            return 100;
        case 15:
            return 150;
        case 17:
            return 200;
        default:
            return 75;
        }
    }
}

int getRandomHero()
{
    //3, 5, 6.5 ,8, 10, 11.5

        double x=(double)(rand()/(double)RAND_MAX)*6;
        x=QString::number(x,'f',2).toDouble();
        int n1;
        double n;
        n1=(int)x;

        switch(n1)
        {
        case 0:
            n=10;
            break;
        case 1:
            n=11;
            break;
        case 2:
            n=12;
            break;
        case 3:
            n=13;
            break;
        case 4:
            n=14;
            break;
        case 5:
            n=15;
            break;
        default:
            n=17;
        }

        return n;

}

int getRandomBullet()
{
    //3, 5, 6.5 ,8, 10, 11.5

        double x=(double)(rand()/(double)RAND_MAX)*4;
        x=QString::number(x,'f',2).toDouble();
        int n1;
        double n;
        n1=(int)x;

        switch(n1)
        {
        case 0:
            n=0;
            break;
        case 1:
            n=1;
            break;
        case 2:
            n=2;
            break;
        case 3:
            n=3;
            break;

        default:
            n=3;
        }

        return n;

}
