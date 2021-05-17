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
    void aimingEngine(QGraphicsItem *a);
    void BotexplosionAdd(QGraphicsItem *a, int index);

public slots:
    void movingEngine();
    void detectionEngine(QGraphicsItem *a);
    void shoot();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle;
    qreal angleNew;
    int movingCount = 0;

    boolean moveNext = false;
    boolean turning = false;
    boolean moving = false;


    QMediaPlayer * m_player, * s_player;
    QMediaPlaylist * m_playlist, * s_playlist;

public:
    int index = 0;
    float health = 60;
    boolean aimDetecting = false;
    boolean aimDetected = false;
};


#endif // BOT_H
