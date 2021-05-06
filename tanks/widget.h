#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>

#include <tank.h>

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
    Tank        *tank;
    Hit   *hit;
    Block   *blocks[15];
    int size;
    QTimer          *timer;

public slots:
    void restriction(QGraphicsItem *a);
};

#endif // WIDGET_H
