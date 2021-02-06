#include "mainwindow.h"

#include <QApplication>
#include <QProcess>
//#include <QThread>

int main(int argc, char *argv[])
{

//    QThread::msleep(3000);
    QProcess process;
    process.start("echo 12345678 | sudo python pin.py PD14 0");
    process.waitForStarted();

    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
