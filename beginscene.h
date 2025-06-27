#ifndef BEGINSCENE_H
#define BEGINSCENE_H

#include "scene.h"

class PlayScene; // 前向声明
class UIController;


class BeginScene : public Scene
{
    Q_OBJECT
public:
    BeginScene(UIController *uicontroller);
    ~BeginScene();
signals:
    void createplayscene(int id);
private:
    UIController *uiController;
};

#endif // BEGINSCENE_H
