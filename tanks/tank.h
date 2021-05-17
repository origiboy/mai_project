#ifndef TANK_H
#define TANK_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <windows.h>

class Tank : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Tank(QObject *parent = 0);
    ~Tank();

signals:
    void explosionAdd();
    void explosionDelete();
    void restriction(QGraphicsItem *a);
    void detectionEngine(QGraphicsItem *a);

public slots:
    void slotGameTimer();
    void shoot();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:

    boolean shootState;

public:
    qreal angle;
    boolean moveNext = false;
    QMediaPlayer * m_player, * s_player;
    QMediaPlaylist * m_playlist, * s_playlist;
};

class Hit : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Hit(QObject *parent = 0);
    ~Hit();

signals:
    void blockTanksHit();


public slots:
    void explosionAdd();
    void explosionDelete();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:


public:

};



#endif // TANK_H
