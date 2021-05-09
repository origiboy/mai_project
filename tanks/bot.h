#ifndef BOT_H
#define BOT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDateTime>

#include <windows.h>

class Bot : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bot(QObject *parent = 0);
    ~Bot();

signals:
    void restriction(QGraphicsItem *a);

public slots:
    void movingEngine();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle;
    qreal angleNew;
    boolean moveNext = false;
    boolean turning = false;
    boolean moving = false;
    int movingCount = 0;
    QMediaPlayer * m_player, * s_player;
    QMediaPlaylist * m_playlist, * s_playlist;

public:

};


#endif // BOT_H
