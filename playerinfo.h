#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include "elements.h"
#include "Player.h"
class PlayerInfo : public Elements
{
public:
    PlayerInfo(UIController *uicontroller,Player *player);
private:
    Player *player;
    bool showpicture() override;
    QGraphicsPixmapItem *avatar,*fastmovepic,*addbloodpic;
    QGraphicsRectItem *health1,*health2;
    QGraphicsTextItem *addbloodcd,*fastmovecd;
    QGraphicsRectItem *fastmovebound,*addbloodbound;
};

#endif // PLAYERINFO_H
