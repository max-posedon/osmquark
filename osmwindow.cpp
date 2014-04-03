#include "osmwindow.h"

#include <QtCore/QDebug>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

#include "osmtiles.h"


OsmWindow::OsmWindow(QWidget *parent, int zoom, int x, int y) : QWidget(parent), zoom(zoom), x(x), y(y)
{
    tiles = new OsmTiles(this);
};

void OsmWindow::paintEvent(QPaintEvent *ev)
{
    static int i = 0;
    qDebug() << i++ << ev->rect();

    int n = 1 << zoom;
    int min_nx = x/256;
    int min_ny = y/256;
    int max_nx = (x+ev->rect().width()-1)/256+1;
    int max_ny = qMin(n, (y+ev->rect().height()-1)/256+1);

    QPainter painter(this);
    for (int ix=min_nx; ix<max_nx; ix++)
        for (int iy=min_ny; iy<max_ny; iy++)
            painter.drawImage(-x+ix*256, -y+iy*256, tiles->getTile(zoom, ix % n, iy));
};

void OsmWindow::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() == Qt::LeftButton) {
        x -= ev->x() - press_x;
        y -= ev->y() - press_y;
        press_x = ev->x();
        press_y = ev->y();
        update();
    } else
        ev->ignore();
};

void OsmWindow::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        press_x = ev->x();
        press_y = ev->y();
    } else
        ev->ignore();
};
