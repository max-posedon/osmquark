#include "osmwindow.h"

#include <QtCore/QDebug>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

#include "osmtiles.h"


OsmWindow::OsmWindow(QWidget *parent, int zoom, int x, int y) : QWidget(parent), zoom(zoom), x(x), y(y)
{
    tiles = new OsmTiles(this);
};

void OsmWindow::paintEvent(QPaintEvent *event)
{
    static int i = 0;
    qDebug() << i++ << event->rect();

    int n = 1 << zoom;
    int min_nx = x/256;
    int min_ny = y/256;
    int max_nx = (x+event->rect().width()-1)/256+1;
    int max_ny = qMin(n, (y+event->rect().height()-1)/256+1);

    QPainter painter(this);
    for (int ix=min_nx; ix<max_nx; ix++)
        for (int iy=min_ny; iy<max_ny; iy++)
            painter.drawImage(-x+ix*256, -y+iy*256, tiles->getTile(zoom, ix % n, iy));
};
