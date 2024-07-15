#include <QApplication>
#include <QFile>
#include <QTextStream>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file(":/Style/style.qss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        app.setStyleSheet(stream.readAll());
    }
    MainWindow w;
    w.show();

    return app.exec();
}
