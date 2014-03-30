#include <QtCore/QTimer>
#include <QtWidgets/QApplication>

#include "osmwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStringList args = app.arguments();
    int zoom = args.size() > 1 ? args.at(1).toInt() : 0;
    OsmWindow window(0, zoom);
    window.show();
    return app.exec();
}
