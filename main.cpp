#include "mainwindow.h"

#include <QApplication>
//#include <QProcess>

int main(int argc, char *argv[])
{
//    QProcess process;
//    process.start("echo 12345678 | sudo python3 /home/koorosh/GasSensor/pin.py PA20 1");
//    if(process.waitForStarted(3000)){
//        if(process.waitForFinished(5000)){
//            qDebug()<<"proccess finish shod :D";
//        } else{
//            qDebug()<<"proccess finish nashod!";
//        }
//    }else{
//        qDebug()<<"proccess start nashod!";
//    }

    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
