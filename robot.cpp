#include <QtGui>

#include "robot.h"

//! [0]
RobotPart::RobotPart(QGraphicsItem *parent)
    : QGraphicsObject(parent), color(Qt::lightGray), dragOver(false)
{
    setAcceptDrops(true);
}
//! [0]

//! [1]
void RobotPart::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasColor()) {
        event->setAccepted(true);
        dragOver = true;
        update();
    } else {
        event->setAccepted(false);
    }
}
//! [1]

//! [2]
void RobotPart::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    dragOver = false;
    update();
}
//! [2]

//! [3]
void RobotPart::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = false;
    if (event->mimeData()->hasColor())
        color = qvariant_cast<QColor>(event->mimeData()->colorData());
    update();
}
//! [3]

//! [4]
RobotHead::RobotHead(QGraphicsItem *parent)
    : RobotPart(parent)
{
}
//! [4]

//! [5]
QRectF RobotHead::boundingRect() const
{
    return QRectF(-15, -50, 30, 50);
}
//! [5]

//! [6]
void RobotHead::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (pixmap.isNull()) {
        painter->setBrush(dragOver ? color.light(130) : color);
        painter->drawRoundedRect(-10, -30, 20, 30, 25, 25, Qt::RelativeSize);
        painter->setBrush(Qt::white);
        painter->drawEllipse(-7, -3 - 20, 7, 7);
        painter->drawEllipse(0, -3 - 20, 7, 7);
        painter->setBrush(Qt::black);
        painter->drawEllipse(-5, -1 - 20, 2, 2);
        painter->drawEllipse(2, -1 - 20, 2, 2);
        painter->setPen(QPen(Qt::black, 2));
        painter->setBrush(Qt::NoBrush);
        painter->drawArc(-6, -2 - 20, 12, 15, 190 * 16, 160 * 16);
    } else {
        painter->scale(.2272, .2824);
        painter->drawPixmap(QPointF(-15 * 4.4, -50 * 3.54), pixmap);
    }
}

//! [6]

//! [7]
void RobotHead::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasImage()) {
        event->setAccepted(true);
        dragOver = true;
        update();
    } else {
        RobotPart::dragEnterEvent(event);
    }
}
//! [7]

//! [8]
void RobotHead::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasImage()) {
        dragOver = false;
        pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
        update();
    } else {
        RobotPart::dropEvent(event);
    }
}
//! [8]

RobotTorso::RobotTorso(QGraphicsItem *parent)
    : RobotPart(parent)
{
}

QRectF RobotTorso::boundingRect() const
{
    return QRectF(-30, -20, 60, 60);
}

void RobotTorso::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(dragOver ? color.light(130) : color);
    painter->drawRoundedRect(-20, -20, 40, 60, 25, 25, Qt::RelativeSize);
    painter->drawEllipse(-25, -20, 20, 20);
    painter->drawEllipse(5, -20, 20, 20);
    painter->drawEllipse(-20, 22, 20, 20);
    painter->drawEllipse(0, 22, 20, 20);
}

RobotLimb::RobotLimb(QGraphicsItem *parent)
    : RobotPart(parent)
{

}

QRectF RobotLimb::boundingRect() const
{
    return QRectF(-5, -5, 40, 10);
}

void RobotLimb::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(dragOver ? color.light(130) : color);
    painter->drawRoundedRect(boundingRect(), 50, 50, Qt::RelativeSize);
    painter->drawEllipse(-5, -5, 10, 10);
}

