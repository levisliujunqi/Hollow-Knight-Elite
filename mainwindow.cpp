#include "mainwindow.h"
#include "./ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    beginscene(nullptr),
    playscene(nullptr),
    endscene(nullptr),
    failscene(nullptr)
{
    srand(time(0));
    ui->setupUi(this);
    setFixedSize(1000, 600);
    setGeometry(QStyle::alignedRect(
        Qt::LeftToRight,
        Qt::AlignCenter,
        size(),
        QGuiApplication::primaryScreen()->availableGeometry()
    ));
    keypresseater=new KeyPressEater();
    qApp->installEventFilter(keypresseater);
    uicontroller=new UIController(this,1000,600,keypresseater);
    returnmain();
    QTimer::singleShot(1000, this, [](){
        QMessageBox::information(nullptr,"tips","Press A to move left, D to move right, J to attack, K to dash, and L to activate the healing skill.");
    });
}

void MainWindow::createplayscene(int id){
    if(beginscene!=nullptr){
        delete beginscene;
        beginscene=nullptr;
    }
    if(playscene!=nullptr){
        delete playscene;
        playscene=nullptr;
    }
    if(endscene!=nullptr){
        delete endscene;
        endscene=nullptr;
    }
    if(failscene!=nullptr){
        delete failscene;
        failscene=nullptr;
    }
    if(id>2){
        endscene=new EndScene(uicontroller);
        connect(endscene,&EndScene::returnmain,this,&MainWindow::returnmain,Qt::QueuedConnection);
        return;
    }
    playscene=new PlayScene(uicontroller,id);
    connect(this,&MainWindow::closeevent,playscene,&PlayScene::closeevent);
    if(id==1) playscene->startLevel();
    connect(playscene,&PlayScene::createplayscene,this,&MainWindow::createplayscene,Qt::QueuedConnection);
    connect(playscene,&PlayScene::createfailscene,this,&MainWindow::createfailscene,Qt::QueuedConnection);
}

void MainWindow::createfailscene()
{
    if(beginscene!=nullptr){
        delete beginscene;
        beginscene=nullptr;
    }
    if(playscene!=nullptr){
        delete playscene;
        playscene=nullptr;
    }
    if(endscene!=nullptr){
        delete endscene;
        endscene=nullptr;
    }
    if(failscene!=nullptr){
        delete failscene;
        failscene=nullptr;
    }
    failscene=new FailScene(uicontroller);
    connect(failscene,&FailScene::returnMain,this,&MainWindow::returnmain,Qt::QueuedConnection);
}

void MainWindow::returnmain(){
    if(beginscene!=nullptr){
        delete beginscene;
        beginscene=nullptr;
    }
    if(playscene!=nullptr){
        delete playscene;
        playscene=nullptr;
    }
    if(endscene!=nullptr){
        delete endscene;
        endscene=nullptr;
    }
    if(failscene!=nullptr){
        delete failscene;
        failscene=nullptr;
    }
    beginscene=new BeginScene(uicontroller);
    connect(beginscene,&BeginScene::createplayscene,this,&MainWindow::createplayscene,Qt::QueuedConnection);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit closeevent();
    event->accept();
}



MainWindow::~MainWindow()
{
    delete ui;
    delete keypresseater;
}

