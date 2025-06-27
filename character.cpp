#include "character.h"

Character::Character(UIController *uicontroller,double maxhealth,double health,double ad,double movev,double fastmovev,double jumpv,int attackdelay,int fastmovedelay,int attackpretime,int attacktotalframesnum,int totalmoveframesnum,int totaljumpframesnum,int totalfastmoveframesnum,double x,double y,double width,double height, int addbloodcd,int preattack,int prefastmove,int preaddblood,QPixmap img,function<bool(Character*)> checkifontheground):uicontroller(uicontroller),
    health(health),maxhealth(maxhealth),direction(1),ad(ad),x(x),y(y),width(width),height(height),movev(movev),fastmovev(fastmovev),jumpv(jumpv),attackdelay(attackdelay),fastmovedelay(fastmovedelay),attackpretime(attackpretime),attacktotalframesnum(attacktotalframesnum),totalmoveframesnum(totalmoveframesnum),totaljumpframesnum(totaljumpframesnum),totalfastmoveframesnum(totalfastmoveframesnum),healthdisplay1(nullptr),healthdisplay2(nullptr),accessbusystate(false),checkifontheground(checkifontheground),addbloodcd(addbloodcd),attackwidth(20),attackheight(height),preattack(preattack),preaddblood(preaddblood),prefastmove(prefastmove)
{
    item=uicontroller->CreateRectWithBackground(img,width,height,1);
    uicontroller->UpdatePos(item,x,y);
    healthdisplay1=uicontroller->CreateRect(0,0,width,5,Qt::gray,1);
    healthdisplay2=uicontroller->CreateRect(0,0,width,5,Qt::red,2);
    healthdisplay1->setPos(x,y-7);
    healthdisplay2->setPos(x,y-7);
}

void Character::updatehealthdisplay(){
    healthdisplay1->setPos(x,y-7);
    healthdisplay2->setPos(x,y-7);
    healthdisplay2->setRect(0,0,width*(max(0.0,health)/maxhealth),5);
}

void Character::showstillpicture()
{

}

void Character::showwalkpicture(int frame)
{

}

void Character::showattackpicture(int frame)
{

}

void Character::showfastmovepicture(int frame)
{

}

void Character::addattackstate()
{
    if(!busystate.count(JUMP)&&!busystate.count(DROP)&&!busystate.count(ATTACK)&&!busystate.count(FASTMOVE)){
        while(accessbusystate);
        accessbusystate=true;
        busystate[ATTACK]=new busystateinfo(0);
        delonestate(MOVEL);
        delonestate(MOVER);
        accessbusystate=false;
    }
}

void Character::delonestate(state s){
    auto it=busystate.find(s);
    if(it!=busystate.end()){
        delete it->second;
        busystate.erase(it);
    }
}
void Character::addfastmovestate()
{
    if(!busystate.count(FASTMOVE)){
        while(accessbusystate);
        accessbusystate=true;
        if(busystate.find(ATTACK)==busystate.end()||busystate[ATTACK]->nowframeid>3){
            delonestate(ATTACK);
            delonestate(MOVEL);
            delonestate(MOVER);
            busystate[FASTMOVE]=new busystateinfo(0);
        }
        accessbusystate=false;
    }
}

void Character::addmoveleftstate(double dis)
{
    if(!busystate.count(MOVEL)&&!busystate.count(FASTMOVE)){
        while(accessbusystate);
        accessbusystate=true;
        if(busystate.find(ATTACK)==busystate.end()||busystate[ATTACK]->nowframeid>3){
            busystate[MOVEL]=new busymovestateinfo(0,dis==-1?movev:dis);
            delonestate(ATTACK);
        }
        accessbusystate=false;
    }
}
void Character::delmoveleftstate(){
    while(accessbusystate);
    accessbusystate=true;
    if(busystate.count(MOVEL)){
        delonestate(MOVEL);
        showstillpicture();
    }
    accessbusystate=false;
}

