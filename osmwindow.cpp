#include "osmwindow.h"

#include <QtCore/QDebug>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

#include "osmtiles.h"


OsmWindow::OsmWindow(QWidget *parent, int zoom) : QWidget(parent), zoom(zoom)
{
    tiles = new OsmTiles(this);
    tiles->startDownload(zoom);
};

void OsmWindow::paintEvent(QPaintEvent *event)
{
    static int i = 0;
    qDebug() << i++ << event->rect();

    int n = zoom == 0 ? 1 : 2 << (zoom-1);

    QPainter painter(this);
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            painter.drawImage(i*256, j*256, tiles->getTile(i,j));
};
