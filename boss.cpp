#include "boss.h"

Boss::Boss(UIController *uicontroller, double maxhealth,double health, double ad, double movev, double fastmovev, double jumpv, int attackdelay, int fastmovedelay, int attackpretime, double x, double y, double width, double height, double addbloodcd,int preattack,int prefastmove,int preaddblood,QPixmap &img, function<bool (Character *)> checkifontheground):
    Enemy(uicontroller,maxhealth,health,ad,movev,fastmovev,jumpv,attackdelay,fastmovedelay,attackpretime,7,6,10,12,x,y,width,height,addbloodcd,preattack,prefastmove,preaddblood,img,checkifontheground){}

void Boss::showstillpicture()
{
    QPixmap img(QString::fromStdString(":/res/Boss/still/"+to_string(direction)+"/0.png"));
    uicontroller->UpdateRectBackground(item,img);
}

void Boss::showwalkpicture(int frame)
{
    QPixmap img(QString::fromStdString(":/res/Boss/walk/"+to_string(direction)+"/"+to_string(frame/2)+".png"));
    uicontroller->UpdateRectBackground(item,img);
}

void Boss::showattackpicture(int frame)
{
    QPixmap img(QString::fromStdString(":/res/Boss/attack/"+to_string(direction)+"/"+to_string(frame)+".png"));
    uicontroller->UpdateRectBackground(item,img);
}

void Boss::showfastmovepicture(int frame)
{

}
