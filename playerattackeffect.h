#ifndef PLAYERATTACKEFFECT_H
#define PLAYERATTACKEFFECT_H

#include "attackeffect.h"

class PlayerAttackEffect : public AttackEffect
{
private:
    const int totalframesnum=12;
public:
    PlayerAttackEffect(UIController *uicontroller,bool direction,double x,double y,double width,double height);
    bool showpicture() override;
};

#endif // PLAYERATTACKEFFECT_H
