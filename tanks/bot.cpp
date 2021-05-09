#include "bot.h"
#include "math.h"

static int randomBetween(int low, int high, int seed)
{
    qsrand(seed); // Установка базового числа для отсчёта рандома в qrand
    return (qrand() % ((high + 1) - low) + low);
}

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
        painter->fillRect(30, 30, -60, 0 - 0, QColor(255, 0, 0, 127));
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Bot::movingEngine()
{
    if (moving == false && turning == false) {
        turning = true;
        angleNew = randomBetween(0, 360, QDateTime::currentMSecsSinceEpoch());
        movingCount = randomBetween(10, 300, QDateTime::currentMSecsSinceEpoch());
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
            if(this->y() + 1 > 870){
                this->setY(869);        // снизу
            }

            emit restriction(this);
        }
    }


}
