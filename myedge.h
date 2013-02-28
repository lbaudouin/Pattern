#ifndef MYEDGE_H
#define MYEDGE_H

#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QObject>

#include <QDebug>

class MyPoint;
class MyEdge;

#include "mypoint.h"
#include "mylink.h"
#include "mypattern.h"

class MyEdgeObject : public QObject
{
    Q_OBJECT
public:
    MyEdgeObject() : show_(false) {}
    bool show() { return show_; }
    bool inverse() { return inverse_; }
private:
    bool show_;
    bool inverse_;
public slots:
    void showStich(){ show_ = true; }
    void hideStich(){ show_ = false; }
    void setStichVisible(bool visibility) { show_ = visibility; }
    void toggle() { inverse_ = !inverse_; }
};

class MyEdge : public QGraphicsItem
{
public:
    explicit MyEdge(MyPoint *src, MyPoint *dest, MyPattern *pattern, int edgeID, QMenu *contextMenu);
    QRectF boundingRect() const;

    QPointF getSourcePoint();
    QPointF getDestPoint();
    MyPoint* getSource();
    MyPoint* getDest();

    QPointF proj(QPointF p);
    double distance(QPointF p);

    QPointF selectedPoint();

    void adjust();

    MyEdgeObject* object;

    void setLink(MyLink *link){
        link_ = link;
    }

    enum { Type = UserType + 2 };
    int type() const { return Type; }

    void remove();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    MyPoint *src_,*dest_;
    QMenu *myContextMenu;
    QPointF selectedPoint_;
    MyEdge *stitchWith_;
    MyLink *link_;
    MyPattern *pattern_;
    int edgeID_;
    
};

#endif // MYEDGE_H
