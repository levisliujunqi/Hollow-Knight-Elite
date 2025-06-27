#include "customgraphicsview.h"
CustomGraphicsView::CustomGraphicsView(QGraphicsScene* scene,QWidget* parent)
    : QGraphicsView(parent){
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignLeft|Qt::AlignTop);
    //setBackgroundBrush(Qt::blue);
}
void CustomGraphicsView::wheelEvent(QWheelEvent *event){
    event->ignore();
}
