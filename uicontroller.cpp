#include "uicontroller.h"
#include "mainwindow.h"
UIController::UIController(MainWindow *mw,double width,
                           double height,KeyPressEater *keypresseater):width(width),
                            height(height),keypresseater(keypresseater){
    pScene=new QGraphicsScene();
    pScene->setSceneRect(0,0,width,height);
    pView=new CustomGraphicsView(pScene,(QWidget*)mw);
    mw->setCentralWidget(pView);
}

UIController::~UIController(){
    delete pScene;
    delete pView;
}

void UIController::MoveCamera(double x, double y){
    x=fmax(0,x),y=fmax(0,y);
    x=fmin(width,x),y=fmin(height,y);
    pView->fitInView(QRectF(x,y,100,60),Qt::KeepAspectRatio);
}

void UIController::clear(){
    pScene->clear();
    pScene->setBackgroundBrush(Qt::NoBrush);
    pView->resetTransform();
}

QGraphicsRectItem* UIController::CreateRect(double x,double y,double width,double height,Qt::GlobalColor color=Qt::black,qreal z){
    QGraphicsRectItem *a=pScene->addRect(x,y,width,height);
    a->setBrush(color);
    a->setZValue(z);
    return a;
}

QGraphicsPixmapItem* UIController::CreateRectWithBackground(QPixmap img,double width,double height,qreal z){
    auto newimg=img.scaled(width,height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *item=pScene->addPixmap(newimg);
    item->setZValue(z);
    return item;
}

bool UIController::IsCrash(QGraphicsItem *x,QGraphicsItem *y){
    return x->collidesWithItem(y,Qt::IntersectsItemBoundingRect);
}

void UIController::SetBackgroundColor(Qt::GlobalColor color){
    pScene->setBackgroundBrush(color);
}

void UIController::SetBackgroundPicture(QPixmap img){
    QSize sceneSize = pScene->sceneRect().size().toSize();
    QPixmap scaledImg = img.scaled(sceneSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pScene->setBackgroundBrush(scaledImg);
}

void UIController::UpdatePos(QGraphicsItem *a, double x, double y){
    a->setPos(x,y);
}

void UIController::UpdateRectBackground(QGraphicsPixmapItem* a,QPixmap img){
    QPixmap currentPixmap = a->pixmap();
    QSize itemSize(a->sceneBoundingRect().width(),a->sceneBoundingRect().height());
    //qDebug()<<a->sceneBoundingRect().width()<<" "<<a->sceneBoundingRect().height()<<"!\n";
    QPixmap scaledImg = img.scaled(a->sceneBoundingRect().width(),a->sceneBoundingRect().height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    a->setPixmap(scaledImg);
}

std::pair<QGraphicsProxyWidget*,QPushButton*> UIController::CreateButton(double x,double y,double width,double height,QString text,qreal z){
    QPushButton *button=new QPushButton(text);
    button->setFixedSize(width,height);
    button->setStyleSheet("QPushButton{padding:0px;margin:0px;border:none;}");
    QGraphicsProxyWidget *a=pScene->addWidget(button);
    a->setPos(x,y);
    a->setZValue(z);
    return std::make_pair(a,button);
}

double UIController::getwidth(){
    return width;
}
double UIController::getheight(){
    return height;
}
QGraphicsTextItem* UIController::CreateText(QString text,QFont f,qreal z){
    auto item=pScene->addText(text,f);
    item->setZValue(z);
    return item;
}
void UIController::UpdateTextPos(QGraphicsTextItem* a,double x,double y){
    a->setPos(x,y);
}
void UIController::delitem(QGraphicsItem *item){
    pScene->removeItem(item);
    delete item;
}
void UIController::delay(int ms){
    auto end=QTime::currentTime().addMSecs(ms);
    while(QTime::currentTime()<end){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}
QString UIController::getnowdir(){
    QString appDir=QCoreApplication::applicationDirPath();

    #if defined(Q_OS_MACOS)
        QDir bundleDir(appDir);
        if(bundleDir.cd("../../../")) {
            qDebug()<<appDir<<" "<<bundleDir.absolutePath()<<"\n";
            return bundleDir.absolutePath(); // 返回 .app 包路径
        }
    #endif
    return appDir;
}
