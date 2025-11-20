#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [](QObject *obj, const QUrl &objUrl) {
            if (!obj && objUrl.toString().endsWith("Main.qml"))
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.loadFromModule("Mastery", "Main");

    return app.exec();
}
