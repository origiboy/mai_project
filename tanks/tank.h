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

public slots:
    void slotGameTimer(); // Слот, который отвечает за обработку перемещения треугольника
    void shoot();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle;    // Угол поворота графического объекта
    boolean shootState;

public:
    QMediaPlayer * m_player;        // Аудио плеер
    QMediaPlaylist * m_playlist;    // Плейлист
    QMediaPlayer * s_player;        // Аудио плеер
    QMediaPlaylist * s_playlist;    // Плейлист
};

#endif // TANK_H
