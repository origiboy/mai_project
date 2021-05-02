#ifndef TANK_H
#define TANK_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>

/* Подключаем библиотеку, отвечающую за использование WinAPI
 * Данная библиотека необходима для асинхронной проверки состояния клавиш
 * */
#include <windows.h>

class Triangle : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Triangle(QObject *parent = 0);
    ~Triangle();

signals:
    void explosionAdd(QGraphicsItem *a);
    void explosionDelete(QGraphicsItem *a);

public slots:
    void slotGameTimer(); // Слот, который отвечает за обработку перемещения треугольника
    void shoot();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    boolean shootState;

public:
    qreal angle;    // Угол поворота графического объекта
    QMediaPlayer * m_player;        // Аудио плеер
    QMediaPlaylist * m_playlist;    // Плейлист
    QMediaPlayer * s_player;        // Аудио плеер
    QMediaPlaylist * s_playlist;    // Плейлист
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

#endif // TANK_H
