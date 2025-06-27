#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H
#include<QGraphicsView>
#include<QWheelEvent>
#include<QGraphicsScene>
class CustomGraphicsView: public QGraphicsView{
    Q_OBJECT
protected:
    void wheelEvent(QWheelEvent *event) override;
public:
    explicit CustomGraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);
};
#endif // CUSTOMGRAPHICSVIEW_H
