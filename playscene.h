#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "scene.h"
#include "uicontroller.h"
#include "Level.h"
#include "sqlitedb.h"
class UIController;
class Level;

class PlayScene : public Scene
{
    Q_OBJECT

public:
    /*
     * @param uic      已构造并初始化好的 UIController
     * @param levelId  要运行的关卡编号（1 或 2）
     */
    PlayScene(UIController *uic, int levelId);

    ~PlayScene() override;
    Level *m_level;  ///< 延迟实例化的关卡对象
    Level* level() { return m_level; }
    void startLevel();
signals:
    void createplayscene(int id);
    void createfailscene();
    void closeeventlevel();
public slots:
    //启动关卡的入口（LevelId=1 由BeginScene开始按钮调用，=2 由内部定时器延迟2秒调用）
    void levelCompleted();
    void levelfail();
    void closeevent();

private:
    UIController *m_uic;    ///< 场景绘制与更新控制器
    int           m_levelId;///< 关卡编号
    bool          m_started;///< 防止重复启动
};

#endif // PLAYSCENE_H
