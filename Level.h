// level.h
#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QTimer>
#include "uicontroller.h"
#include "character.h"
#include "Player.h"
#include "enemy1.h"
#include "boss.h"
#include "grounds.h"
#include <iterator>
#include "elements.h"
#include "gate.h"
#include "sqlitedb.h"
#include "playerinfo.h"
#include <QMessageBox>
class Level : public QObject
{
    Q_OBJECT
public:
    explicit Level(UIController* uicontroller, int id, bool readuser,QObject* parent = nullptr);
    ~Level();
    void InitializeLevel();
    function<bool(Character*)> checkifontheground;
signals:
    void levelCompleted();
    void levelfail();
public slots:
    void renderfunc();
    void addelementsslot(Elements *ele);
    void closeevent();
private:
    void setupConnections();
    void createLevelElements();
    void createEnemies(bool readuser,SqliteDB &db);
    void creategates();
    void saveToDatabase();

    UIController* m_uiController;
    int m_levelId;
    Player* m_player;
    QList<Character*> m_characters;
    QList<Enemy*> m_enemies;
    QList<Grounds*> m_grounds;
    QList<Elements*> m_elements;
    QList<Gate*> m_gate;
    QTimer* render;
    bool visitelements;
};

#endif // LEVEL_H
