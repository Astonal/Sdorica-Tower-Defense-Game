#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QGraphicsScene>
#include <QMainWindow>
#include<QGraphicsView>
#include"Map.h"
#include<QDebug>
#include<QMouseEvent>
#include"tools.h"
#include"Enemy.h"
#include"Hero.h"
#include"QTimer"
#include"Shop.h"
#include<QSound>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent* ev);
    void Create_enemy();
    void Check_game();
    //void Check_level();

    QSound * backsound;
    QGraphicsScene *scene;
    QGraphicsView * view;
    QTimer * timer;
    Shop* shop;
    MapBlock * mapblock;
    bool game_state;
    int cross_enemy;
private:
    Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H
