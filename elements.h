#ifndef ELEMENTS_H
#define ELEMENTS_H
#include"uicontroller.h"
class Elements
{
public:
    Elements();
    Elements(UIController *uicontroller);
    UIController *uicontroller;
    virtual bool showpicture();
};

#endif // ELEMENTS_H
