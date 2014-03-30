#include "osmwindow.h"

#include <QtCore/QDebug>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

#include "osmtiles.h"


OsmWindow::OsmWindow(QWidget *parent, int zoom) : QWidget(parent), zoom(zoom)
{
    tiles = new OsmTiles(this);
};

void OsmWindow::paintEvent(QPaintEvent *event)
{
    static int i = 0;
    qDebug() << i++ << event->rect();

    int n = 1 << zoom;
    int nx = (event->rect().width()-1)/256+1;
    int ny = qMin(n, (event->rect().height()-1)/256+1);

    QPainter painter(this);
    for (int x=0; x<nx; x++)
        for (int y=0; y<ny; y++)
            painter.drawImage(x*256, y*256, tiles->getTile(zoom, x % n, y));
};
