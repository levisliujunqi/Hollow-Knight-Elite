#include "playscene.h"

#include <QTimer>
#include <QFont>
#include <QColor>

PlayScene::PlayScene(UIController *uic, int levelId)
    :m_uic(uic)
    , m_levelId(levelId)
    , m_level(nullptr)
    , m_started(false)
{
    //清空旧场景
    m_uic->clear();
    if (m_levelId == 2) {
        //先画过渡背景并显示文字
        m_uic->SetBackgroundColor(Qt::black);
        QPixmap bg(":/res/next_level.png");
        m_uic->SetBackgroundPicture(bg);//放一张类似于：恭喜通过第一关的图片
        // 2 秒后自动启动第 2 关
        QTimer::singleShot(2000, this, &PlayScene::startLevel);
    }
    // 如果是 LevelId == 1，则等待外部调用 startLevel()
}

PlayScene::~PlayScene()
{
    delete m_level;
}
void PlayScene::levelCompleted(){
    QTimer::singleShot(1000,this,[this](){
        emit createplayscene(m_levelId+1);
    });
}
void PlayScene::levelfail(){
    QTimer::singleShot(1000,this,[this](){
        emit createfailscene();
    });
}

void PlayScene::closeevent()
{
    emit closeeventlevel();
}
void PlayScene::startLevel()
{
    m_uic->clear();
    if (m_started) return;
    m_started = true;
    vector<vector<string>> result;
    SqliteDB db(m_uic->getnowdir()+"/database.sqlite");
    vector<string> column={"class"};
    result=db.query("select class from user where levelid="+to_string(m_levelId)+";",column);
    if(result.empty()){
        //实例化 Level，并在其构造函数里完成所有绘制与信号连接
        m_level = new Level(m_uic, m_levelId,0);
    }else{
        int reply=QMessageBox::question(nullptr,"询问","检测到存档，是否要加载存档？",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes){
            m_level = new Level(m_uic, m_levelId,1);
        }else{
            db.excusesql(QString::fromStdString("DELETE FROM user where levelid="+to_string(m_levelId)+";"));
            m_level = new Level(m_uic, m_levelId,0);
        }
    }
    connect(m_level,&Level::levelCompleted,this,&PlayScene::levelCompleted);
    connect(m_level,&Level::levelfail,this,&PlayScene::levelfail);
    connect(this,&PlayScene::closeeventlevel,m_level,&Level::closeevent);
}
