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
    tank->setPos(100, 60);
    int size = 15;
    int posX = 0, posY = 0;
    for (int i=0; i < size; i++) {
        blocks[i] = new Block();
        scene->addItem(blocks[i]);
        posX = rand() % 13;
        posY = rand() % 13;
        blocks[i]->setPos(30 + posX * 60, 30 + posY * 60);

    }


    timer = new QTimer();
    connect(timer, &QTimer::timeout, tank, &Tank::slotGameTimer);
    timer->start(20);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, tank, &Tank::shoot);
    timer->start(2000);

    connect(tank, &Tank::explosionAdd, hit, &Hit::explosionAdd);
    connect(tank, &Tank::explosionDelete, hit, &Hit::explosionDelete);
    connect(tank, &Tank::restriction, *blocks, &Block::restriction);
}

Widget::~Widget()
{
    delete ui;
}
