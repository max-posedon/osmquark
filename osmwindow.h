#ifndef OSMWINDOW_H
#define OSMWINDOW_H

#include <QtWidgets/QWidget>

class OsmTiles;

class OsmWindow: public QWidget
{
    Q_OBJECT

public:
    OsmWindow(QWidget *parent = 0, int zoom = 0, int x = 0, int y = 0);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    OsmTiles *tiles;
    int zoom;
    int x;
    int y;
};

#endif
