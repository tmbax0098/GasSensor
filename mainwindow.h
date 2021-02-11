#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tools.h"

#include <QMainWindow>
#include <QTimer>
#include <aboutwindow.h>
#include <messagewindow.h>
#include <nodesetting.h>
#include <nodewindow.h>
#include <packet.h>
#include <passwordcertificatewindow.h>
#include <pinmanager.h>
#include <portmanager.h>
#include <settingwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:

    void manageNewPacket(QString packet);

    void on_btnSetting_clicked();

    void on_btnAbout_clicked();

private:
    Ui::MainWindow *ui;

    enum CertificateMode{
        SETTING,
        RESET_FACTORY
    };

    CertificateMode certificateMode;

    QTimer timer;
    QTimer timerDatabase;

    Tools tools;
    PinManager pinManager;
    MessageWindow messageWindow;
    SettingWindow settingWindow;
    AboutWindow aboutWindow;
    PasswordCertificateWindow passwordCertificateWindow;
    NodeWindow nodeWindow;
    PortManager portManager;
    QSqlDatabase database;

    void openDatabase();
    void loadNodeSetting();
    void manageAlarm();

    Packet packet_1;
    Packet packet_2;
    Packet packet_3;
    Packet packet_4;
    Packet packet_5;
    Packet packet_6;

    bool input1= false;
    bool input2= false;
    bool output= false;
    bool alarm= false;

    void saveRecord(Packet &packet);
    void removeOldRecords();
    void getNodeArchive(int node);
    void saveNodeSetting(Packet *packet);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
