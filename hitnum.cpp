#include "hitnum.h"

HitNum::HitNum(UIController *uicontroller, double x, double y,int damage):Elements(uicontroller),nowframe(0),x(x),y(y)
{
    QFont font("Arial", 20, QFont::Bold);
    item=uicontroller->CreateText(QString::fromStdString("-"+to_string(damage)),font,3);
    item->setDefaultTextColor(Qt::red);
    item->setPos(x,y);
}

bool HitNum::showpicture()
{
    if(nowframe==16){
        uicontroller->delitem(item);
        return false;
    }
    if(nowframe%5==0) item->setPos(x,y-(nowframe/5+1)*10);
    nowframe++;
    return true;
}
