#include "tank.h"


Triangle::Triangle(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    angle = 180;     // Задаём угол поворота графического объекта
    setRotation(angle);     // Устанавилваем угол поворота графического объекта
}

Triangle::~Triangle()
{

}

QRectF Triangle::boundingRect() const
{
    return QRectF(-25,-40,50,80);   /// Ограничиваем область, в которой лежит треугольник
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::NoBrush);
        painter->drawPixmap(-30,-30,60,60,QPixmap(":/images/tank.png"));
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Triangle::slotGameTimer()
{
    /* Поочерёдно выполняем проверку на нажатие клавиш
     * с помощью функции асинхронного получения состояния клавиш,
     * которая предоставляется WinAPI
     * */
    if(GetAsyncKeyState(VK_LEFT)){
        angle -= 1;        // Задаём поворот на 10 градусов влево
        setRotation(angle); // Поворачиваем объект
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        angle += 1;        // Задаём поворот на 10 градусов вправо
        setRotation(angle); // Поворачиваем объект
    }
    if(GetAsyncKeyState(VK_UP)){
        setPos(mapToParent(0, -2));
    }
    if(GetAsyncKeyState(VK_DOWN)){
        setPos(mapToParent(0, 2));      /* Продвигаем объект на 5 пискселей назад
                                         * перетранслировав их в координатную систему
                                         * графической сцены
                                         * */
    }

    /* Проверка выхода за границы поля
     * Если объект выходит за заданные границы, то возвращаем его назад
     * */
    if(this->x() - 1 < 0){
        this->setX(0);       // слева
    }
    if(this->x() + 1 > 800){
        this->setX(800);        // справа
    }

    if(this->y() - 1 < 0){
        this->setY(0);       // сверху
    }
    if(this->y() + 1 > 800){
        this->setY(800);        // снизу
    }
}