void Character::delmoverightstate()
{
    while(accessbusystate);
    accessbusystate=true;
    if(busystate.count(MOVER)){
        delonestate(MOVER);
        showstillpicture();
    }
    accessbusystate=false;
}
void Character::addmoverightstate(double dis)
{
    if(!busystate.count(MOVER)&&!busystate.count(FASTMOVE)){
        while(accessbusystate);
        accessbusystate=true;
        if(busystate.find(ATTACK)==busystate.end()||busystate[ATTACK]->nowframeid>3){
            busystate[MOVER]=new busymovestateinfo(0,dis==-1?movev:dis);
            delonestate(ATTACK);
        }
        accessbusystate=false;
    }
}

void Character::addjumpstate()
{
    if(!busystate.count(DROP)&&!busystate.count(JUMP)&&!busystate.count(FASTMOVE)){
        while(accessbusystate);
        accessbusystate=true;
        if(busystate.find(ATTACK)==busystate.end()||busystate[ATTACK]->nowframeid>3){
            busystate[JUMP]=new busystateinfo(0);
            delonestate(ATTACK);
        }
        accessbusystate=false;
    }
}

void Character::adddropstate()
{
    if(!busystate.count(DROP)){
        while(accessbusystate);
        accessbusystate=true;
        delonestate(ATTACK);
        delonestate(JUMP);
        busystate[DROP]=new busystateinfo(0);
        accessbusystate=false;
    }
}

void Character::attack(){
    if(!busystate.count(ATTACK)) return;
    //攻击动作一共有几帧
    while(accessbusystate);
    accessbusystate=true;
    int nowt=QDateTime::currentMSecsSinceEpoch();
    auto it=busystate.find(ATTACK);
    if(nowt-preattack<attackdelay&&it->second->nowframeid==0){
        delete busystate[ATTACK];
        busystate.erase(ATTACK);
        showstillpicture();
    }else{
        if(it->second->nowframeid==attacktotalframesnum){
            showstillpicture();
            delete it->second;
            busystate.erase(it);
        }else{
            //放一帧
            if(it->second->nowframeid==attackpretime){
                preattack=nowt;
                QGraphicsRectItem *p=nullptr;
                PlayerAttackEffect* pp=nullptr;
                if(direction){
                    p=uicontroller->CreateRect(x,y,attackwidth+width,attackheight,Qt::yellow,2);
                    p->setOpacity(0);
                    pp=new PlayerAttackEffect(uicontroller,direction,x+width,y,attackwidth,attackheight);
                }else{
                    p=uicontroller->CreateRect(x-attackwidth,y,attackwidth+width,attackheight,Qt::yellow,2);
                    p->setOpacity(0);
                    pp=new PlayerAttackEffect(uicontroller,direction,x-attackwidth,y,attackwidth,attackheight);
                }
                emit attacksignal(p,ad);
                uicontroller->delitem(p);
                emit addelements(pp);
            }
            showattackpicture(it->second->nowframeid);
            it->second->nowframeid++;
        }
    }
    accessbusystate=false;
}

void Character::walk(double x,double y){
    this->x=x;
    this->y=y;
    uicontroller->UpdatePos(item,x,y);
    updatehealthdisplay();
}

void Character::moveleft(){
    if(!busystate.count(MOVEL)) return;
    if(direction==1) direction=0;
    const int totalframesnum=totalmoveframesnum;
    while(accessbusystate);
    accessbusystate=true;
    auto it=busystate.find(MOVEL);
    if(it->second->nowframeid==totalframesnum){
        it->second->nowframeid=0;
    }else{
        //放一帧
        showwalkpicture(it->second->nowframeid);
        //
        x-=min(static_cast<busymovestateinfo*>(it->second)->movev,movev);
        x=max(x,0.0);
        walk(x,y);
        it->second->nowframeid++;
        if(!checkifontheground(this)&&!busystate.count(JUMP)&&!busystate.count(DROP)){
            busystate[DROP]=new busystateinfo(0);
        }
    }
    accessbusystate=false;
}

