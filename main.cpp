#include <QtCore/QTimer>
#include <QtWidgets/QApplication>

//#include "osmtiles.h"
#include "osmwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    //OsmTiles tiles(&app);
    QStringList args = app.arguments();
    int zoom = args.size() > 1 ? args.at(1).toInt() : 0;
    //tiles.startDownload(zoom);
    //QTimer::singleShot(1000, &app, SLOT(quit()));
    OsmWindow window(0, zoom);
    window.show();
    return app.exec();
}
