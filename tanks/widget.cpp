#include "widget.h"
#include "ui_widget.h"
#include "math.h"

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    this->resize(900,1000);
    this->setFixedSize(900,1000);
    scene = new QGraphicsScene();   /// Инициализируем графическую сцену
    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали
    QPixmap bg(":/images/bg.png");

    ui->author->setStyleSheet("background-color: #75c1ff;" "selection-color: #75c1ff;" "selection-background-color: blue;");
    ui->pushButton->setStyleSheet("background-color: #008000;" "selection-color: #008000;" "color: white;" "border-radius: 10px;");
    scene->setSceneRect(0, 0, 900, 900); /// Устанавливаем область графической сцены
    scene->addPixmap(bg);

}

void Widget::on_pushButton_clicked() {
    ui->pushButton->setDisabled(true);
    ui->pushButton->setStyleSheet("background-color: #333;" "selection-color: #333;" "color: white;" "border-radius: 10px;");
    tank = new Tank();
    hit = new Hit();
    botA = new Bot();

    scene->addItem(tank);
    scene->addItem(botA);

    botA->setPos(600, 600);
    size = ui->spinBox_2->value();
    int posX = 0, posY = 0;
    for (int i=0; i < size; i++) {
        blocks[i] = new Block();
        scene->addItem(blocks[i]);
        posX = qrand() % ((13 + 1) - 1) + 1; //qrand() % ((high + 1) - low) + low
        posY = qrand() % ((13 + 1) - 1) + 1;
        blocks[i]->setPos(posX * 60, posY * 60);

    }

    scene->addItem(hit);

    hit->setVisible(false);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, tank, &Tank::slotGameTimer);
    connect(timer, &QTimer::timeout, botA, &Bot::movingEngine);
    timer->start(10);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, tank, &Tank::shoot);
    timer->start(2000);

    connect(tank, &Tank::explosionAdd, hit, &Hit::explosionAdd);
    connect(tank, &Tank::explosionDelete, hit, &Hit::explosionDelete);
    connect(tank, &Tank::restriction, this, &Widget::restriction);
    connect(botA, &Bot::restriction, this, &Widget::restriction);
    connect(hit, &Hit::blockHit, this, &Widget::blockHit);

}

void Widget::restriction(QGraphicsItem *a)
{
    int tankFrontX = a->x() + 30;
    int tankFrontY = a->y() + 30;
    int tankBackX = a->x() - 30;
    int tankBackY = a->y() - 30;
    for (int j=0; j < size; j++)
    {
        if (tankFrontX + 1 > blocks[j]->x() && tankFrontX < blocks[j]->x() + 60 && tankFrontY > blocks[j]->y() &&  tankBackY < blocks[j]->y() + 60) {
             a->setX(a->x()-1);
        }
        if (tankBackX - 1 < blocks[j]->x() + 60  && tankBackX > blocks[j]->x() && tankFrontY > blocks[j]->y() &&  tankBackY < blocks[j]->y() + 60) {
             a->setX(a->x()+1);
        }
        if (tankFrontY + 1 > blocks[j]->y() && tankFrontY < blocks[j]->y() + 60 && tankFrontX > blocks[j]->x() &&  tankBackX < blocks[j]->x() + 60) {
             a->setY(a->y()-1);
        }
        if (tankBackY > blocks[j]->y() && tankBackY - 1 < blocks[j]->y() + 60 && tankFrontX > blocks[j]->x() &&  tankBackX < blocks[j]->x() + 60) {
             a->setY(a->y()+1);
        }
    }
}

void Widget::blockHit()
{
    int xTo = 300 * sin(tank->rotation()/180*3.14) + tank->x();
    int yTo = - 300 * cos(tank->rotation()/180*3.14) + tank->y();
    int xFrom = tank->x();
    int yFrom = tank->y();
    int x = 0;
    int y = 0;
    int distToBlockMin = 1000;
    int BlockMinIndex = 0;
    int angle = tank->rotation();
    int direction = 1;
    boolean blockWasHit = false;
    if ((angle % 360 >= 45 && angle % 360 <= 135) || (angle % 360 >= 225 && angle % 360 <= 315))
    {
        x = xFrom;
        if ((xTo - xFrom) < 0) {
            direction = -1;
        }
        while (direction * (xTo - x) >= 0) {
            y = ((x - xFrom)*(yTo - yFrom)/(xTo - xFrom)) + yFrom;
            for (int j=0; j < size; j++)
            {
                if (y >= blocks[j]->y() && y <= blocks[j]->y() + 60 && x >= blocks[j]->x() && x <= blocks[j]->x() + 60) {
                    if (sqrt((blocks[j]->x() - xFrom)*(blocks[j]->x() - xFrom) + (blocks[j]->y() - yFrom)*(blocks[j]->y() - yFrom)) < distToBlockMin) {
                        BlockMinIndex = j;
                        distToBlockMin = sqrt((blocks[j]->x() + 30 - xFrom)*(blocks[j]->x() + 30 - xFrom) + (blocks[j]->y() + 30  - yFrom)*(blocks[j]->y() + 30 - yFrom));
                    }

                    blockWasHit = true;
                }
                if (blockWasHit == true) {
                    break;
                }

            }
            x += direction * 5;

        }
    } else {
        y = yFrom;
        if ((yTo - yFrom) < 0) {
            direction = -1;
        }
        while (direction * (yTo - y) >= 0) {
            x = ((y - yFrom)*(xTo - xFrom)/(yTo - yFrom)) + xFrom;

            for (int j=0; j < size; j++)
            {
                if (y >= blocks[j]->y() && y <= blocks[j]->y() + 60 && x >= blocks[j]->x() && x <= blocks[j]->x() + 60) {
                    if (sqrt((blocks[j]->x() - xFrom)*(blocks[j]->x() - xFrom) + (blocks[j]->y() - yFrom)*(blocks[j]->y() - yFrom)) < distToBlockMin) {
                        BlockMinIndex = j;
                        distToBlockMin = sqrt((blocks[j]->x() - xFrom)*(blocks[j]->x() - xFrom) + (blocks[j]->y() - yFrom)*(blocks[j]->y() - yFrom));
                    }
                    blockWasHit = true;
                    break;
                }
                if (blockWasHit == true) {
                    break;
                }

            }
            y += direction * 5;

        }
    }

    if (blockWasHit == false) {
        hit->setX(xTo);
        hit->setY(yTo);
        hit->setVisible(true);
    } else {
        hit->setX(blocks[BlockMinIndex]->x() + 30);
        hit->setY(blocks[BlockMinIndex]->y() + 30);
        hit->setVisible(true);
        blocks[BlockMinIndex]->setPos(-900, -900);
    }

}

Widget::~Widget()
{
    delete ui;
}