void Character::moveright(){
    if(!busystate.count(MOVER)) return;
    if(direction==0) direction=1;
    const int totalframesnum=totalmoveframesnum;
    while(accessbusystate);
    accessbusystate=true;
    auto it=busystate.find(MOVER);
    if(it->second->nowframeid==totalframesnum){
        //busystate.erase(it);
        it->second->nowframeid=0;
    }else{
        //放一帧
        showwalkpicture(it->second->nowframeid);
        //
        x+=min(static_cast<busymovestateinfo*>(it->second)->movev,movev);
        x=min(x,uicontroller->width-width);
        walk(x,y);
        it->second->nowframeid++;
        if(!checkifontheground(this)&&!busystate.count(JUMP)&&!busystate.count(DROP)){
            busystate[DROP]=new busystateinfo(0);
        }
    }
    accessbusystate=false;
}

void Character::jump(){
    if(!busystate.count(JUMP)) return;
    const int totalframesnum=totaljumpframesnum;
    while(accessbusystate);
    accessbusystate=true;
    auto it=busystate.find(JUMP);
    if(it->second->nowframeid==totalframesnum){
        delete it->second;
        busystate.erase(it);
        busystate[DROP]=new busystateinfo(0);
    }else{
        //放一帧
        showstillpicture();
        y-=jumpv;
        walk(x,y);
        it->second->nowframeid++;
    }
    accessbusystate=false;
}

void Character::drop(){
    if(!busystate.count(DROP)) return;
    while(accessbusystate);
    accessbusystate=true;
    auto it=busystate.find(DROP);
    if(checkifontheground(this)){
        double l=0,r=jumpv,ans=0;
        double prey=y;
        const double eps=0.01;
        while(r-l>eps){
            double mid=(l+r)/2;
            double tmp=y;
            y=prey-mid;
            walk(x,y);
            if(checkifontheground(this)){
                ans=mid;
                l=mid+eps;
            }else{
                r=mid-eps;
            }
        }
        y=prey-ans;
        walk(x,y);
        delete it->second;
        busystate.erase(it);
    }else{
        //放一帧
        showstillpicture();
        y+=jumpv;
        walk(x,y);
        it->second->nowframeid++;
    }
    accessbusystate=false;
}

void Character::fastmove()
{
    if(!busystate.count(FASTMOVE)) return;
    int totalframesnum=totalfastmoveframesnum;
    while(accessbusystate);
    accessbusystate=true;
    int nowt=QDateTime::currentMSecsSinceEpoch();
    auto it=busystate.find(FASTMOVE);
    if(nowt-prefastmove<fastmovedelay&&it->second->nowframeid==0){
        delete busystate[FASTMOVE];
        busystate.erase(FASTMOVE);
        showstillpicture();
    }else{
        if(it->second->nowframeid==totalframesnum){
            delete it->second;
            busystate.erase(it);
            showstillpicture();
        }else{
            if(it->second->nowframeid==0){
                prefastmove=nowt;
            }
            showfastmovepicture(it->second->nowframeid);
            x+=(direction?1:-1)*fastmovev;
            x=min(x,uicontroller->width-width);
            x=max(x,0.0);
            walk(x,y);
            it->second->nowframeid++;
            if(!checkifontheground(this)){
                busystate.clear();
                busystate[DROP]=new busystateinfo(0);
            }
        }
    }
    accessbusystate=false;
}

bool Character::isdead(){
    return health<=0;
}

void Character::attackslots(QGraphicsRectItem *p,double ad){
    if(isdead()) return;
    if(uicontroller->IsCrash(item,p)&&!busystate.count(FASTMOVE)){
        double damage=min(health,ad);
        health-=damage;
        updatehealthdisplay();
        auto *pp=new HitNum(uicontroller,x,y,int(damage));
        addelements(pp);
        if(isdead()) {
            emit die(this);
        }
    }
}

Character::~Character(){
    uicontroller->delitem(item);
    uicontroller->delitem(healthdisplay1);
    uicontroller->delitem(healthdisplay2);
}
