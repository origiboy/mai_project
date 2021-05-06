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
    void explosionAdd(QGraphicsItem *a);
    void explosionDelete(QGraphicsItem *a);
    void restriction(QGraphicsItem *a);

public slots:
    void slotGameTimer(); // Слот, который отвечает за обработку перемещения треугольника
    void shoot();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    boolean shootState;

public:
    qreal angle;
    QMediaPlayer * m_player;
    QMediaPlaylist * m_playlist;
    QMediaPlayer * s_player;
    QMediaPlaylist * s_playlist;
};

class Hit : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Hit(QObject *parent = 0);
    ~Hit();

signals:

public slots:
    void explosionAdd(QGraphicsItem *a);
    void explosionDelete(QGraphicsItem *a);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:


public:

};

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

#endif // TANK_H
