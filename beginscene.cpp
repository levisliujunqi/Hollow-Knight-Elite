#include "beginscene.h"
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFont>
#include <QPixmap>
#include <QString>
#include <QPushButton>
#include <QDebug>
//#include "playscene.h"


BeginScene::BeginScene(UIController *uicontroller)
    : uiController(uicontroller)
{
    QPixmap bg(":/res/beginscenebackground.png"); // TODO: 替换为实际背景图路径
    uiController->SetBackgroundPicture(bg);

    // 获取当前的视图和场景
    /*QGraphicsView *view = qobject_cast<QGraphicsView*>(mainWindow->centralWidget());*/
    //if (view) {
    // 在界面中心绘制标题文字
    QFont font("Arial", 36, QFont::Bold);
    QGraphicsTextItem *titleItem=uicontroller->CreateText(QString("Welcome to our Game！！！"),font);
    titleItem->setDefaultTextColor(Qt::white);
    // 将标题置于水平和垂直中心位置
    QRectF textRect = titleItem->boundingRect();
    //QRectF sceneRect = scene->sceneRect();
    titleItem->setPos((uicontroller->getwidth() - textRect.width()) / 2,
                      (uicontroller->getheight() - textRect.height()) / 4);


    // 创建“开始游戏”按钮，置于标题下方
    double sceneWidth = uicontroller->getwidth();
    double sceneHeight = uicontroller->getheight();
    int btnW = 200, btnH = 50;
    double btnX = (sceneWidth - btnW) / 2;
    double btnY = sceneHeight * 0.6;
    auto pair = uiController->CreateButton(btnX, btnY, btnW, btnH, QStringLiteral("开始游戏"));
    QGraphicsProxyWidget *proxyBtn = pair.first;
    QPushButton *startButton = pair.second;

    connect(startButton,&QPushButton::clicked,[&](){
        emit createplayscene(1);
    });
}
BeginScene::~BeginScene(){
    uiController->clear();
}
