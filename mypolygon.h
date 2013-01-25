#ifndef MYPOLYGON_H
#define MYPOLYGON_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QPainter>
#include <QGraphicsSceneContextMenuEvent>
#include <QDebug>

#include <mypoint.h>
#include <mypattern.h>

class MyPolygon : public QGraphicsItem
{
public:
    MyPolygon(MyPattern *pattern, QMenu *contextMenu = 0);
    QRectF boundingRect() const;

    void setColor(QColor color);
    void setPolygon(QPolygonF &poly);
    void adjust();
    void addPoint(MyPoint *point);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    QMenu *myContextMenu;
    MyPattern *pattern_;
    QList<MyPoint*> points_;

    QColor color_;
};


#endif // MYPOLYGON_H
