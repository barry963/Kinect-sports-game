#include "QtKinectExample.h"
#include "ui_QtKinectExample.h"

#include <QtTest/QtTest>
#include <QtKinect.h>
#include <QDebug>


#define PREVIEW_X 640
#define PREVIEW_Y 480

const int actionparameter[4][8]={90,90,0,0,0,60,-30,-150,90,90,0,0,60,60,260,160,0,60,-30,-150,0,60,-30,-150,120,120,100,200,60,60,260,160};

QtKinectExample::QtKinectExample(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtKinectExample),
    m_handCoordinatesLabel(0),
    m_handSquare(0),
    operationstep(0),
    currentplayer(0),
    levelfinishnum(0)
{
    ui->setupUi(this);

    m_kinect =  new QtKinect(this);

    qRegisterMetaType< XnPoint3D >("XnPoint3D");
    qRegisterMetaType< XnUInt32>("XnUInt32");

    connect( m_kinect, SIGNAL(message(QString)), ui->outputText, SLOT(append(QString)));
    connect( m_kinect, SIGNAL(pointGenerated(XnPoint3D, XnUInt32)), this, SLOT(setPointOnView(XnPoint3D, XnUInt32)));

    connect( m_kinect, SIGNAL(pushDetected()), this, SLOT(kinectPushGestureDetected()));
    connect(m_kinect,SIGNAL(waveDetected()),this,SLOT(kinectWaveGestureDetected()));

    connect(ui->led_blinkGreen, SIGNAL(clicked()), this, SLOT(newLEDState()));
    connect(ui->led_green, SIGNAL(clicked()), this, SLOT(newLEDState()));
    connect(ui->led_red, SIGNAL(clicked()), this, SLOT(newLEDState()));
    connect(ui->led_off, SIGNAL(clicked()), this, SLOT(newLEDState()));
    connect(ui->led_yellowRed, SIGNAL(clicked()), this, SLOT(newLEDState()));
    connect(ui->led_yellow, SIGNAL(clicked()), this, SLOT(newLEDState()));

    connect (ui->slide_Tilt, SIGNAL(valueChanged(int)), this, SLOT(onSlideTiltValueChanged(int)));

    connect(ui->bt_clearPreview, SIGNAL(clicked()), this, SLOT(onBtClearPreviewClicked()));

    m_kinect->initDevice();
    m_scene = new QGraphicsScene(0, 0, PREVIEW_X, PREVIEW_Y, ui->previewScene);
    m_scene->setBackgroundBrush(QBrush(Qt::lightGray));
    ui->previewScene->setScene(m_scene);



    connect(ui->showGamedata,SIGNAL(clicked()),this,SLOT(showGameData()));
    gamedatabrowser.addConnection();

    connect(&gamedatabrowser,SIGNAL(statusMessage(QString)),ui->outputText,SLOT(append(QString)));



    onBtClearPreviewClicked();

    m_scene->clear();

    m_handSquare = new QGraphicsEllipseItem(0,0,20,20);
    m_handSquare->setBrush(Qt::white);
    m_handSquare->setZValue(256); // make sure the hand is above
    m_scene->addItem(m_handSquare);

    playerName=gamedatabrowser.exec("SELECT playerID from playerInfo");
    LoginPage.PageInit(playerName);
    LoginPage.AddPage(m_scene);

    ProfilePage.PageInit(Qt::yellow);



}

QtKinectExample::~QtKinectExample()
{
    delete m_scene;
    delete m_handCoordinatesLabel;
    delete m_handSquare;

    delete m_kinect;
    delete ui;
}

bool QtKinectExample::Inside(QGraphicsRectItem &A,QGraphicsEllipseItem &B)
{
    qreal X=A.x();
    qreal Y=A.y();
    qreal x=B.x();
    qreal y=B.y();

    return (x>=X)&&(x<=X+200)&&(y>=Y)&&(y<=Y+50);
}

void QtKinectExample::newLEDState()
{
    if( ui->led_off->isChecked())
        m_kinect->setLed(LED_OFF);

    else if(ui->led_green->isChecked())
        m_kinect->setLed(LED_GREEN);

    else if(ui->led_red->isChecked())
        m_kinect->setLed(LED_RED);

    else if(ui->led_yellow->isChecked())
        m_kinect->setLed(LED_YELLOW);

    else if(ui->led_blinkGreen->isChecked())
        m_kinect->setLed(LED_BLINK_GREEN);

    else if(ui->led_yellowRed->isChecked())
        m_kinect->setLed(LED_BLINK_RED_YELLOW);
}

