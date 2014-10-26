#include <QtCore/QLibraryInfo>
#include <QtCore/QTimer>
#include <QtCore/QTranslator>
#include <QtCore/QCommandLineParser>
#include <QtWidgets/QApplication>

#include "osmwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setOrganizationName("max_posedon");
    QCoreApplication::setOrganizationDomain("maxposedon.org");

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);
    QTranslator appTranslator;
    appTranslator.load(QCoreApplication::applicationName() + "_" + QLocale::system().name());
    app.installTranslator(&appTranslator);

    QCoreApplication::setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, false);

    QCommandLineOption zoomOption(QStringList() << "z" << "zoom", QObject::tr("Zoom Level"), "zoom", "0");
    QCommandLineOption xOption("x", QObject::tr("X offset"), "x", "0");
    QCommandLineOption yOption("y", QObject::tr("Y offset"), "y", "0");

    QCommandLineParser parser;
    parser.setApplicationDescription(QObject::tr("very simple open street map app"));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(zoomOption);
    parser.addOption(xOption);
    parser.addOption(yOption);
    parser.process(app);

    int zoom = parser.value(zoomOption).toInt();
    int x = parser.value(xOption).toInt();
    int y = parser.value(yOption).toInt();

    OsmWindow window(0, zoom, x, y);
    window.show();

    return app.exec();
}
