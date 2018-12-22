#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQuickView viewer;

    viewer.setSource(QUrl("qrc:/main.qml"));
    viewer.show();

    return app.exec();
}
