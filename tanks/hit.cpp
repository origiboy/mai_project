#include "hit.h"

Hit::Hit(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

Hit::~Hit()
{

}

QRectF Hit::boundingRect() const
{
    return QRectF(-30,-30,60,60);
}

void Hit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::NoBrush);
        painter->drawPixmap(-30,-30,60,60,QPixmap(":/images/hit.png"));
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Hit::explosionAdd()
{
    blockTanksHit();
}

void Hit::explosionDelete()
{
    this->setVisible(false);
}


void Hit::BotexplosionAdd(QGraphicsItem *a, int index)
{
    BotBlockTanksHit(a, index);
}

