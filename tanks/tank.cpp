#include "tank.h"
#include "math.h"

Tank::Tank(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    shootState = false;
    angle = 90;     // Задаём угол поворота графического объекта
    setRotation(angle);     // Устанавилваем угол поворота графического объекта
    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);
    m_playlist->addMedia(QUrl("qrc:/sounds/moving.mp3"));
    s_player = new QMediaPlayer(this);
    s_playlist = new QMediaPlaylist(s_player);
    s_player->setPlaylist(s_playlist);
    s_playlist->addMedia(QUrl("qrc:/sounds/shoot.mp3"));
}

Tank::~Tank()
{

}

QRectF Tank::boundingRect() const
{
    return QRectF(-30,-30,60,60);
}

void Tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    if (moveNext) {
        moveNext = false;
        painter->drawPixmap(-30,-30,60,60,QPixmap(":/images/tank.png"));
    } else {
        moveNext = true;
        painter->drawPixmap(-30,-30,60,60,QPixmap(":/images/tank-moved.png"));
    }
        painter->setPen(QPen(Qt::green));
        painter->fillRect(30, 30, -60, 0 - 0, QColor(255, 0, 0, 127));
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Tank::slotGameTimer()
{
    detectionEngine(this);
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
        setPos(mapToParent(0, -1));
    }
    if(GetAsyncKeyState(VK_DOWN)){
        setPos(mapToParent(0, 1));


    }

    if(this->x() - 1 < 30){
        this->setX(31);
    }
    if(this->x() + 1 > 870){
        this->setX(869);
    }

    if(this->y() - 1 < 30){
        this->setY(31);
    }
    if(this->y() + 1 > 570){
        this->setY(569);
    }

    emit restriction(this);

}

void Tank::shoot()
{
    if(GetAsyncKeyState(VK_SPACE)){
        s_player->play();
        emit explosionAdd();
    } else {
        emit explosionDelete();
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
    return QRectF(-30,-30,60,60);
}

void Hit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::NoBrush);
        painter->drawPixmap(-30,-30,60,60,QPixmap(":/images/hit.png"));
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Hit::explosionAdd()
{
    blockTanksHit();
}

void Hit::BotexplosionAdd(QGraphicsItem *a, int index)
{
    BotBlockTanksHit(a, index);
}

void Hit::explosionDelete()
{
    this->setVisible(false);
}




