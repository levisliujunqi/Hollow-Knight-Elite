#ifndef FAILSCENE_H
#define FAILSCENE_H
#include "scene.h"

class UIController;

class FailScene : public Scene {
    Q_OBJECT
public:
    FailScene(UIController *uicontroller);
    ~FailScene();

signals:
    void returnMain();  // 返回主菜单
private:
    UIController *uicontroller;
};

#endif // FAILSCENE_H
