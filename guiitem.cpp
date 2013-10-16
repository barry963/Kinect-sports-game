#include "guiitem.h"

GUILoginPage::GUILoginPage():Title("Kinect Sports Game")
{
}

void GUILoginPage::PageInit(QStringList list)
{

    playerName=list;

    GUITitle.setHtml(Title);
    GUITitle.setX(200);
    GUITitle.setY(50);
    GUITitle.setZValue(1);
    GUITitle.setFont(QFont("Times", 20, QFont::Bold));

    GUIPlayerlist[0].setRect(0,0,100,50);
    GUIPlayerlist[0].setPos(200,200);

    GUIPlayerlist[0].setBrush(Qt::yellow);
    GUIPlayerlist[0].setZValue(255);

    for(int i=1;i<MAXPLAYERNUM+1;i++)
    {
        GUIPlayerlist[i].setRect(0,0,100,50);
        GUIPlayerlist[i].setPos(350,50+60*i);
        GUIPlayerlist[i].setBrush(Qt::yellow);
        GUIPlayerlist[i].setZValue(255);
    }


    GUIPlayernamelist[0].setHtml("<p>Account</p>");
    GUIPlayernamelist[0].setX(GUIPlayerlist[0].x()+10);
    GUIPlayernamelist[0].setY(GUIPlayerlist[0].y()+10);
    GUIPlayernamelist[0].setZValue(255);
    GUIPlayernamelist[0].setFont(QFont("Times",15, QFont::Bold));

    QString info="Player";
    for(int i=1;i<playerName.size()+1;i++)
    {

        info=QString("<p>Player %1</p>").arg(playerName[i-1]);
        GUIPlayernamelist[i].setHtml(info);

        GUIPlayernamelist[i].setX(GUIPlayerlist[i].x()+10);
        GUIPlayernamelist[i].setY(GUIPlayerlist[i].y()+10);
        GUIPlayernamelist[i].setZValue(255);
        GUIPlayernamelist[i].setFont(QFont("Times", 15, QFont::Bold));
    }


    for(int i=0;i<PLAYEROPTIONNUM;i++)
    {
        GUIPlayeroption[i].setRect(0,0,100,50);
        GUIPlayeroption[i].setPos(GUIPlayernamelist[1].x()+100,GUIPlayernamelist[1].y()-50+i*60);
        GUIPlayeroption[i].setBrush(Qt::yellow);
        GUIPlayeroption[i].setZValue(255);

        GUIPlayeroptionname[i].setX(GUIPlayeroption[i].x()+10);
        GUIPlayeroptionname[i].setY(GUIPlayeroption[i].y()+10);
        GUIPlayeroptionname[i].setZValue(255);
        GUIPlayeroptionname[i].setFont(QFont("Times", 15, QFont::Bold));
    }
    info=QString("<p>Login </p>");
    GUIPlayeroptionname[0].setHtml(info);
    info=QString("<p>Delete </p>");
    GUIPlayeroptionname[1].setHtml(info);

    qDebug()<<GUIPlayerlist[0].isActive();
}

void GUILoginPage::PageUpdate(QStringList list)
{
    playerName=list;
    QString info="Player";

    for(int i=1;i<playerName.size()+1;i++)
    {
        info=QString("<p>Player %1</p>").arg(playerName[i-1]);
        GUIPlayernamelist[i].setHtml(info);

        GUIPlayernamelist[i].setX(GUIPlayerlist[i].x()+10);
        GUIPlayernamelist[i].setY(GUIPlayerlist[i].y()+10);
        GUIPlayernamelist[i].setZValue(255);
        GUIPlayernamelist[i].setFont(QFont("Times", 15, QFont::Bold));
    }
}

void GUILoginPage::AddPage(QGraphicsScene *scene)
{
    scene->addItem(&GUITitle);
    scene->addItem(GUIPlayerlist+0);
    scene->addItem(GUIPlayernamelist+0);

}

void GUILoginPage::RemovePage(QGraphicsScene *scene)
{
    scene->removeItem(&GUITitle);
    scene->removeItem(GUIPlayerlist+0);
    scene->removeItem(GUIPlayernamelist+0);
}

void GUILoginPage::AddPlayerList(QGraphicsScene *scene)
{
    for(int i=1;i<playerName.size()+1;i++)
    {
        scene->addItem(GUIPlayerlist+i);
        scene->addItem(GUIPlayernamelist+i);
    }
}

void GUILoginPage::RemovePlayerList(QGraphicsScene *scene)
{
    for(int i=1;i<playerName.size()+1;i++)
    {
        scene->removeItem(GUIPlayerlist+i);
        scene->removeItem(GUIPlayernamelist+i);
    }
}

