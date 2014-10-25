#ifndef OSMWINDOW_H
#define OSMWINDOW_H

#include <QtWidgets/QWidget>

class OsmTiles;
class QTouchEvent;

class OsmWindow: public QWidget
{
    Q_OBJECT

public:
    enum ZoomLevel {
        Minimal = 0,
        Maximum = 16
    };

public:
    OsmWindow(QWidget *parent = 0, int zoom = 0, int x = 0, int y = 0);

protected:
    virtual void paintEvent(QPaintEvent *ev);
    virtual void mouseMoveEvent(QMouseEvent *ev);
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void wheelEvent(QWheelEvent *ev);
    virtual void tabletEvent(QTabletEvent *ev);
    virtual void touchEvent(QTouchEvent *ev);
    virtual bool event(QEvent *ev);

private:
    OsmTiles *tiles;
    int zoom;
    int x;
    int y;
    int press_x;
    int press_y;
};

#endif