void QtKinectExample::onSlideTiltValueChanged(int value)
{
    m_kinect->setTilt(value);
}

void QtKinectExample::setPointOnView(XnPoint3D handPoint, XnUInt32 handID)
{
    //adapting the point to match the scene coordinates
    QPointF adaptedPoint(handPoint.X + PREVIEW_X/2, -handPoint.Y + PREVIEW_Y/2);

        m_handSquare->setX(adaptedPoint.x());
        m_handSquare->setY(adaptedPoint.y());

    QString corrdinateStr = QString("<font color=\"#333333\">(%1, %2)</font>").arg(adaptedPoint.x()).arg(adaptedPoint.y());
    if(!m_scene->items().contains(m_handCoordinatesLabel)) {
        m_handCoordinatesLabel = new QGraphicsTextItem();
        m_scene->addItem(m_handCoordinatesLabel);
    }
    m_handCoordinatesLabel->setHtml(corrdinateStr);
    m_handCoordinatesLabel->setX(adaptedPoint.x()); // offset the text 17
    m_handCoordinatesLabel->setY(adaptedPoint.y());
    m_handCoordinatesLabel->setZValue(256); // make sure the text is above
    m_handCoordinatesLabel->setFont(QFont("Times", 9, QFont::Bold));
}

void QtKinectExample::kinectPushGestureDetected()
{
    ui->outputText->append("Push Detected");
    if((operationstep==0)&&(Inside(LoginPage.GUIPlayerlist[0],*m_handSquare)))
    {
        ui->outputText->append("Player List");
        LoginPage.AddPlayerList(m_scene);
        operationstep++;
    }
    else
        if((operationstep==1))
        {
            for(int i=1;i<playerName.size()+1;i++)
            {
                if(Inside(LoginPage.GUIPlayerlist[i],*m_handSquare))
                {
                    LoginPage.GUIPlayeroption[0].setPos(LoginPage.GUIPlayerlist[i].x()+150,LoginPage.GUIPlayerlist[i].y()-50);
                    LoginPage.GUIPlayeroption[1].setPos(LoginPage.GUIPlayerlist[i].x()+150,LoginPage.GUIPlayerlist[i].y()+50);

                    LoginPage.GUIPlayeroptionname[0].setX( LoginPage.GUIPlayeroption[0].x()+10);
                    LoginPage.GUIPlayeroptionname[0].setY( LoginPage.GUIPlayeroption[0].y()+10);

                    LoginPage.GUIPlayeroptionname[1].setX( LoginPage.GUIPlayeroption[1].x()+10);
                    LoginPage.GUIPlayeroptionname[1].setY( LoginPage.GUIPlayeroption[1].y()+10);

                    currentplayer=i;
                    ui->outputText->append(LoginPage.GUIPlayernamelist[i].toPlainText());
                    ui->outputText->append("Player  "+playerName[i-1]);

                    break;
                }
            }

            ui->outputText->append("Option List");
            LoginPage.AddOption(m_scene);
            operationstep++;
        }
    else
         if((operationstep==2))
        {
             if(Inside(LoginPage.GUIPlayeroption[0],*m_handSquare))
             {
                 LoginPage.RemoveAll(m_scene);

                 ProfilePage.AddPage(m_scene);

                 ui->outputText->append("Option Login");
                 operationstep++;
             }
             else
                 if(Inside(LoginPage.GUIPlayeroption[1],*m_handSquare))
             {
                 ui->outputText->append("Option delete");
                 gamedatabrowser.exec("DELETE from playerInfo WHERE playerID='"+playerName[currentplayer-1]+"'");
                 playerName=gamedatabrowser.exec("SELECT playerID from playerInfo");
                 LoginPage.RemovePlayerList(m_scene);
                 LoginPage.PageUpdate(playerName);
                 LoginPage.AddPlayerList(m_scene);
                 operationstep++;
             }
        }
    else
         if(operationstep==3)
         {
             //start game
             if(Inside(ProfilePage.GUIProfilelist[0],*m_handSquare))
             {
                 ProfilePage.RemoveAll(m_scene);

                level=gamedatabrowser.exec("SELECT currentLevel FROM playerInfo WHERE playerID='"+playerName[currentplayer-1]+"'");
                GamePage.PageInit(level[0]);
                GamePage.AddPage(m_scene);

                QStringList para=gamedatabrowser.exec("SELECT Parameter FROM LevelInfo WHERE LevelID='"+level[0]+"'");


                ParameterSet(para);
                GamePage.robot.actionMode(currentparameter);

                operationstep++;
             }
             else//option
                if(Inside(ProfilePage.GUIProfilelist[1],*m_handSquare))
                {
                    ProfilePage.AddOptionList(m_scene);
                }

             else
                if(Inside(ProfilePage.GUIProfileoptionlist[0],*m_handSquare))
             {
                 ui->outputText->append("Change color");
                 //ProfilePage.RemovePage(m_scene);
                 ProfilePage.ChangeColor();
                 level=gamedatabrowser.exec("SELECT currentLevel FROM playerInfo WHERE playerID='"+playerName[currentplayer-1]+"'");

                 ProfilePage.PageUpdate(level);

                 ProfilePage.AddPage(m_scene);
             }
                else
                   if(Inside(ProfilePage.GUIProfileoptionlist[2],*m_handSquare))
                {
                    ui->outputText->append("Change back");
                    ProfilePage.ChangeBack(m_scene);
                }
             else//history
                 if(Inside(ProfilePage.GUIProfilelist[2],*m_handSquare))
                 {
                     level=gamedatabrowser.exec("SELECT currentLevel FROM playerInfo WHERE playerID='"+playerName[currentplayer-1]+"'");

                     ProfilePage.PageUpdate(level);

                    ProfilePage.AddHistoryList(m_scene);
                 }

             //========
             else
                 if(Inside(ProfilePage.GUIProfilerecordlist[0],*m_handSquare))
                 {
                     QStringList para=gamedatabrowser.exec("SELECT Parameter FROM LevelInfo WHERE LevelID=1");


                     ParameterSet(para);
                     ProfilePage.robot.actionMode(currentparameter);
                 }
                 else
                     if(Inside(ProfilePage.GUIProfilerecordlist[1],*m_handSquare))
                     {
                         QStringList para=gamedatabrowser.exec("SELECT Parameter FROM LevelInfo WHERE LevelID=2");


                         ParameterSet(para);
                         ProfilePage.robot.actionMode(currentparameter);
                     }
                     else
                         if(Inside(ProfilePage.GUIProfilerecordlist[2],*m_handSquare))
                         {
                             QStringList para=gamedatabrowser.exec("SELECT Parameter FROM LevelInfo WHERE LevelID=3");


                             ParameterSet(para);
                             ProfilePage.robot.actionMode(currentparameter);
                         }
                         else
                             if(Inside(ProfilePage.GUIProfilerecordlist[3],*m_handSquare))
                             {
                                 QStringList para=gamedatabrowser.exec("SELECT Parameter FROM LevelInfo WHERE LevelID=4");


                                 ParameterSet(para);
                                 ProfilePage.robot.actionMode(currentparameter);
                             }
                             else
                                 if(Inside(ProfilePage.GUIProfilerecordlist[4],*m_handSquare))
                                 {
                                     QStringList para=gamedatabrowser.exec("SELECT Parameter FROM LevelInfo WHERE LevelID=5");


                                     ParameterSet(para);
                                     ProfilePage.robot.actionMode(currentparameter);
                                 }
                                 else
                                     if(Inside(ProfilePage.GUIProfilerecordlist[5],*m_handSquare))
                                     {
                                         QStringList para=gamedatabrowser.exec("SELECT Parameter FROM LevelInfo WHERE LevelID=6");


                                         ParameterSet(para);
                                         ProfilePage.robot.actionMode(currentparameter);
                                     }
                                     else
                                         if(Inside(ProfilePage.GUIProfilerecordlist[6],*m_handSquare))
                                         {
                                             QStringList para=gamedatabrowser.exec("SELECT Parameter FROM LevelInfo WHERE LevelID=7");


                                             ParameterSet(para);
                                             ProfilePage.robot.actionMode(currentparameter);
                                         }
                                         else
                                             if(Inside(ProfilePage.GUIProfilerecordlist[7],*m_handSquare))
                                             {
                                                 QStringList para=gamedatabrowser.exec("SELECT Parameter FROM LevelInfo WHERE LevelID=8");


                                                 ParameterSet(para);
                                                 ProfilePage.robot.actionMode(currentparameter);
                                             }
                                             else
                                                 if(Inside(ProfilePage.GUIProfilerecordlist[8],*m_handSquare))
                                                 {
                                                     QStringList para=gamedatabrowser.exec("SELECT Parameter FROM LevelInfo WHERE LevelID=9");


                                                     ParameterSet(para);
                                                     ProfilePage.robot.actionMode(currentparameter);
                                                 }
                                                 else
                                                     if(Inside(ProfilePage.GUIProfilerecordlist[9],*m_handSquare))
                                                     {
                                                         QStringList para=gamedatabrowser.exec("SELECT Parameter FROM LevelInfo WHERE LevelID=10");


                                                         ParameterSet(para);
                                                         ProfilePage.robot.actionMode(currentparameter);
                                                     }
         }
        else
             if((operationstep==4))
         {
                 if(Inside(GamePage.GUIGamelist[1],*m_handSquare))
                 {
                     GamePage.RemovePage(m_scene);
                     ProfilePage.AddPage(m_scene);

                     ui->outputText->append("Option Login");
                     operationstep--;
                 }

                 if(currentpara[levelfinishnum]%2==0)
                 {

                 if(++levelfinishnum==4)
                 {
                     levelfinishnum=0;
                 GamePage.AddInfo(m_scene);

                 bool b;
                 gamedatabrowser.exec("UPDATE playerInfo SET currentLevel='"+QString::number(level[0].toInt(&b,10)+1)+"' WHERE playerID='"+playerName[currentplayer-1]+"'");
                 level=gamedatabrowser.exec("SELECT currentLevel FROM playerInfo WHERE playerID='"+playerName[currentplayer-1]+"'");
                 GamePage.PageUpdate(level[0]);

                 QStringList para=gamedatabrowser.exec("SELECT Parameter FROM LevelInfo WHERE LevelID='"+level[0]+"'");
                 ParameterSet(para);
                 GamePage.robot.actionMode(currentparameter);
                 }

                 //GamePage.robot.actionMode(actionparameter);
                }



         }

}

