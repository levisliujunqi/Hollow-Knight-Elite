#include "enemy1.h"

Enemy1::Enemy1(UIController *uicontroller, double maxhealth,double health, double ad, double movev, double fastmovev, double jumpv, int attackdelay, int fastmovedelay, int attackpretime, double x, double y, double width, double height, int addbloodcd,int preattack,int prefastmove,int preaddblood,QPixmap &img, function<bool (Character *)> checkifontheground):
    Enemy(uicontroller,maxhealth,health,ad,movev,fastmovev,jumpv,attackdelay,fastmovedelay,attackpretime,6,6,10,12,x,y,width,height,addbloodcd,preattack,prefastmove,preaddblood,img,checkifontheground)
{

}

void Enemy1::showstillpicture()
{
    QPixmap img(QString::fromStdString(":/res/Enemy1/still/"+to_string(direction)+"/0.png"));
    uicontroller->UpdateRectBackground(item,img);
}

void Enemy1::showwalkpicture(int frame)
{
    QPixmap img(QString::fromStdString(":/res/Enemy1/walk/"+to_string(direction)+"/"+to_string(frame/2)+".png"));
    uicontroller->UpdateRectBackground(item,img);
}

void Enemy1::showattackpicture(int frame)
{
    QPixmap img(QString::fromStdString(":/res/Enemy1/attack/"+to_string(direction)+"/"+to_string(frame)+".png"));
    uicontroller->UpdateRectBackground(item,img);
}

void Enemy1::showfastmovepicture(int frame)
{

}
