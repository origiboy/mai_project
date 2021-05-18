#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <tank.h>
#include <bot.h>
#include <block.h>
#include <hit.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget      *ui;
    QGraphicsScene  *scene;
    /* Пользовательский танк */
    Tank        *tank;
    Hit   *hit;
    /* Боты */
    Bot   *bot[3];
    Hit   *hitEnemy[3];
    /* Блоки */
    Block   *blocks[20];

    int size, botsCount, botsLeft;
    boolean sound = false;
    QTimer          *timer;


signals:
    void gameEndSignal(int a);

public slots:
    void restriction(QGraphicsItem *a);
    void blockTanksHit();
    void BotBlockTanksHit(QGraphicsItem *a, int index);
    void on_pushButton_clicked();
    void BotexplosionDelete(int index);
    void gameEnd(int a);

};

#endif // WIDGET_H