//! [10]
Robot::Robot(QGraphicsItem *parent)
    : RobotPart(parent)
{
    timer=0;
    setFlag(ItemHasNoContents);

    torsoItem = new RobotTorso(this);
    headItem = new RobotHead(torsoItem);
    upperLeftArmItem = new RobotLimb(torsoItem);
    lowerLeftArmItem = new RobotLimb(upperLeftArmItem);
    upperRightArmItem = new RobotLimb(torsoItem);
    lowerRightArmItem = new RobotLimb(upperRightArmItem);
    upperRightLegItem = new RobotLimb(torsoItem);
    lowerRightLegItem = new RobotLimb(upperRightLegItem);
    upperLeftLegItem = new RobotLimb(torsoItem);
    lowerLeftLegItem = new RobotLimb(upperLeftLegItem);


//! [10]

//! [11]
    headItem->setPos(0, -18);
    upperLeftArmItem->setPos(-15, -10);
    lowerLeftArmItem->setPos(30, 0);
    upperRightArmItem->setPos(15, -10);
    lowerRightArmItem->setPos(30, 0);
    upperRightLegItem->setPos(10, 32);
    lowerRightLegItem->setPos(30, 0);
    upperLeftLegItem->setPos(-10, 32);
    lowerLeftLegItem->setPos(30, 0);
}

//! [9]
QRectF Robot::boundingRect() const
{
    return QRectF();
}

void Robot::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


