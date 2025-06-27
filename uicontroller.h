#ifndef UICONTROLLER_H
#define UICONTROLLER_H
#include "customgraphicsview.h"
#include <QGraphicsView>
#include <QPushButton>
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "keypresseater.h"
#include <QGraphicsProxyWidget>
#include <QFont>
#include <QString>
#include "keypresseater.h"
#include "customgraphicsview.h"
#include <QTime>
class MainWindow;
class UIController:public QObject
{
    Q_OBJECT
public:
    UIController(MainWindow *mw,double width,double height,KeyPressEater* keypresseater);
    ~UIController();
    void clear();
    void MoveCamera(double x,double y);
    //z越大越靠前
    QGraphicsRectItem* CreateRect(double x,double y,double width,double height,Qt::GlobalColor color,qreal z=0);
    QGraphicsPixmapItem* CreateRectWithBackground(QPixmap img,double width,double height,qreal z=0);
    QGraphicsTextItem* CreateText(QString text,QFont f,qreal z=0);
    std::pair<QGraphicsProxyWidget*,QPushButton*> CreateButton(double x,double y,double width,double height,QString text,qreal z=0);
    bool IsCrash(QGraphicsItem *x,QGraphicsItem *y);
    void SetBackgroundPicture(QPixmap img);
    void SetBackgroundColor(Qt::GlobalColor color);
    void UpdatePos(QGraphicsItem *a,double x,double y);
    void UpdateRectBackground(QGraphicsPixmapItem* a,QPixmap img);
    void UpdateTextPos(QGraphicsTextItem* a,double x,double y);
    double getwidth();
    double getheight();
    void delitem(QGraphicsItem *item);
    KeyPressEater* keypresseater;
    QGraphicsScene *pScene;
    CustomGraphicsView *pView;
    void delay(int ms);
    double width;
    double height;
    QString getnowdir();
};

#endif // UICONTROLLER_H
