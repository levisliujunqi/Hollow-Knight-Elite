#include "failscene.h"

FailScene::FailScene(UIController *uicontroller):uicontroller(uicontroller) {
    uicontroller->clear();
    QPixmap bg(":/res/beginscenebackground.png");  // 失败背景图
    uicontroller->SetBackgroundPicture(bg);

    QFont font("Arial", 36, QFont::Bold);
    auto textitem = uicontroller->CreateText(QString("游戏失败！"), font);
    textitem->setDefaultTextColor(Qt::red);
    textitem->setPos(uicontroller->getwidth()/2 - textitem->boundingRect().width()/2,
                     uicontroller->getheight()/2 - textitem->boundingRect().height());

    auto [buttonitem, button] = uicontroller->CreateButton(uicontroller->getwidth()/2 - 200/2,
                                                           uicontroller->getheight()/2 + 50,
                                                           200, 50, QString("返回主菜单"));

    connect(button, &QPushButton::clicked, [&](){
        emit returnMain();
    });
}

FailScene::~FailScene() {
    uicontroller->clear();
}
