#ifndef ENEMY_H
#define ENEMY_H
#include"character.h"
#include"Player.h"
class Enemy:public Character
{
    Q_OBJECT
private:
    bool run;
    double originx,originy;
    bool turnback;
public:
    Enemy(UIController *uicontroller,double maxhealth,double health,double ad,double movev,double fastmovev,double jumpv,int attackdelay,int fastmovedelay,int attackpretime,int attacktotalframesnum,int totalmoveframesnum,int totaljumpframesnum,int totalfastmoveframesnum,double x,double y,double width,double height,int addbloodcd,int preattack,int prefastmove,int preaddblood,QPixmap &img,function<bool(Character*)> checkifontheground);
    void AI(Player* player);
    void showstillpicture() override;
    void showwalkpicture(int frame) override;
    void showattackpicture(int frame) override;
    void showfastmovepicture(int frame) override;
};

#endif // ENEMY_H
