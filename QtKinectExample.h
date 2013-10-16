#ifndef VIEW_H
#define VIEW_H


#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMap>

#include "QtKinect.h"
#include "database/browser.h"
#include "guiitem.h"
#include "robot.h"

namespace Ui {
    class QtKinectExample;
}

class QtKinectExample : public QWidget
{
    Q_OBJECT

public:
    explicit QtKinectExample(QWidget *parent = 0);
    ~QtKinectExample();
    bool Inside(QGraphicsRectItem &A,QGraphicsEllipseItem &B);
    void ParameterSet(QStringList list);

    int operationstep;
    int currentplayer;
    int paranum;

    int levelfinishnum;
    int nextexpect;

    QStringList level;

    QStringList playerName;

    //QTimer timer;

private:
    Ui::QtKinectExample *ui;
    Ui::Browser *databaseui;
    Browser gamedatabrowser;


    QtKinect *m_kinect;
    QMap<XnUInt32, QGraphicsRectItem*> m_trackedHands;
    QGraphicsScene *m_scene;

    QGraphicsTextItem *m_handCoordinatesLabel;
    QGraphicsEllipseItem* m_handSquare;
    GUILoginPage LoginPage;
    GUIProfile ProfilePage;
    GUIGame GamePage;
    int currentparameter[4][8];
    int currentpara[4];


private slots:
    void setPointOnView(XnPoint3D handPoints, XnUInt32 handID);

    void kinectPushGestureDetected();
    void kinectWaveGestureDetected();

    void onSlideTiltValueChanged(int value);
    void newLEDState();
    void onBtClearPreviewClicked();

    void showGameData();

};

#endif // VIEW_H
