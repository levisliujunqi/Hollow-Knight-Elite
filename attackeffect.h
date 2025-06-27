#ifndef ATTACKEFFECT_H
#define ATTACKEFFECT_H

#include "elements.h"

class AttackEffect : public Elements
{
protected:
    bool direction;
    int nowframe;
    QGraphicsPixmapItem *item;
public:
    AttackEffect(UIController *uicontroller,bool direction,double x,double y,double width,double height);
    bool showpicture() override;
};

#endif // ATTACKEFFECT_H
