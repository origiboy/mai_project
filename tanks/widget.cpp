#include "widget.h"
#include "ui_widget.h"
#include "math.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    /* Инициализация фона */

    ui->setupUi(this);
    this->resize(900,700);
    this->setFixedSize(900,700);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QPixmap bg(":/images/bg.png");
    scene->setSceneRect(0, 0, 900, 600); /// Устанавливаем область графической сцены
    scene->addPixmap(bg);



    /* Кастомизация элементов */

    ui->author->setStyleSheet("background-color: #75c1ff;" "selection-color: #75c1ff;" "selection-background-color: blue;");
    ui->pushButton->setStyleSheet("background-color: #008000;" "selection-color: #008000;" "color: white;" "border-radius: 10px;");

}



void Widget::on_pushButton_clicked() {


    /* Отключение кнопки запуска */

    ui->pushButton->setDisabled(true);
    ui->pushButton->setStyleSheet("background-color: #333;" "selection-color: #333;" "color: white;" "border-radius: 10px;");

    ui->spinBox_2->setDisabled(true);
    ui->spinBox->setDisabled(true);

    ui->progressBar->setValue(100);

    /* Создание объектов пользовательский танк и выстрел */

    tank = new Tank();
    hit = new Hit();

    scene->addItem(tank);


    /* Создание объектов бот танки и выстрелы */

    int posX = 0, posY = 0;

    botsCount = ui->spinBox->value();
    botsLeft = botsCount;
    for (int i=0; i < botsCount; i++) {
        bot[i] = new Bot();
        bot[i]->index = i;
        scene->addItem(bot[i]);
        bot[i]->setPos(840, (i+1) * 2 * 60 + 30);
        hitEnemy[i] = new Hit();

    }

    /* Создание препятствий */

    size = ui->spinBox_2->value();
    for (int i=0; i < size; i++) {
        blocks[i] = new Block();
        scene->addItem(blocks[i]);
        posX = qrand() % ((11 + 1) - 1) + 1; //qrand() % ((high + 1) - low) + low
        posY = qrand() % ((8 + 1) - 1) + 1;
        blocks[i]->setPos(posX * 60, posY * 60);

    }

    scene->addItem(hit);
    hit->setVisible(false);

    for (int i=0; i < botsCount; i++) {
        scene->addItem(hitEnemy[i]);
        hitEnemy[i]->setVisible(false);

    }

    /* Создание и связка сигналов и слотов  */

    timer = new QTimer();
    connect(timer, &QTimer::timeout, tank, &Tank::tankMovingEngine);
    for (int i=0; i < botsCount; i++) {
        connect(timer, &QTimer::timeout, bot[i], &Bot::movingEngine);

    }

    timer->start(10);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, tank, &Tank::shoot); 
    for (int i=0; i < botsCount; i++) {
        connect(timer, &QTimer::timeout, bot[i], &Bot::shoot);

    }
    timer->start(2000);

    connect(tank, &Tank::explosionAdd, hit, &Hit::explosionAdd);
    connect(tank, &Tank::explosionDelete, hit, &Hit::explosionDelete);
    connect(tank, &Tank::restriction, this, &Widget::restriction); 
    for (int i=0; i < botsCount; i++) {
        connect(tank, &Tank::detectionEngine, bot[i], &Bot::detectionEngine);
        connect(bot[i], &Bot::restriction, this, &Widget::restriction);
        connect(bot[i], &Bot::BotexplosionAdd, hitEnemy[i], &Hit::BotexplosionAdd);
        connect(bot[i], &Bot::BotexplosionDelete, this, &Widget::BotexplosionDelete);
        connect(hitEnemy[i], &Hit::BotBlockTanksHit, this, &Widget::BotBlockTanksHit);
    }
    connect(hit, &Hit::blockTanksHit, this, &Widget::blockTanksHit);

    connect(this, &Widget::gameEndSignal, this, &Widget::gameEnd);

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

