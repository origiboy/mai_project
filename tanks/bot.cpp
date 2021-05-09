#include "bot.h"
#include "math.h"

Bot::~Bot()
{

}

Bot::Bot(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

QRectF Bot::boundingRect() const
{
    return QRectF(-30,-30,60,60);
}

void Bot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
        painter->drawPixmap(-30,-30,60,60,QPixmap(":/images/tank.png"));

        painter->setPen(QPen(Qt::green));
        painter->fillRect(30, 30, -60, 0 - 0, QColor(255, 0, 0, 127));
        Q_UNUSED(option);
        Q_UNUSED(widget);
}


