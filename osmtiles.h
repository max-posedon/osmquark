#ifndef OSMTILES_H
#define OSMTILES_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtGui/QImage>


class OsmTiles: public QObject
{
    Q_OBJECT

public:
    OsmTiles(QObject *parent = 0);
    void startDownload(int zoom = 0);
    const QImage getTile(int i = 0, int j = 0);

private slots:
    void downloadFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager manager;
    QMap<int, QMap<int, QImage> > tiles;
};


#endif
