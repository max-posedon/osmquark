#include <QtCore/QTimer>
#include <QtWidgets/QApplication>

#include "osmwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, false);
    QStringList args = app.arguments();
    int zoom = args.size() > 1 ? args.at(1).toInt() : 0;
    int x = args.size() > 3 ? args.at(2).toInt() : 0;
    int y = args.size() > 3 ? args.at(3).toInt() : 0;
    OsmWindow window(0, zoom, x, y);
    window.show();
    return app.exec();
}
