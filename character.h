#ifndef CHARACTER_H
#define CHARACTER_H
#include<vector>
#include"uicontroller.h"
#include<QTimer>
#include<QPointer>
#include<QPropertyAnimation>
#include<queue>
#include<map>
#include<QFuture>
#include<QtConcurrent/QtConcurrent>
#include"busystateinfo.h"
#include<QDateTime>
#include"playerattackeffect.h"
#include"busymovestateinfo.h"
#include"hitnum.h"
#include"addblood.h"
using namespace std;

class Character:public QObject
{
    Q_OBJECT
public:
    enum state{MOVEL,MOVER,JUMP,ATTACK,DROP,FASTMOVE};
    void walk(double x,double y);//走到(x,y)
    Character(UIController *uicontroller,double maxhealth,double health,double ad,double movev,double fastmovev,double jumpv,int attackdelay,int fastmovedelay,int attackpretime,int attacktotalframesnum,int totalmoveframesnum,int totaljumpframesnum,int totalfastmoveframesnum,double x,double y,double width,double height,int addbloodcd,int preattack,int prefastmove,int preaddblood,QPixmap img,function<bool(Character*)> checkifontheground);//在(x,y)出生
    ~Character();
    bool isdead();
    QGraphicsPixmapItem* item;
    QGraphicsRectItem* healthdisplay1;
    QGraphicsRectItem* healthdisplay2;
    void updatehealthdisplay();
    map<state,busystateinfo*> busystate;
    bool accessbusystate;
    function<bool(Character*)> checkifontheground;
    virtual void showstillpicture();
    virtual void showwalkpicture(int frame);
    virtual void showattackpicture(int frame);
    virtual void showfastmovepicture(int frame);
    int preattack;
    int prefastmove;
    int preaddblood;
    void addattackstate();
    void addfastmovestate();
    void addmoveleftstate(double dis=-1);
    void addmoverightstate(double dis=-1);
    void addjumpstate();
    void adddropstate();
    void delmoveleftstate();
    void delmoverightstate();
    void delonestate(state s);
signals:
    void attacksignal(QGraphicsRectItem *p,double ad);
    void die(Character* c);
    void addelements(Elements* ele);
public slots:
    void attack();//攻击，emit attacksignal
    void moveleft();
    void moveright();
    void jump();
    void drop();
    void fastmove();
    void attackslots(QGraphicsRectItem *p,double ad);
public:
    int attackdelay;
    int fastmovedelay;
    int attackpretime;//前摇
    double x,y,width,height;
    double movev;
    double fastmovev;
    double jumpv;
    double health,maxhealth;//当前生命值，最大生命值
    bool direction;//朝向，0，左，1，右
    double ad;//攻击力
    int addbloodcd;
    UIController *uicontroller;
    double attackwidth,attackheight;
    int attacktotalframesnum,totalmoveframesnum,totaljumpframesnum,totalfastmoveframesnum;
};

#endif // CHARACTER_H
