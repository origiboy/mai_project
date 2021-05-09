#ifndef BOT_H
#define BOT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <windows.h>

class Bot : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bot(QObject *parent = 0);
    ~Bot();

signals:


public slots:


protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

public:

};


#endif // BOT_H
