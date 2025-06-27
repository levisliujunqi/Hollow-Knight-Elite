#include "keypresseater.h"

KeyPressEater::KeyPressEater() {}
bool KeyPressEater::eventFilter(QObject *obj, QEvent *event){
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->isAutoRepeat()) return true;
        int k=keyEvent->key();
        emit KeyPress(k);
        return true;
    }else if(event->type()==QEvent::KeyRelease){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->isAutoRepeat()) return true;
        int k=keyEvent->key();
        emit KeyReelase(k);
        return true;
    }
    return QObject::eventFilter(obj, event);
}
