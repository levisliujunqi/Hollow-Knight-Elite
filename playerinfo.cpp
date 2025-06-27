#include "playerinfo.h"

PlayerInfo::PlayerInfo(UIController *uicontroller, Player *player):player(player)
{
    avatar=uicontroller->CreateRectWithBackground(QPixmap(":/res/Player/Still/1/0.png"),20,40,10);
    avatar->setPos(10,10);
    health1=uicontroller->CreateRect(0,0,70,5,Qt::gray,1);
    health2=uicontroller->CreateRect(0,0,70,5,Qt::red,2);
    health1->setPos(50,15);
    health2->setPos(50,15);
    fastmovepic=uicontroller->CreateRectWithBackground(QPixmap(":/res/Player/FastMove/1/0.png"),30,20,1);
    fastmovepic->setPos(40,30);
    fastmovebound=uicontroller->CreateRect(50,30,25,20,Qt::white,-1);
    fastmovebound->setPen(QPen(Qt::white,0.5));
    fastmovebound->setBrush(Qt::NoBrush);
    QFont font("Arial", 20, QFont::Bold);
    addbloodpic=uicontroller->CreateRectWithBackground(QPixmap(":/res/addblood.jpg"),20,20,1);
    addbloodpic->setPos(90,29);
    addbloodbound=uicontroller->CreateRect(87,30,25,20,Qt::white,-1);
    addbloodbound->setPen(QPen(Qt::white,0.5));
    addbloodbound->setBrush(Qt::NoBrush);
    QFont font1("Arial", 15, QFont::Bold);
    fastmovecd=uicontroller->CreateText("0",font1,100);
    fastmovecd->setPos(49,30);
    fastmovecd->setDefaultTextColor(Qt::white);
    addbloodcd=uicontroller->CreateText("0",font1,100);
    addbloodcd->setPos(85,30);
    addbloodcd->setDefaultTextColor(Qt::white);
}

bool PlayerInfo::showpicture()
{
    health2->setRect(0,0,70*max(0.0,player->health)/player->maxhealth,5);
    int nowt=QDateTime::currentMSecsSinceEpoch();
    if(nowt-player->prefastmove<player->fastmovedelay){
        fastmovebound->setOpacity(0.4);
        fastmovepic->setOpacity(0.4);
        fastmovecd->setPlainText(QString::number((player->prefastmove+player->fastmovedelay-nowt)/1000.0,'f',1));
    }else{
        fastmovebound->setOpacity(1);
        fastmovepic->setOpacity(1);
        fastmovecd->setPlainText("");
    }
    if(nowt-player->preaddblood<player->addbloodcd){
        addbloodbound->setOpacity(0.4);
        addbloodpic->setOpacity(0.4);
        addbloodcd->setPlainText(QString::number((player->preaddblood+player->addbloodcd-nowt)/1000.0,'f',1));
    }else{
        addbloodbound->setOpacity(1);
        addbloodpic->setOpacity(1);
        addbloodcd->setPlainText("");
    }
    return true;
}
