#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QSet>
#include "character.h"
class Player : public Character{
    Q_OBJECT
public:
    Player(UIController *uicontroller,double maxhealth,double health,double ad,double movev,double fastmovev,double jumpv,int attackdelay,int fastmovedelay,int attackpretime,double x,double y,double width,double height,int addbloodcd,int preattack,int prefastmove,int preaddblood,QPixmap &img,function<bool(Character*)> checkifontheground);
    ~Player();
    void showstillpicture() override;
    void showwalkpicture(int frame) override;
    void showattackpicture(int frame) override;
    void showfastmovepicture(int frame) override;
public slots:
    void keypress(int key);
    void keyrelease(int key);
private:
    QTimer* moveleftTimer;
    QTimer* moverightTimer;
    QTimer* jumpTimer;
    QTimer* attackTimer;
    QTimer* dropTimer;
    QTimer* fastmoveTimer;
};

#endif // PLAYER_H
