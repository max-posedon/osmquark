#include "osmtiles.h"

#include <QtCore/QDebug>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

OsmTiles::OsmTiles(QObject *parent) : QObject(parent)
{
    cache.setCacheDirectory("cache");
    manager.setCache(&cache);
    connect(&manager, &QNetworkAccessManager::finished, this, &OsmTiles::downloadFinished);
}

void OsmTiles::startDownload(int zoom, int x, int y)
{
    const QString url = QString("http://a.tile.openstreetmap.by:3128/osmby-ru/%1/%2/%3.png").arg(zoom).arg(x).arg(y);
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));
    reply->setProperty("zoom", zoom);
    reply->setProperty("x", x);
    reply->setProperty("y", y);
}

void OsmTiles::downloadFinished(QNetworkReply *reply)
{
    int zoom = reply->property("zoom").toInt();
    int x = reply->property("x").toInt();
    int y = reply->property("y").toInt();
    if (reply->error() == QNetworkReply::NoError) {
        tiles[zoom][x][y].load(reply, "PNG");
        qDebug() << reply->url() << reply->error() << zoom << x << y << tiles[zoom][x][y];
    } else
        qDebug() << reply->url() << reply->error() << zoom << x << y;
}

const QImage OsmTiles::getTile(int zoom, int x, int y)
{
    if (tiles.contains(zoom))
        if (tiles.value(zoom).contains(x))
            if (tiles.value(zoom).value(x).contains(y))
                return tiles.value(zoom).value(x).value(y);
    startDownload(zoom, x, y);
    return tiles[zoom][x][y];
}
