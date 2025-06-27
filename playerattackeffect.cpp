#include "playerattackeffect.h"

PlayerAttackEffect::PlayerAttackEffect(UIController *uicontroller,bool direction,double x,double y,double width,double height):AttackEffect(uicontroller,direction,x,y,width,height) {
    QPixmap img(QString::fromStdString(":/res/Player/AttackEffect/"+to_string(direction)+"/0.png"));
    item=uicontroller->CreateRectWithBackground(img,width,height,100);
    item->setPos(x,y);
}

bool PlayerAttackEffect::showpicture()
{
    if(nowframe==totalframesnum){
        uicontroller->delitem(item);
        return false;
    }
    if(nowframe&1){
        nowframe++;
        return true;
    }
    QPixmap img(QString::fromStdString(":/res/Player/AttackEffect/"+to_string(direction)+"/"+to_string(nowframe/2)+".png"));
    nowframe++;
    uicontroller->UpdateRectBackground(item,img);
    return true;
}
