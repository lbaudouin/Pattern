#include "myedge.h"

MyEdge::MyEdge(MyPoint *src, MyPoint *dest, MyPattern *pattern, int edgeID, QMenu *contextMenu) : object(new MyEdgeObject), stitchWith_(0), link_(0), pattern_(pattern), edgeID_(edgeID)
{
    src_ = src;
    dest_ = dest;
    src_->setDestEdge(this);
    dest_->setSrcEdge(this);
    myContextMenu = contextMenu;
    setZValue(1);
    adjust();
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void MyEdge::remove()
{
    src_ = 0;
    dest_ = 0;
    if(scene())
        scene()->removeItem(this);
}

void MyEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);
    if(isSelected()){
        painter->setPen( QPen(Qt::red,3) );
        painter->drawLine(src_->pos(),dest_->pos());
    }else{
        painter->setPen(Qt::darkGreen);
        painter->drawLine(src_->pos(),dest_->pos());
    }
}

QRectF MyEdge::boundingRect() const
{
    if (!src_ || !dest_)
        return QRectF();

    //qreal penWidth = 1;
    //qreal extra = (penWidth + arrowSize) / 2.0;
    qreal extra = 1.0;

    return QRectF(src_->pos(), QSizeF(dest_->x() - src_->x(),
                                      dest_->y() - src_->y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void MyEdge::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    if(distance(event->scenePos())<10.0){
        selectedPoint_ = proj(event->scenePos());
        myContextMenu->exec(event->screenPos());
    }else{
        QGraphicsItem::contextMenuEvent(event);
    }
}

QPointF MyEdge::getSourcePoint()
{
    return src_->getPoint();
}

QPointF MyEdge::getDestPoint()
{
    return dest_->getPoint();
}

double MyEdge::distance(QPointF pt)
{
    if (!src_ || !dest_)
        return 0.0;
    if(src_->pos()==dest_->pos())
        return QLineF(src_->pos(),pt).length();

    return QLineF(proj(pt),pt).length();
}


QPointF MyEdge::proj(QPointF pt)
{
    if (!src_ || !dest_)
        return QPointF();
    if(src_->pos()==dest_->pos())
        return src_->pos();


    QLineF line(src_->pos(),dest_->pos());
    QPointF p;

    QLineF normal = line.normalVector();
    normal.setP2( normal.p2() - normal.p1() + pt);
    normal.setP1( pt );
    line.intersect(normal,&p);
    return p;
}

QPointF MyEdge::selectedPoint()
{
    return selectedPoint_;
}

void MyEdge::adjust()
{
    prepareGeometryChange();
    if(link_!=0)
        link_->adjust();
}
