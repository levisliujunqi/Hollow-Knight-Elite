#ifndef KEYPRESSEATER_H
#define KEYPRESSEATER_H
#include <QEvent>
#include <QObject>
#include <QKeyEvent>
#include <queue>
#include <set>
using namespace std;
class KeyPressEater:public QObject
{
    Q_OBJECT
public:
    KeyPressEater();
    bool eventFilter(QObject *obj, QEvent *event) override;
signals:
    void KeyPress(int key);
    void KeyReelase(int key);
};

#endif // KEYPRESSEATER_H
