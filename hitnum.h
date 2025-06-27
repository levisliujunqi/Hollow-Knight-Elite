#ifndef HITNUM_H
#define HITNUM_H

#include "elements.h"

class HitNum : public Elements
{
public:
    HitNum(UIController *uicontroller,double x,double y,int damage);
    QGraphicsTextItem *item;
private:
    double x,y;
    int nowframe;
    bool showpicture() override;
};

#endif // HITNUM_H
