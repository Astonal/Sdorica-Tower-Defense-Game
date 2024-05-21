#include"Map.h"
#include<QtDebug>
#include<QPainter>
#include<QPixmap>


MapBlock::MapBlock()
{
   setAcceptDrops(true);

}

void MapBlock::setshop(Shop *shop)
{
    myshop=shop;
}

QRectF MapBlock::boundingRect()const
{
    return QRectF(0,0,1478,867);
}

void MapBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void MapBlock::advance(int phase)
{

}

void MapBlock::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()!=nullptr)
        event->accept();
    else
        event->ignore();
}

void MapBlock::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();
}

void MapBlock::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    const QMimeData* mdata=event->mimeData();

    int mytype = event->mimeData()->text().toInt();
    QPointF pos = mapToScene(event->pos());
    int x0=pos.x();
    int y0=pos.y();

    myshop->CreateHero(x0,y0,mytype);
}
