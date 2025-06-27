#ifndef ENDSCENE_H
#define ENDSCENE_H
#include "scene.h"
class UIController;
class EndScene:public Scene
{
    Q_OBJECT
public:
    EndScene(UIController *uicontroller);
    ~EndScene();
signals:
    void returnmain();
private:
    UIController *uicontroller;
};

#endif // ENDSCENE_H