void QtKinectExample::kinectWaveGestureDetected()
{
        ui->outputText->append("Wave Detected");
        if((operationstep==4))
        {

            if(currentpara[levelfinishnum]%2==1)
            {
            if(++levelfinishnum==4)
            {
                levelfinishnum=0;
            GamePage.AddInfo(m_scene);

            bool b;
            gamedatabrowser.exec("UPDATE playerInfo SET currentLevel='"+QString::number(level[0].toInt(&b,10)+1)+"' WHERE playerID='"+playerName[currentplayer-1]+"'");
            level=gamedatabrowser.exec("SELECT currentLevel FROM playerInfo WHERE playerID='"+playerName[currentplayer-1]+"'");
            GamePage.PageUpdate(level[0]);

            QStringList para=gamedatabrowser.exec("SELECT Parameter FROM LevelInfo WHERE LevelID='"+level[0]+"'");
            ParameterSet(para);
            GamePage.robot.actionMode(currentparameter);
            }
            }

        }
}

void QtKinectExample::onBtClearPreviewClicked()
{

//    option=new QGraphicsRectItem(200,200,100,50);
//    option->setBrush(Qt::yellow);
//    option->setZValue(255); // make sure the hand is above

//    m_scene->addItem(option);



//    QString name=gamedatabrowser.exec("SELECT playerID from playerInfo")[3];


//    optionLabel=new QGraphicsTextItem();
//    QString info=QString("<p>Player %1</p>").arg(name);

//    optionLabel->setHtml(info);
//    optionLabel->setX(210);
//    optionLabel->setY(210);
//    optionLabel->setZValue(256);
//    optionLabel->setFont(QFont("Times", 9, QFont::Bold));

//    m_scene->addItem(optionLabel);

//    button=new QPushButton("Player1");
//    button->setGeometry(QRect(QPoint(300, 300), QSize(100, 50)));

//    button->resize(100,50);

//    m_scene->addWidget(button);


//    connect(button,SIGNAL(clicked()),this,SLOT(kinectPushGestureDetected()));


}

void QtKinectExample::showGameData()
{
    gamedatabrowser.show();
}

void QtKinectExample::ParameterSet(QStringList list)
{
    bool b;
    for(int i=0;i<4;i++)
    {
        currentpara[i]=(list[0].left(i+1).right(1)).toInt(&b,10);
        for(int j=0;j<8;j++)
        {
            currentparameter[i][j]=actionparameter[currentpara[i]][j];
        }
    }
}
