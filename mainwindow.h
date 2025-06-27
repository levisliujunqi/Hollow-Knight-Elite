#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsScene>
#include<iostream>
#include"uicontroller.h"
#include"scene.h"
#include<QRectF>
#include<QPushButton>
#include"keypresseater.h"
#include<QStyle>
#include"beginscene.h"
#include"playscene.h"
#include"endscene.h"
#include"failscene.h"
class UIController;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void createplayscene(int id);
    void createfailscene();
    void returnmain();
signals:
    void closeevent();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::MainWindow *ui;
    KeyPressEater *keypresseater;
    UIController *uicontroller;
    BeginScene *beginscene;
    PlayScene *playscene;
    EndScene *endscene;
    FailScene *failscene;
};
#endif // MAINWINDOW_H
