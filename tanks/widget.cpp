#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(900,900);
    this->setFixedSize(900,900);

    QPixmap bg(":/images/bg.png");


    scene = new QGraphicsScene();   /// Инициализируем графическую сцену
    tank = new Tank();
    hit = new Hit();


    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

    scene->setSceneRect(0, 0, 900, 900); /// Устанавливаем область графической сцены
    scene->addPixmap(bg);
    scene->addItem(tank);
    scene->addItem(hit);

    hit->setVisible(false);
    tank->setPos(0, 0);
    size = 1;
    int posX = 0, posY = 0;
    for (int i=0; i < size; i++) {
        blocks[i] = new Block();
        scene->addItem(blocks[i]);
        posX = 2;
        posY = 2;
        blocks[i]->setPos(posX * 60, posY * 60);

    }


    timer = new QTimer();
    connect(timer, &QTimer::timeout, tank, &Tank::slotGameTimer);
    timer->start(20);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, tank, &Tank::shoot);
    timer->start(2000);

    connect(tank, &Tank::explosionAdd, hit, &Hit::explosionAdd);
    connect(tank, &Tank::explosionDelete, hit, &Hit::explosionDelete);
    connect(tank, &Tank::restriction, this, &Widget::restriction);
}

void Widget::restriction(QGraphicsItem *a)
{
    int tankFrontX = a->x() + 45;
    int tankFrontY = a->y() + 45;
    int tankBackX = a->x() - 45;
    int tankBackY = a->y() - 45;
    for (int j=0; j < size; j++)
    {
        if (tankFrontX + 2 > blocks[j]->x() && tankFrontX <= blocks[j]->x() + 60 && tankFrontY >= blocks[j]->y() &&  tankBackY <= blocks[j]->y() + 60) {
             a->setX(a->x()-2);
        }
        if (tankBackX - 2 <= blocks[j]->x() + 60  && tankBackX >= blocks[j]->x() && tankFrontY >= blocks[j]->y() &&  tankBackY <= blocks[j]->y() + 60) {
             a->setX(a->x()+2);
        }
        if (tankFrontY + 2 >= blocks[j]->y() && tankFrontY <= blocks[j]->y() + 60 && tankFrontX >= blocks[j]->x() &&  tankBackX <= blocks[j]->x() + 60) {
             a->setY(a->y()-2);
        }
        if (tankBackY >= blocks[j]->y() && tankBackY - 2 <= blocks[j]->y() + 60 && tankFrontX >= blocks[j]->x() &&  tankBackX <= blocks[j]->x() + 60) {
             a->setY(a->y()+2);
        }
    }





}

Widget::~Widget()
{
    delete ui;
}
