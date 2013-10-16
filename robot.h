
#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QParallelAnimationGroup;
QT_END_NAMESPACE

//! [0]
class RobotPart : public QGraphicsObject
{
public:
    RobotPart(QGraphicsItem *parent = 0);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    QColor color;
    bool dragOver;
};
//! [0]

//! [1]
class RobotHead : public RobotPart
{
public:
    RobotHead(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
    QPixmap pixmap;
};
//! [1]

//! [2]
class RobotTorso : public RobotPart
{
public:
    RobotTorso(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};
//! [2]

//! [3]
class RobotLimb : public RobotPart
{
public:
    RobotLimb(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};
//! [3]

//! [4]
class Robot : public RobotPart
{
    Q_OBJECT
public:

    QGraphicsObject *torsoItem ;
    QGraphicsObject *headItem;
    QGraphicsObject *upperLeftArmItem;
    QGraphicsObject *lowerLeftArmItem;
    QGraphicsObject *upperRightArmItem;
    QGraphicsObject *lowerRightArmItem;
    QGraphicsObject *upperRightLegItem;
    QGraphicsObject *lowerRightLegItem;
    QGraphicsObject *upperLeftLegItem;
    QGraphicsObject *lowerLeftLegItem;
    Robot(QGraphicsItem *parent = 0);
    ~Robot(){}
    QTimer *timer;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);


    void actionMode(int list[4][8]);

private slots:

    void AniStart()
    {
    }

};
//! [4]

#endif