void GUILoginPage::AddOption(QGraphicsScene *scene)
{

        for(int i=0;i<PLAYEROPTIONNUM;i++)
        {
            scene->addItem(GUIPlayeroption+i);
            scene->addItem(GUIPlayeroptionname+i);
        }
}

void  GUILoginPage::RemoveOption(QGraphicsScene *scene)
{

        for(int i=0;i<PLAYEROPTIONNUM;i++)
        {
            scene->removeItem(GUIPlayeroption+i);
            scene->removeItem(GUIPlayeroptionname+i);
        }
}

 GUIProfile::GUIProfile()
{
    colornum=0;
}

void GUIProfile::PageInit(QBrush color)
{
    robot.setScale(2);
    robot.setPos(-100, 200);


    for(int i=0;i<PROFILELISTNUM;i++)
    {
        GUIProfilelist[i].setRect(0,0,100,50);
        GUIProfilelist[i].setPos(200,30+100*i);
        GUIProfilelist[i].setBrush(color);
        GUIProfilelist[i].setZValue(255);

        GUIProfilenamelist[i].setX(GUIProfilelist[i].x()+10);
        GUIProfilenamelist[i].setY(GUIProfilelist[i].y()+10);
        GUIProfilenamelist[i].setZValue(255);
        GUIProfilenamelist[i].setFont(QFont("Times", 13, QFont::Bold));

    }
    GUIProfilenamelist[0].setHtml("<p>Start Game</p>");
    GUIProfilenamelist[1].setHtml("<p>Option</p>");
    GUIProfilenamelist[2].setHtml("<p>History</p>");

    for(int i=0;i<PROFILEOPTIONNUM;i++)
    {
        GUIProfileoptionlist[i].setRect(0,0,100,50);
        GUIProfileoptionlist[i].setPos(350,50+50*i);
        GUIProfileoptionlist[i].setBrush(color);
        GUIProfileoptionlist[i].setZValue(255);

        GUIProfileoptionnamelist[i].setX(GUIProfileoptionlist[i].x()+10);
        GUIProfileoptionnamelist[i].setY(GUIProfileoptionlist[i].y()+10);
        GUIProfileoptionnamelist[i].setZValue(255);
        GUIProfileoptionnamelist[i].setFont(QFont("Times", 12, QFont::Bold));

    }
    GUIProfileoptionnamelist[0].setHtml("<p>Color</p>");
    GUIProfileoptionnamelist[1].setHtml("<p>Role</p>");
    GUIProfileoptionnamelist[2].setHtml("<p>Background</p>");

     QString info="Level";
    for(int i=0;i<MAXLEVEL;i++)
    {

        GUIProfilerecordlist[i].setRect(0,0,100,50);
        GUIProfilerecordlist[i].setPos(10+150*(i%(MAXLEVEL/2)),330+80*(int)(i/(MAXLEVEL/2)));
        GUIProfilerecordlist[i].setBrush(color);
        GUIProfilerecordlist[i].setZValue(255);

        info=QString("<p>Level %1</p>").arg(i+1);
        GUIProfilerecordnamelist[i].setHtml(info);

        GUIProfilerecordnamelist[i].setX(GUIProfilerecordlist[i].x()+10);
        GUIProfilerecordnamelist[i].setY(GUIProfilerecordlist[i].y()+10);
        GUIProfilerecordnamelist[i].setZValue(255);
        GUIProfilerecordnamelist[i].setFont(QFont("Times", 15, QFont::Bold));

    }
}

void GUIProfile::PageUpdate(QStringList level)
{
    bool b;
    for(int i=0;i<level[0].toInt(&b,10);i++)
    {
        GUIProfilerecordlist[i].setBrush(Qt::red);
    }
}

void GUIProfile::RemovePage(QGraphicsScene *scene)
{
    for(int i=0;i<PROFILELISTNUM;i++)
    {
        scene->removeItem(GUIProfilenamelist+i);
        scene->removeItem(GUIProfilelist+i);
    }
}

void GUIProfile::AddPage(QGraphicsScene *scene)
{
    for(int i=0;i<PROFILELISTNUM;i++)
    {
        scene->addItem(GUIProfilelist+i);
        scene->addItem(GUIProfilenamelist+i);
    }


}

void GUIProfile::AddOptionList(QGraphicsScene *scene)
{
    GUIProfileoptionlist[1].setVisible(false);
    GUIProfileoptionnamelist[1].setVisible(false);

    for(int i=0;i<PROFILEOPTIONNUM;i++)
    {
        scene->addItem(GUIProfileoptionlist+i);
        scene->addItem(GUIProfileoptionnamelist+i);
    }
}

