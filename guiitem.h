#ifndef GUIITEM_H
#define GUIITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QBrush>

#include<database/browser.h>
#include "robot.h"

#define MAXPLAYERNUM 5
#define PLAYEROPTIONNUM 2
#define SYSTEMSETNUM 2


class GUILoginPage
{
public:
    GUILoginPage();
    void PageInit(QStringList list);
    void PageUpdate(QStringList list);

    void RemovePage(QGraphicsScene *scene);
    void AddPage(QGraphicsScene *scene);

    void AddPlayerList(QGraphicsScene *scene);
    void RemovePlayerList(QGraphicsScene *scene);

    void AddOption(QGraphicsScene *scene);
    void RemoveOption(QGraphicsScene *scene);

    void RemoveAll(QGraphicsScene *scene)
    {
        RemovePage(scene);
        RemovePlayerList(scene);
        RemoveOption(scene);
    }
    const QString Title;
    QGraphicsTextItem GUITitle;

    QStringList playerName;
    QGraphicsTextItem GUIPlayernamelist[MAXPLAYERNUM+1];

    QGraphicsRectItem GUIPlayerlist[MAXPLAYERNUM+1];

    QGraphicsTextItem GUIPlayeroptionname[PLAYEROPTIONNUM];
    QGraphicsRectItem GUIPlayeroption[PLAYEROPTIONNUM];

    QGraphicsRectItem GUISystemsetting[SYSTEMSETNUM+1];

};

#define PROFILELISTNUM 3
#define PROFILEOPTIONNUM 3
#define MAXLEVEL 10

class GUIProfile
{
private:
    int colornum;

public:


    GUIProfile();
    void PageInit(QBrush color);
    void PageUpdate(QStringList list);

    void RemovePage(QGraphicsScene *scene);
    void AddPage(QGraphicsScene *scene);

    void AddOptionList(QGraphicsScene *scene);
    void RemoveOptionList(QGraphicsScene *scene);

    void AddHistoryList(QGraphicsScene *scene);
    void RemoveHistoryList(QGraphicsScene *scene);

    void RemoveAll(QGraphicsScene *scene)
    {
        RemovePage(scene);
        RemoveOptionList(scene);
        RemoveHistoryList(scene);
    }

    void ChangeColor();
    void ChangeBack(QGraphicsScene *scene);
    void ChangeRole(QGraphicsScene *scene);

    QGraphicsTextItem GUIProfilenamelist[PROFILELISTNUM];
    QGraphicsRectItem GUIProfilelist[PROFILELISTNUM];

    QGraphicsTextItem GUIProfileoptionnamelist[PROFILEOPTIONNUM];
    QGraphicsRectItem GUIProfileoptionlist[PROFILEOPTIONNUM];

    QGraphicsTextItem GUIProfilerecordnamelist[MAXLEVEL];
    QGraphicsRectItem GUIProfilerecordlist[MAXLEVEL];

    Robot robot;


};

class GUIGame:public QObject
{
    Q_OBJECT
public:
    GUIGame(QObject *parent=0);
    void PageInit(QString level);
    void PageUpdate(QString level);

    void RemovePage(QGraphicsScene *scene);
    void AddPage(QGraphicsScene *scene);

    void RemoveInfo(QGraphicsScene *scene);
    void AddInfo(QGraphicsScene *scene);

    QGraphicsTextItem GUIGamelevel;

    QGraphicsTextItem GUIGameInfo;

    QGraphicsTextItem GUIGamenamelist[2];
    QGraphicsRectItem GUIGamelist[2];

    Robot robot;
    QTimer timer;
private slots:

    void InfoChange();


};

#endif // GUIITEM_H
