#include "mainwindow.h"

#include <QApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
    QProcess process;
    process.start("sudo python pin.py PD14 0");
    process.waitForStarted();

    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
