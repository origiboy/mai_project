#include "tank.h"
#include "math.h"

Tank::Tank(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    shootState = false;
    angle = 90;     // Задаём угол поворота графического объекта
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

Tank::~Tank()
{

}

QRectF Tank::boundingRect() const
{
    return QRectF(-45,-45,90,90);
}

void Tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::NoBrush);

            painter->drawPixmap(-45,-45,90,90,QPixmap(":/images/tank.png"));

        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Tank::slotGameTimer()
{
    if(GetAsyncKeyState(VK_LEFT) ||
          GetAsyncKeyState(VK_RIGHT) ||
          GetAsyncKeyState(VK_UP) ||
          GetAsyncKeyState(VK_DOWN))
       {


           m_player->play();
       } else {
           m_player->stop();
       }
    if(GetAsyncKeyState(VK_LEFT)){
        angle -= 1;
        setRotation(angle);
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        angle += 1;
        setRotation(angle);
    }
    if(GetAsyncKeyState(VK_UP)){
        setPos(mapToParent(0, -2));
    }
    if(GetAsyncKeyState(VK_DOWN)){
        setPos(mapToParent(0, 2));


    }

    /* Проверка выхода за границы поля
     * Если объект выходит за заданные границы, то возвращаем его назад
     * */
    if(this->x() - 1 < 0){
        this->setX(0);       // слева
    }
    if(this->x() + 1 > 900){
        this->setX(900);        // справа
    }

    if(this->y() - 1 < 0){
        this->setY(0);       // сверху
    }
    if(this->y() + 1 > 900){
        this->setY(900);        // снизу
    }

    emit restriction(this);

}

void Tank::shoot()
{
    if(GetAsyncKeyState(VK_SPACE)){
        s_player->play();
        emit explosionAdd(this);
    } else {
        emit explosionDelete(this);
    }
}



Hit::Hit(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

Hit::~Hit()
{

}

QRectF Hit::boundingRect() const
{
    return QRectF(-30,-30,60,60);   /// Ограничиваем область, в которой лежит треугольник
}

void Hit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::NoBrush);
        painter->drawPixmap(-30,-30,60,60,QPixmap(":/images/hit.png"));
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Hit::explosionAdd(QGraphicsItem *a)
{
    //a->setY(900);
    int xTo = 300 * sin(a->rotation()/180*3.14);
    int yTo = - 300 * cos(a->rotation()/180*3.14);
    this->setX(xTo + a->x());
    this->setY(yTo + a->y());
    this->setVisible(true);
}

void Hit::explosionDelete(QGraphicsItem *a)
{
    //a->setY(900);

    this->setVisible(false);
}

Block::Block(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

Block::~Block()
{

}

QRectF Block::boundingRect() const
{
    return QRectF(0,0,60,60);   /// Ограничиваем область, в которой лежит треугольник
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::NoBrush);
        painter->drawPixmap(0,0,60,60,QPixmap(":/images/block-wood.png"));
        Q_UNUSED(option);
        Q_UNUSED(widget);
}


