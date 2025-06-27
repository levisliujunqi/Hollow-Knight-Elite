#include "attackeffect.h"

AttackEffect::AttackEffect(UIController *uicontroller,bool direction,double x,double y,double width,double height):Elements(uicontroller),direction(direction),nowframe(0),item(nullptr) {

}

bool AttackEffect::showpicture(){
    return false;
}
