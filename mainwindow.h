#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "point2d.h"
#include "edge.h"
#include "meshing.h"
#include "patternscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QList<Point2D*> currentPoly;
    QList< QList<Point2D*> > polys;
    PatternScene *scene;
    int n;
    QList<Point2D*> points;


    QList<QGraphicsPolygonItem*> polyDraw;

private slots:
    void pressTest();
    void addPoint(QPointF pt);
    void closePoly();
};

#endif // MAINWINDOW_H