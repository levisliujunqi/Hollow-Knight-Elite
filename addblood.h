#ifndef ADDBLOOD_H
#define ADDBLOOD_H

#include "elements.h"

class AddBlood : public Elements
{
public:
    AddBlood(UIController *uicontroller,double x,double y,int addblood);
    QGraphicsTextItem *item;
private:
    double x,y;
    int nowframe;
    bool showpicture() override;
};

#endif // ADDBLOOD_H
