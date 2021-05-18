#ifndef HIT_H
#define HIT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <windows.h>

class Hit : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Hit(QObject *parent = 0);
    ~Hit();

signals:
    void blockTanksHit();
    void BotBlockTanksHit(QGraphicsItem *a, int index);


public slots:
    void explosionAdd();
    void BotexplosionAdd(QGraphicsItem *a, int index);
    void explosionDelete();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:


public:

};

#endif // HIT_H