void Widget::blockTanksHit()
{
    int xTo = 300 * sin(tank->rotation()/180*3.14) + tank->x();
    int yTo = - 300 * cos(tank->rotation()/180*3.14) + tank->y();
    int xFrom = tank->x();
    int yFrom = tank->y();
    int x = 0;
    int y = 0;
    int distToBlockMin = 1000;
    int BlockMinIndex = 0, TankMinIndex = 0;
    int angle = tank->rotation();
    int direction = 1;
    boolean blockWasHit = false, TankWasHit = false;

    /* Определение ближайшего бота по направлению выстрела */
    if ((angle % 360 >= 45 && angle % 360 <= 135) || (angle % 360 >= 225 && angle % 360 <= 315))
    {
        x = xFrom;
        if ((xTo - xFrom) < 0) {
            direction = -1;
        }
        while (direction * (xTo - x) >= 0) {
            y = ((x - xFrom)*(yTo - yFrom)/(xTo - xFrom)) + yFrom;
            for (int j=0; j < botsCount; j++)
            {
                if (y >= bot[j]->y() - 30 && y <= bot[j]->y() + 30 && x >= bot[j]->x() - 30 && x <= bot[j]->x() + 30) {
                    if (sqrt((bot[j]->x() - xFrom)*(bot[j]->x() - xFrom) + (bot[j]->y() - yFrom)*(bot[j]->y() - yFrom)) < distToBlockMin) {
                        TankMinIndex = j;
                        distToBlockMin = sqrt((bot[j]->x() + 30 - xFrom)*(bot[j]->x() + 30 - xFrom) + (bot[j]->y() + 30  - yFrom)*(bot[j]->y() + 30 - yFrom));
                    }

                    TankWasHit = true;
                }
                if (TankWasHit == true) {
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

            for (int j=0; j < botsCount; j++)
            {
                if (y >= bot[j]->y() - 30 && y <= bot[j]->y() + 30 && x >= bot[j]->x() - 30 && x <= bot[j]->x() + 30) {
                    if (sqrt((bot[j]->x() - xFrom)*(bot[j]->x() - xFrom) + (bot[j]->y() - yFrom)*(bot[j]->y() - yFrom)) < distToBlockMin) {
                        TankMinIndex = j;
                        distToBlockMin = sqrt((bot[j]->x() - xFrom)*(bot[j]->x() - xFrom) + (bot[j]->y() - yFrom)*(bot[j]->y() - yFrom));
                    }
                    TankWasHit = true;
                    break;
                }
                if (TankWasHit == true) {
                    break;
                }

            }
            y += direction * 5;

        }
    }



    /* Определение ближайшего блока по направлению выстрела */
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
        if (TankWasHit == true) {
            hit->setX(bot[TankMinIndex]->x());
            hit->setY(bot[TankMinIndex]->y());
            hit->setVisible(true);
            float damage = 30;
            if (bot[TankMinIndex]->health - damage <= 0) {
               bot[TankMinIndex]->health = 0;
               scene->removeItem(bot[TankMinIndex]);
               scene->removeItem(hitEnemy[TankMinIndex]);
               botsLeft--;
               if (botsLeft == 0) {
                gameEndSignal(2);
               }
            } else {
                bot[TankMinIndex]->health = bot[TankMinIndex]->health - damage;
            }
        } else {
            hit->setX(xTo);
            hit->setY(yTo);
            hit->setVisible(true);
        }
    } else {
        hit->setX(blocks[BlockMinIndex]->x() + 30);
        hit->setY(blocks[BlockMinIndex]->y() + 30);
        hit->setVisible(true);
        blocks[BlockMinIndex]->setPos(-900, -900);
    }

}

void Widget::BotBlockTanksHit(QGraphicsItem *a, int index)
{
    int xTo = 300 * sin(a->rotation()/180*3.14) + a->x();
    int yTo = - 300 * cos(a->rotation()/180*3.14) + a->y();
    int xFrom = a->x();
    int yFrom = a->y();
    int x = 0;
    int y = 0;
    int distToBlockMin = 1000;
    int BlockMinIndex = 0;
    int angle = a->rotation();
    int direction = 1;
    boolean blockWasHit = false, TankWasHit = false;

    /* Определение ближайшего бота по направлению выстрела */
    if ((angle % 360 >= 45 && angle % 360 <= 135) || (angle % 360 >= 225 && angle % 360 <= 315))
    {
        x = xFrom;
        if ((xTo - xFrom) < 0) {
            direction = -1;
        }
        while (direction * (xTo - x) >= 0) {
            y = ((x - xFrom)*(yTo - yFrom)/(xTo - xFrom)) + yFrom;
                if (y >= tank->y() - 30 && y <= tank->y() + 30 && x >= tank->x() - 30 && x <= tank->x() + 30) {
                    if (sqrt((tank->x() - xFrom)*(tank->x() - xFrom) + (tank->y() - yFrom)*(tank->y() - yFrom)) < distToBlockMin) {
                        distToBlockMin = sqrt((tank->x() + 30 - xFrom)*(tank->x() + 30 - xFrom) + (tank->y() + 30  - yFrom)*(tank->y() + 30 - yFrom));
                    }

                    TankWasHit = true;
                }
                if (TankWasHit == true) {
                    break;
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

                if (y >= tank->y() - 30 && y <= tank->y() + 30 && x >= tank->x() - 30 && x <= tank->x() + 30) {
                    if (sqrt((tank->x() - xFrom)*(tank->x() - xFrom) + (tank->y() - yFrom)*(tank->y() - yFrom)) < distToBlockMin) {
                        distToBlockMin = sqrt((tank->x() - xFrom)*(tank->x() - xFrom) + (tank->y() - yFrom)*(tank->y() - yFrom));
                    }
                    TankWasHit = true;
                    break;
                }
                if (TankWasHit == true) {
                    break;
                }

            y += direction * 5;

        }
    }



    /* Определение ближайшего блока по направлению выстрела */
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
        if (TankWasHit == true) {
            hitEnemy[index]->setX(tank->x());
            hitEnemy[index]->setY(tank->y());
            hitEnemy[index]->setVisible(true);
            float damage = 20;
            if (tank->health - damage <= 0) {
               tank->health = 0;
               ui->progressBar->setValue(0);

               gameEndSignal(1);
            } else {
               tank->health = tank->health - damage;
               ui->progressBar->setValue(tank->health);
            }
        } else {
            hitEnemy[index]->setX(xTo);
            hitEnemy[index]->setY(yTo);
            hitEnemy[index]->setVisible(true);
        }
    } else {
        hitEnemy[index]->setX(blocks[BlockMinIndex]->x() + 30);
        hitEnemy[index]->setY(blocks[BlockMinIndex]->y() + 30);
        hitEnemy[index]->setVisible(true);
        blocks[BlockMinIndex]->setPos(-900, -900);
    }

}

void Widget::gameEnd(int a) {

    timer->stop();
    delete timer;
    disconnect(timer, &QTimer::timeout, tank, &Tank::tankMovingEngine);
    for (int i=0; i < botsCount; i++) {
        disconnect(timer, &QTimer::timeout, bot[i], &Bot::movingEngine);
    }
    disconnect(timer, &QTimer::timeout, tank, &Tank::shoot);
    for (int i=0; i < botsCount; i++) {
        disconnect(timer, &QTimer::timeout, bot[i], &Bot::shoot);
    }

    disconnect(tank, &Tank::explosionAdd, hit, &Hit::explosionAdd);
    disconnect(tank, &Tank::explosionDelete, hit, &Hit::explosionDelete);
    disconnect(tank, &Tank::restriction, this, &Widget::restriction);
    for (int i=0; i < botsCount; i++) {
        disconnect(tank, &Tank::detectionEngine, bot[i], &Bot::detectionEngine);
        disconnect(bot[i], &Bot::restriction, this, &Widget::restriction);
        disconnect(bot[i], &Bot::BotexplosionAdd, hitEnemy[i], &Hit::BotexplosionAdd);
        disconnect(bot[i], &Bot::BotexplosionDelete, this, &Widget::BotexplosionDelete);
        disconnect(hitEnemy[i], &Hit::BotBlockTanksHit, this, &Widget::BotBlockTanksHit);
    }
    disconnect(hit, &Hit::blockTanksHit, this, &Widget::blockTanksHit);
    disconnect(this, &Widget::gameEndSignal, this, &Widget::gameEnd);

    for (int j=0; j < botsCount; j++)
    {
        scene->removeItem(bot[j]);
        scene->removeItem(hitEnemy[j]);
        delete bot[j];
        delete hitEnemy[j];
    }
    scene->removeItem(tank);
    scene->removeItem(hit);
    delete tank;
    delete hit;

    for (int j=0; j < size; j++)
    {
        scene->removeItem(blocks[j]);
        delete blocks[j];
    }
    if (a == 1) {
        QMessageBox::warning(this,
        "Game Over",
        "Вас убили(");
    }
    if (a == 2) {
        QMessageBox::warning(this,
        "Game Over",
        "Вы выиграли!");
    }



    ui->pushButton->setDisabled(false);
    ui->pushButton->setStyleSheet("background-color: #008000;" "selection-color: #008000;" "color: white;" "border-radius: 10px;");

    ui->spinBox_2->setDisabled(false);
    ui->spinBox->setDisabled(false);
}

void Widget::BotexplosionDelete(int index) {
    hitEnemy[index]->setVisible(false);
}



Widget::~Widget()
{
    delete ui;
}
