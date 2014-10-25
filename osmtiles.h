#ifndef OSMTILES_H
#define OSMTILES_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkDiskCache>
#include <QtGui/QImage>

typedef QMap<int, QImage> TilesY;
typedef QMap<int, TilesY> TilesXY;
typedef QMap<int, TilesXY> TilesZoomXY;

class OsmTiles: public QObject
{
    Q_OBJECT

public:
    OsmTiles(QObject *parent = 0);
    const QImage getTile(int zoom = 0, int x = 0, int y = 0);

private slots:
    void downloadFinished(QNetworkReply *reply);
    void startDownload(int zoom = 0, int x = 0, int y = 0);

private:
    QNetworkAccessManager manager;
    QNetworkDiskCache cache;
    TilesZoomXY tiles;
};


#endif
