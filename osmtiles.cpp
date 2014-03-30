#include "osmtiles.h"

#include <QtCore/QDebug>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

OsmTiles::OsmTiles(QObject *parent) : QObject(parent)
{
    connect(&manager, &QNetworkAccessManager::finished, this, &OsmTiles::downloadFinished);
}

void OsmTiles::startDownload(int zoom)
{
    int n = zoom == 0 ? 1 : 2 << (zoom-1);
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++) {
            const QString url = QString("http://a.tile.openstreetmap.by:3128/osmby-ru/%1/%2/%3.png").arg(zoom).arg(i).arg(j);
            QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));
            reply->setProperty("i", i);
            reply->setProperty("j", j);
        }
}

void OsmTiles::downloadFinished(QNetworkReply *reply)
{
    int i = reply->property("i").toInt();
    int j = reply->property("j").toInt();
    if (reply->error() == QNetworkReply::NoError) {
        tiles[i][j].load(reply, "PNG");
        qDebug() << reply->url() << reply->error() << QPair<int,int>(i,j) << tiles[i][j];
    }
}

const QImage OsmTiles::getTile(int i, int j)
{
    return tiles[i][j];
}
