#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(1200,1200);          /// Задаем размеры виджета, то есть окна
    this->setFixedSize(1200,1200);    /// Фиксируем размеры виджета

    QPixmap bg(":/images/bg.png");


    scene = new QGraphicsScene();   /// Инициализируем графическую сцену
    triangle = new Triangle();      /// Инициализируем треугольник

    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

    scene->setSceneRect(0, 0,800,800); /// Устанавливаем область графической сцены
    scene->addPixmap(bg);
    scene->addItem(triangle);   /// Добавляем на сцену треугольник
    triangle->setPos(30, 30);      /// Устанавливаем треугольник в центр сцены

    /* Инициализируем таймер и вызываем слот обработки сигнала таймера
     * у Треугольника 20 раз в секунду.
     * Управляя скоростью отсчётов, соответственно управляем скоростью
     * изменения состояния графической сцены
     * */
    timer = new QTimer();
    connect(timer, &QTimer::timeout, triangle, &Triangle::slotGameTimer);
    timer->start(1000 / 50);
}

Widget::~Widget()
{
    delete ui;
}
