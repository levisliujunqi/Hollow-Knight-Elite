#include "endscene.h"

EndScene::EndScene(UIController *uicontroller):uicontroller(uicontroller) {
    uicontroller->clear();
    QPixmap bg(":/res/beginscenebackground.png");
    uicontroller->SetBackgroundPicture(bg);
    QFont font("Arial",36,QFont::Bold);
    auto textitem=uicontroller->CreateText(QString("你已经全部通关了"),font);
    textitem->setDefaultTextColor(Qt::white);
    textitem->setPos(uicontroller->getwidth()/2-textitem->boundingRect().width()/2,
                     uicontroller->getheight()/2-textitem->boundingRect().height());
    auto [buttonitem,button]=uicontroller->CreateButton(uicontroller->getwidth()/2-200/2,uicontroller->getheight()/2+50,200,50,QString("返回"));
    connect(button,&QPushButton::clicked,[&](){
        emit returnmain();
    });
}
EndScene::~EndScene(){
    uicontroller->clear();
}