void Robot::actionMode(int list[4][8])
{


//! [11]
    QSequentialAnimationGroup *animationsum = new QSequentialAnimationGroup(this);

    QParallelAnimationGroup* animation[4];
    //animation[0]=new QParallelAnimationGroup(this);

    QPropertyAnimation * upperLeftArmAnimation[4];
    QPropertyAnimation * lowerLeftArmAnimation[4];
    QPropertyAnimation * upperRightArmAnimation[4];
    QPropertyAnimation * lowerRightArmAnimation[4];
    QPropertyAnimation * upperLeftLegAnimation[4];
    QPropertyAnimation * lowerLeftLegAnimation[4];
    QPropertyAnimation * upperRightLegAnimation[4];
    QPropertyAnimation * lowerRightLegAnimation[4];


    for(int j=0;j<4;j++)
    {

    animation[j]=new QParallelAnimationGroup(this);

    upperLeftArmAnimation[j] = new QPropertyAnimation(upperLeftArmItem, "rotation");


    upperLeftArmAnimation[j]->setStartValue(list[j][0]);//0 60 120 120
    upperLeftArmAnimation[j]->setEndValue(list[j][1]);
    animation[j]->addAnimation(upperLeftArmAnimation[j]);


    lowerLeftArmAnimation[j] = new QPropertyAnimation(lowerLeftArmItem, "rotation");
    lowerLeftArmAnimation[j]->setStartValue(list[j][2]);// -30 -150 100 200
    lowerLeftArmAnimation[j]->setEndValue(list[j][3]);
    animation[j]->addAnimation(lowerLeftArmAnimation[j]);



    upperRightArmAnimation[j] = new QPropertyAnimation(upperRightArmItem, "rotation");
     upperRightArmAnimation[j]->setStartValue(list[j][4]);//0 60 60 60
     upperRightArmAnimation[j]->setEndValue(list[j][5]);
    animation[j]->addAnimation(upperRightArmAnimation[j]);


    lowerRightArmAnimation[j] = new QPropertyAnimation(lowerRightArmItem, "rotation");
    lowerRightArmAnimation[j]->setStartValue(list[j][6]);//-30 -150 260 160
    lowerRightArmAnimation[j]->setEndValue(list[j][7]);
    animation[j]->addAnimation(lowerRightArmAnimation[j]);



    upperLeftLegAnimation[j] = new QPropertyAnimation(upperLeftLegItem, "rotation");
    upperLeftLegAnimation[j]->setStartValue(90);
    upperLeftLegAnimation[j]->setEndValue(90);
    animation[j]->addAnimation(upperLeftLegAnimation[j]);

    lowerLeftLegAnimation[j] = new QPropertyAnimation(lowerLeftLegItem, "rotation");
    lowerLeftLegAnimation[j]->setStartValue(0);
    lowerLeftLegAnimation[j]->setEndValue(0);
    animation[j]->addAnimation(lowerLeftLegAnimation[j]);

    upperRightLegAnimation[j] = new QPropertyAnimation(upperRightLegItem, "rotation");
    upperRightLegAnimation[j]->setStartValue(90);
    upperRightLegAnimation[j]->setEndValue(90);
    animation[j]->addAnimation(upperRightLegAnimation[j]);

    lowerRightLegAnimation[j] = new QPropertyAnimation(lowerRightLegItem, "rotation");
    lowerRightLegAnimation[j]->setStartValue(0);
    lowerRightLegAnimation[j]->setEndValue(0);
    animation[j]->addAnimation(lowerRightLegAnimation[j]);

    for (int i = 0; i < animation[j]->animationCount(); ++i) {
        QPropertyAnimation *anim = qobject_cast<QPropertyAnimation *>(animation[j]->animationAt(i));
        anim->setEasingCurve(QEasingCurve::SineCurve);
        anim->setDuration(2000);
    }

    animation[j]->setLoopCount(1);

    animationsum->addAnimation(animation[j]);
    }

//    QParallelAnimationGroup *animation1 = new QParallelAnimationGroup(this);

////! [12]

//    QPropertyAnimation *upperLeftArmAnimation1 = new QPropertyAnimation(upperLeftArmItem, "rotation");
//    upperLeftArmAnimation1->setStartValue(list[0]);//0 60 120 120
//    upperLeftArmAnimation1->setEndValue(list[1]);
//    animation1->addAnimation(upperLeftArmAnimation1);

//    QPropertyAnimation *lowerLeftArmAnimation1 = new QPropertyAnimation(lowerLeftArmItem, "rotation");
//    lowerLeftArmAnimation1->setStartValue(list[2]);// -30 -150 100 200
//    lowerLeftArmAnimation1->setEndValue(list[3]);
//    animation1->addAnimation(lowerLeftArmAnimation1);



//    QPropertyAnimation *upperRightArmAnimation1 = new QPropertyAnimation(upperRightArmItem, "rotation");
//    upperRightArmAnimation1->setStartValue(list[4]);//0 60 60 60
//    upperRightArmAnimation1->setEndValue(list[5]);
//    animation1->addAnimation(upperRightArmAnimation1);


//    QPropertyAnimation *lowerRightArmAnimation1 = new QPropertyAnimation(lowerRightArmItem, "rotation");
//    lowerRightArmAnimation1->setStartValue(list[6]);//-30 -150 260 160
//    lowerRightArmAnimation1->setEndValue(list[7]);
//    animation1->addAnimation(lowerRightArmAnimation1);



//    QPropertyAnimation *upperLeftLegAnimation1 = new QPropertyAnimation(upperLeftLegItem, "rotation");
//    upperLeftLegAnimation1->setStartValue(90);
//    upperLeftLegAnimation1->setEndValue(90);
//    animation1->addAnimation(upperLeftLegAnimation1);

//    QPropertyAnimation *lowerLeftLegAnimation1 = new QPropertyAnimation(lowerLeftLegItem, "rotation");
//    lowerLeftLegAnimation1->setStartValue(0);
//    lowerLeftLegAnimation1->setEndValue(0);
//    animation1->addAnimation(lowerLeftLegAnimation1);

//    QPropertyAnimation *upperRightLegAnimation1 = new QPropertyAnimation(upperRightLegItem, "rotation");
//    upperRightLegAnimation1->setStartValue(90);
//    upperRightLegAnimation1->setEndValue(90);
//    animation1->addAnimation(upperRightLegAnimation1);

//    QPropertyAnimation *lowerRightLegAnimation1 = new QPropertyAnimation(lowerRightLegItem, "rotation");
//    lowerRightLegAnimation1->setStartValue(0);
//    lowerRightLegAnimation1->setEndValue(0);
//    animation1->addAnimation(lowerRightLegAnimation1);

////! [13]

//    for (int i = 0; i < animation1->animationCount(); ++i) {
//        QPropertyAnimation *anim = qobject_cast<QPropertyAnimation *>(animation1->animationAt(i));
//        anim->setEasingCurve(QEasingCurve::SineCurve);
//        anim->setDuration(2000);
//    }

//    animation1->setLoopCount(1);
//    animation->start();




    animationsum->start();

//    if(timer==0)
//    timer = new QTimer(this);
//    else
//    {
//        delete timer;
//        timer = new QTimer(this);
//    }
//    connect(timer,SIGNAL(timeout()),this,SLOT(showPos()));
//    timer->start(1000);

//! [13]
}
