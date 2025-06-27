#include "enemy.h"

Enemy::Enemy(UIController *uicontroller,double maxhealth,double health,double ad,double movev,double fastmovev,double jumpv,int attackdelay,int fastmovedelay,int attackpretime,int attacktotalframesnum,int totalmoveframesnum,int totaljumpframesnum,int totalfastmoveframesnum,double x,double y,double width,double height,int addbloodcd,int preattack,int prefastmove,int preaddblood,QPixmap &img,function<bool(Character*)> checkifontheground):run(0),
    Character(uicontroller,maxhealth,health,ad,movev,fastmovev,jumpv,attackdelay,fastmovedelay,attackpretime,attacktotalframesnum,totalmoveframesnum,totaljumpframesnum,totalfastmoveframesnum,x,y,width,height,addbloodcd,preattack,prefastmove,preaddblood,img,checkifontheground),originx(x),originy(y),turnback(0){}

void Enemy::AI(Player *player){
    if(busystate.count(ATTACK)) return;
    if(fabs(player->y-y)>100||fabs(player->x+width/2-(x+width/2))>150){
        //health=maxhealth;
        if(fabs(originx-x)>=movev){
            if(originx>x){
                delmoveleftstate();
                if(turnback){
                    delmoverightstate();
                    turnback=0;
                }
                addmoverightstate();
            }else{
                delmoverightstate();
                if(turnback){
                    delmoveleftstate();
                    turnback=0;
                }
                addmoveleftstate();
            }
        }else{
            delmoveleftstate();
            delmoverightstate();
            turnback=0;
        }
    }else if(player->x<x){
        if(player->x+player->width/2<x-attackwidth){
            if(turnback){
                delmoveleftstate();
                turnback=0;
            }
            delmoverightstate();
            addmoveleftstate();
        }else{
            if(direction!=0){
                if(turnback){
                    delmoveleftstate();
                    turnback=0;
                }
                delmoverightstate();
                addmoveleftstate(0);
                turnback=1;
            }else{
                delmoveleftstate();
                delmoverightstate();
                addattackstate();
            }
        }
    }else{
        if(x+width+attackwidth<player->x+player->width/2){
            delmoveleftstate();
            if(turnback){
                delmoverightstate();
                turnback=0;
            }
            addmoverightstate();
        }else{
            if(direction!=1){
                delmoveleftstate();
                if(turnback){
                    delmoverightstate();
                    turnback=0;
                }
                addmoverightstate(0);
                turnback=1;
            }else{
                delmoveleftstate();
                delmoverightstate();
                addattackstate();
            }
        }
    }
}

void Enemy::showstillpicture()
{
    QPixmap img(QString::fromStdString(":/res/Player/Still/"+to_string(direction)+"/0.png"));
    uicontroller->UpdateRectBackground(item,img);
}

void Enemy::showwalkpicture(int frame)
{
    QPixmap img(QString::fromStdString(":/res/Player/Walk/"+to_string(direction)+"/"+to_string(frame/2)+".png"));
    uicontroller->UpdateRectBackground(item,img);
}

void Enemy::showattackpicture(int frame)
{

}

void Enemy::showfastmovepicture(int frame)
{

}
