#include "osmwindow.h"

#include <QtCore/QDebug>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

#include "osmtiles.h"


OsmWindow::OsmWindow(QWidget *parent, int zoom, int x, int y) : QWidget(parent), zoom(zoom), x(x), y(y)
{
    tiles = new OsmTiles(this);
    setAttribute(Qt::WA_AcceptTouchEvents);
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

void OsmWindow::wheelEvent(QWheelEvent *ev)
{
    if (-60 < ev->angleDelta().y() && ev->angleDelta().y() < 60)
        ev->ignore();
    else {
        if (ev->angleDelta().y() > 0) {
            zoom++;
            x *= 2;
            y *= 2;
        } else {
            zoom--;
            x /= 2;
            y /= 2;
        }
        update();
    }
};

void OsmWindow::tabletEvent(QTabletEvent *ev) {
    qDebug() << ev;
    ev->ignore();
};

void OsmWindow::touchEvent(QTouchEvent *ev) {
    qDebug() << ev;
    ev->ignore();
};

bool OsmWindow::event(QEvent *ev)
{
    switch (ev->type()) {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        case QEvent::TouchCancel:
        {
            touchEvent((QTouchEvent*)ev);
            return ev->isAccepted();
            break;
        }
        default:
        {
            return QWidget::event(ev);
            break;
        }
    }
};
