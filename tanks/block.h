#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDateTime>

#include <windows.h>


class Block : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Block(QObject *parent = 0);
    ~Block();

signals:

public slots:

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:


public:

};
#endif // BLOCK_H
