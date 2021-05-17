#include "bot.h"
#include "math.h"

Bot::~Bot()
{

}

Bot::Bot(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(m_player);

    m_player->setPlaylist(m_playlist);
    m_playlist->addMedia(QUrl("qrc:/sounds/moving.mp3"));

    s_player = new QMediaPlayer(this);
    s_playlist = new QMediaPlaylist(s_player);

    s_player->setPlaylist(s_playlist);
    s_playlist->addMedia(QUrl("qrc:/sounds/shoot.mp3"));
}

QRectF Bot::boundingRect() const
{
    return QRectF(-30,-30,60,60);
}

void Bot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    if (moveNext) {
        moveNext = false;
        painter->drawPixmap(-30,-30,60,60,QPixmap(":/images/tankEnemy.png"));
    } else {
        moveNext = true;
        painter->drawPixmap(-30,-30,60,60,QPixmap(":/images/tankEnemy-moved.png"));
    }
        painter->setPen(QPen(Qt::green));

        painter->fillRect(30, 30, -60,  -60 + this->health, QColor(255, 0, 0, 127));
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Bot::movingEngine()
{
    if (aimDetecting == false) {
        if (moving == false && turning == false) {
            turning = true;
            qsrand(QDateTime::currentMSecsSinceEpoch() * (Random + 1));
            angleNew = qrand() % ((360 + 1) - 0) + 0;
            movingCount = qrand() % ((300 + 1) - 10) + 10;
        }
        else {
            m_player->play();
            if (turning == true) {
                if (angle > angleNew) {
                    angle -= 1;
                    setRotation(angle);
                }
                if (angle < angleNew) {
                    angle += 1;
                    setRotation(angle);
                }
                if (angle == angleNew) {
                    turning = false;
                    moving = true;
                }
            }
            if (moving == true) {
                if (movingCount > 0) {
                    setPos(mapToParent(0, -1));
                    movingCount--;
                } else {
                    turning = false;
                    moving = false;
                }
                if(this->x() - 1 < 30){
                    this->setX(31);       // слева
                }
                if(this->x() + 1 > 870){
                    this->setX(869);        // справа
                }

                if(this->y() - 1 < 30){
                    this->setY(31);       // сверху
                }
                if(this->y() + 1 > 570){
                    this->setY(569);        // снизу
                }

                emit restriction(this);
            }
        }
    }


}

void Bot::detectionEngine(QGraphicsItem *a)
{
    if (sqrt((this->x() - a->x())*(this->x() - a->x()) + (this->y() - a->y())*(this->y() - a->y())) <= 300) {
        aimDetecting = true;
        int dist = sqrt((a->x() - this->x())*(a->x() - this->x()) + (a->y() - this->y())*(a->y() - this->y()));
        int angleAim = 0;
        if (a->y() - this->y() < 0) {
            angleAim = 180/3.14 * asin((a->x() - this->x())/dist);
        } else {
            angleAim = (180/3.14 * asin(-(a->x() - this->x())/dist) + 180);
        }



        if (this->rotation() > angleAim) {
            this->setRotation(this->rotation() - 1);
        }
        if (this->rotation() < angleAim) {
            this->setRotation(this->rotation() + 1);
        }
        if (this->rotation() == angleAim) {
            aimDetected = true;
        } else {
            aimDetected = false;
        }
    } else {
        aimDetecting = false;
    }
}

void Bot::shoot()
{
        if (aimDetected == true) {
            s_player->play();
        }
}
