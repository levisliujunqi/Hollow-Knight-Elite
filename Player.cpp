#include "Player.h"

Player::Player(UIController *uicontroller, double maxhealth,double health, double ad, double movev,double fastmovev,double jumpv,int attackdelay,int fastmovedelay,int attackpretime,double x, double y, double width, double height, int addbloodcd,int preattack,int prefastmove,int preaddblood,QPixmap &img,function<bool(Character*)> checkifontheground):
    Character(uicontroller,maxhealth,health,ad,movev,fastmovev,jumpv,attackdelay,fastmovedelay,attackpretime,15,14,10,12,x,y,width,height,addbloodcd,preattack,prefastmove,preaddblood,img,checkifontheground)
{
    moveleftTimer=new QTimer(this);
    moverightTimer=new QTimer(this);
    jumpTimer=new QTimer(this);
    attackTimer=new QTimer(this);
    dropTimer=new QTimer(this);
    fastmoveTimer=new QTimer(this);

    moveleftTimer->setInterval(16);
    moverightTimer->setInterval(16);
    jumpTimer->setInterval(16);
    attackTimer->setInterval(16);
    dropTimer->setInterval(16);
    fastmoveTimer->setInterval(16);

    connect(moveleftTimer,&QTimer::timeout,this,[&](){
        addmoveleftstate();
    });
    connect(moverightTimer,&QTimer::timeout,this,[&](){
        addmoverightstate();
    });
    connect(jumpTimer,&QTimer::timeout,this,[&](){
        addjumpstate();
    });
    connect(attackTimer,&QTimer::timeout,this,[&](){
        addattackstate();
    });
    connect(dropTimer,&QTimer::timeout,this,[&](){
        adddropstate();
    });
    connect(fastmoveTimer,&QTimer::timeout,this,[&](){
        addfastmovestate();
    });
}

void Player::keypress(int key){
    if(key==Qt::Key_D){
        moverightTimer->start();
    }else if(key==Qt::Key_A){
        moveleftTimer->start();
    }else if(key==Qt::Key_Space){
        jumpTimer->start();
    }else if(key==Qt::Key_J){
        attackTimer->start();
    }else if(key==Qt::Key_K){
        fastmoveTimer->start();
    }else if(key==Qt::Key_L){
        int nowt=QDateTime::currentMSecsSinceEpoch();
        if(nowt-preaddblood>=addbloodcd){
            preaddblood=nowt;
            double add=min(10.0,maxhealth-health);
            health+=add;
            addelements(new AddBlood(uicontroller,x,y,add));
        }
    }
}
void Player::keyrelease(int key){
    if(key==Qt::Key_D){
        moverightTimer->stop();
        delmoverightstate();
    }else if(key==Qt::Key_A){
        moveleftTimer->stop();
        delmoveleftstate();
    }else if(key==Qt::Key_Space){
        jumpTimer->stop();
    }else if(key==Qt::Key_J){
        attackTimer->stop();
    }else if(key==Qt::Key_K){
        fastmoveTimer->stop();
    }
}
Player::~Player(){
}

void Player::showstillpicture()
{
    QPixmap img(QString::fromStdString(":/res/Player/Still/"+to_string(direction)+"/0.png"));
    uicontroller->UpdateRectBackground(item,img);
}

void Player::showwalkpicture(int frame)
{
    QPixmap img(QString::fromStdString(":/res/Player/Walk/"+to_string(direction)+"/"+to_string(frame/2)+".png"));
    uicontroller->UpdateRectBackground(item,img);
}

void Player::showattackpicture(int frame)
{
    QPixmap img(QString::fromStdString(":/res/Player/Attack/"+to_string(direction)+"/"+to_string(frame)+".png"));
    uicontroller->UpdateRectBackground(item,img);
}

void Player::showfastmovepicture(int frame)
{
    QPixmap img(QString::fromStdString(":/res/Player/FastMove/"+to_string(direction)+"/"+to_string(frame)+".png"));
    uicontroller->UpdateRectBackground(item,img);
}