void GUIProfile::RemoveOptionList(QGraphicsScene *scene)
{
    for(int i=0;i<PROFILEOPTIONNUM;i++)
    {
        scene->removeItem(GUIProfileoptionlist+i);
        scene->removeItem(GUIProfileoptionnamelist+i);
    }
}

void GUIProfile::AddHistoryList(QGraphicsScene *scene)
{
    for(int i=0;i<MAXLEVEL;i++)
    {
        scene->addItem(GUIProfilerecordlist+i);
        scene->addItem(GUIProfilerecordnamelist+i);
    }
    scene->addItem(&robot);


}

void GUIProfile::RemoveHistoryList(QGraphicsScene *scene)
{
    scene->removeItem(&robot);
    for(int i=0;i<MAXLEVEL;i++)
    {
        scene->removeItem(GUIProfilerecordlist+i);
        scene->removeItem(GUIProfilerecordnamelist+i);
    }
}

void GUIProfile::ChangeColor()
{
    if(++colornum==2)
        colornum=0;
    if(colornum==0)
        PageInit(Qt::yellow);
    else
        PageInit(Qt::white);


}

void GUIProfile::ChangeBack(QGraphicsScene *scene)
{
    if(++colornum==2)
        colornum=0;
    if(colornum==0)
         scene->setBackgroundBrush(QBrush(Qt::lightGray));
    else
         scene->setBackgroundBrush(QBrush(Qt::white));
}

void GUIProfile::ChangeRole(QGraphicsScene *scene)
{

}

GUIGame::GUIGame(QObject *parent)
{
    timer.setSingleShot(true);
    connect(&timer,SIGNAL(timeout()),this,SLOT(InfoChange()));
}

void GUIGame::PageInit(QString level)
{
    //robot.actionMode(0,0,0,0,0,0,0,0);
    robot.setScale(3);
    robot.setPos(0, 150);

    for(int i=0;i<2;i++)
    {
        GUIGamelist[i].setRect(0,0,100,50);
        GUIGamelist[i].setPos(400+i*200,0);
        GUIGamelist[i].setBrush(Qt::yellow);
        GUIGamelist[i].setZValue(255);

        GUIGamenamelist[i].setX(GUIGamelist[i].x()+10);
        GUIGamenamelist[i].setY(GUIGamelist[i].y()+10);
        GUIGamenamelist[i].setZValue(255);
        GUIGamenamelist[i].setFont(QFont("Times", 15, QFont::Bold));

    }
    GUIGamenamelist[0].setHtml("<p>Retry</p>");
    GUIGamenamelist[1].setHtml("<p>Back</p>");

    GUIGamelevel.setX(200);
    GUIGamelevel.setY(0);
    GUIGamelevel.setZValue(255);
    GUIGamelevel.setFont(QFont("Times", 15, QFont::Bold));
    GUIGamelevel.setHtml("<p>Level "+level+"</p>");

    GUIGameInfo.setX(200);
    GUIGameInfo.setY(100);
    GUIGameInfo.setZValue(255);
    GUIGameInfo.setFont(QFont("Times", 15, QFont::Bold));
    GUIGameInfo.setHtml("");
}

void GUIGame::PageUpdate(QString level)
{
    GUIGamelevel.setHtml("<p>Level "+level+"</p>");
        timer.setSingleShot(true);
}

void GUIGame::RemovePage(QGraphicsScene *scene)
{
    for(int i=0;i<2;i++)
    {
        scene->removeItem(GUIGamelist+i);
        scene->removeItem(GUIGamenamelist+i);
    }
    scene->removeItem(&GUIGamelevel);

    scene->removeItem(&robot);
}

void GUIGame::AddPage(QGraphicsScene *scene)
{
    GUIGamelist[0].setVisible(false);
    GUIGamenamelist[0].setVisible(false);

    for(int i=0;i<2;i++)
    {
        scene->addItem(GUIGamelist+i);
        scene->addItem(GUIGamenamelist+i);
    }
    scene->addItem(&GUIGamelevel);
    scene->addItem(&robot);
        scene->addItem(&GUIGameInfo);
}

void GUIGame::AddInfo(QGraphicsScene *scene)
{
    GUIGameInfo.setHtml("<p>Perfect!  Next level! </p>");
    timer.start(3000);
}

void GUIGame::RemoveInfo(QGraphicsScene *scene)
{
    scene->removeItem(&GUIGameInfo);
}

void GUIGame::InfoChange()
{
    GUIGameInfo.setHtml("");
}
