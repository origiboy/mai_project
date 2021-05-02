#include "tank.h"


Triangle::Triangle(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    shootState = false;
    angle = 180;     // Задаём угол поворота графического объекта
    setRotation(angle);     // Устанавилваем угол поворота графического объекта
    m_player = new QMediaPlayer(this);          // Инициализация плеера
    m_playlist = new QMediaPlaylist(m_player);  // Инициализация плейлиста

    m_player->setPlaylist(m_playlist);          // Установка плейлиста в аудио плеер
    m_playlist->addMedia(QUrl("qrc:/sounds/moving.mp3"));       // Добавление трека в плейлист

    s_player = new QMediaPlayer(this);          // Инициализация плеера
    s_playlist = new QMediaPlaylist(s_player);  // Инициализация плейлиста

    s_player->setPlaylist(s_playlist);          // Установка плейлиста в аудио плеер
    s_playlist->addMedia(QUrl("qrc:/sounds/shoot.mp3"));       // Добавление трека в плейлист
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

        if (shootState == true) {
            painter->drawPixmap(-30,-30,60,60,QPixmap(":/images/tank-shoot.png"));
        } else {
            painter->drawPixmap(-30,-30,60,60,QPixmap(":/images/tank.png"));
        }
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Triangle::slotGameTimer()
{
    /* Поочерёдно выполняем проверку на нажатие клавиш
     * с помощью функции асинхронного получения состояния клавиш,
     * которая предоставляется WinAPI
     * */
    if(GetAsyncKeyState(VK_LEFT) ||
          GetAsyncKeyState(VK_RIGHT) ||
          GetAsyncKeyState(VK_UP) ||
          GetAsyncKeyState(VK_DOWN))
       {
          // Программный код из прошлых уроков

           m_player->play();   // Плеер играет только тогда, когда муха движется
       } else {
           m_player->stop();   // Если Муха не движется, то отключаем плее
       }
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

void Triangle::shoot()
{
    if(GetAsyncKeyState(VK_SPACE)){
        s_player->play();
        update(QRectF(-25,-40,50,80));
    } else {
        update(QRectF(-25,-40,50,80));
    }
}
