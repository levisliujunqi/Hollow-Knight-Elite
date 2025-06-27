#ifndef ENEMY1_H
#define ENEMY1_H

#include "enemy.h"

class Enemy1 : public Enemy
{
public:
    Enemy1(UIController *uicontroller,double maxhealth,double health,double ad,double movev,double fastmovev,double jumpv,int attackdelay,int fastmovedelay,int attackpretime,double x,double y,double width,double height,int addbloodcd,int preattack,int prefastmove,int preaddblood,QPixmap &img,function<bool(Character*)> checkifontheground);
    void showstillpicture() override;
    void showwalkpicture(int frame) override;
    void showattackpicture(int frame) override;
    void showfastmovepicture(int frame) override;
};

#endif // ENEMY1_H
