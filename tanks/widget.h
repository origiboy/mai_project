#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>

#include <tank.h>
#include <bot.h>
#include <block.h>

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
    Bot   *bot[4];
    Hit   *hitEnemy[4];
    /* Блоки */
    Block   *blocks[20];

    int size, botsCount;
    QTimer          *timer;

public slots:
    void restriction(QGraphicsItem *a);
    void blockTanksHit();
    void on_pushButton_clicked();
};

#endif // WIDGET_H
