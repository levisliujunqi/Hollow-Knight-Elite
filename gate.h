#ifndef GATE_H
#define GATE_H
#include "uicontroller.h"
class Gate
{
public:
    UIController *uicontroller;
    pair<double,double> to;
    QGraphicsPixmapItem *item;
    Gate(UIController *uicontroller,double x,double y,double width,double height,pair<double,double> to,QPixmap img);
};

#endif // GATE_H
