#ifndef BOSS_H
#define BOSS_H

#include "enemy.h"

class Boss : public Enemy
{
public:
    Boss(UIController *uicontroller,double maxhealth,double health,double ad,double movev,double fastmovev,double jumpv,int attackdelay,int fastmovedelay,int attackpretime,double x,double y,double width,double height,double addbloodcd,int preattack,int prefastmove,int preaddblood,QPixmap &img,function<bool(Character*)> checkifontheground);
    void showstillpicture() override;
    void showwalkpicture(int frame) override;
    void showattackpicture(int frame) override;
    void showfastmovepicture(int frame) override;
};

#endif // BOSS_H
