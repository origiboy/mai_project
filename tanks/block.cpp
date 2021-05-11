#include "block.h"

Block::Block(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

Block::~Block()
{

}

QRectF Block::boundingRect() const
{
    return QRectF(0,0,60,60);   /// Ограничиваем область, в которой лежит треугольник
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::NoBrush);
        painter->drawPixmap(0,0,60,60,QPixmap(":/images/block-wood.png"));
        Q_UNUSED(option);
        Q_UNUSED(widget);
}
