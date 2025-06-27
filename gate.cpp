#include "gate.h"


Gate::Gate(UIController *uicontroller,double x,double y,double width,double height,pair<double, double> to,QPixmap img):uicontroller(uicontroller),to(to)
{
    item=uicontroller->CreateRectWithBackground(img,width,height,-1);
    item->setPos(x,y);
}
