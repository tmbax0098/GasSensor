#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QFile>
#include <QLayout>
#include<QDebug>

#include<QSqlError>
#include <packet.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile File(":/Dark.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);


    packet_1.setNode(1);
    packet_2.setNode(2);
    packet_3.setNode(3);
    packet_4.setNode(4);
    packet_5.setNode(5);
    packet_6.setNode(6);



    timer.setInterval(1000);
    QObject::connect(&timer , &QTimer::timeout , [=](){
        ui->lblTime->setText(QDateTime::currentDateTime().time().toString());
    });
    timer.start(1000);


    QObject::connect(&passwordCertificateWindow, &PasswordCertificateWindow::login , &settingWindow , &SettingWindow::showFullScreen);
    QObject::connect(&passwordCertificateWindow, &PasswordCertificateWindow::login, &passwordCertificateWindow , &PasswordCertificateWindow::close);


    QObject::connect(ui->pushButtonNode1 , &QPushButton::clicked ,[=](){
        nodeWindow.setNode(1);
        nodeWindow.showFullScreen();
    });
    QObject::connect(ui->pushButtonNode2 , &QPushButton::clicked ,[=](){
        nodeWindow.setNode(2);
        nodeWindow.showFullScreen();
    });
    QObject::connect(ui->pushButtonNode3 , &QPushButton::clicked ,[=](){
        nodeWindow.setNode(3);
        nodeWindow.showFullScreen();
    });
    QObject::connect(ui->pushButtonNode4 , &QPushButton::clicked ,[=](){
        nodeWindow.setNode(4);
        nodeWindow.showFullScreen();
    });
    QObject::connect(ui->pushButtonNode5 , &QPushButton::clicked ,[=](){
        nodeWindow.setNode(5);
        nodeWindow.showFullScreen();
    });
    QObject::connect(ui->pushButtonNode6 , &QPushButton::clicked ,[=](){
        nodeWindow.setNode(7);
        nodeWindow.showFullScreen();
    });

    openDatabase();
    loadNodeSetting();

    //when packet recieved
    QObject::connect(&portManager , &PortManager::newPacket ,this, &MainWindow::manageNewPacket);


    timerDatabase.setInterval(60000);
    QObject::connect(&timerDatabase , &QTimer::timeout , [=](){
        saveRecord(packet_1);
        saveRecord(packet_2);
        saveRecord(packet_3);
        saveRecord(packet_4);
        saveRecord(packet_5);
        saveRecord(packet_6);
    });
    timerDatabase.start(60000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    database.close();
    QStringList list = QSqlDatabase::connectionNames();
    foreach (QString name,list) {
        qDebug()<<"Connection closed! "<<name;
        QSqlDatabase::removeDatabase(name);
    }
}


void MainWindow::on_btnSetting_clicked()
{

    passwordCertificateWindow.reset();
    passwordCertificateWindow.showFullScreen();
}

void MainWindow::on_btnAbout_clicked()
{
    aboutWindow.showFullScreen();
}

void MainWindow::openDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("GasSensor.db");
    bool ok = database.open();
    qDebug()<<"openDatabase ==> database is open state : "<<ok ;
}

void MainWindow::loadNodeSetting()
{
    if(database.isOpen()){
        QSqlQuery query;
        if(query.exec("select * from node_setting where 1")){
            while (query.next()) {
                qDebug()<<"data is "<<query.value(1).toInt()<<" active is " << query.value(1).toBool();

                switch (query.value(0).toInt()) {
                case 1:
                    packet_1.setMax(query.value(2).toInt());
                    packet_1.setMin(query.value(3).toInt());
                    ui->pushButtonNode1->setEnabled(query.value(1).toBool());
                    break;
                case 2:
                    packet_2.setMax(query.value(2).toInt());
                    packet_2.setMin(query.value(3).toInt());
                    ui->pushButtonNode2->setEnabled(query.value(1).toBool());
                    break;
                case 3:
                    packet_3.setMax(query.value(2).toInt());
                    packet_3.setMin(query.value(3).toInt());
                    ui->pushButtonNode3->setEnabled(query.value(1).toBool());
                    break;
                case 4:
                    packet_4.setMax(query.value(2).toInt());
                    packet_4.setMin(query.value(3).toInt());
                    ui->pushButtonNode4->setEnabled(query.value(1).toBool());
                    break;
                case 5:
                    packet_5.setMax(query.value(2).toInt());
                    packet_5.setMin(query.value(3).toInt());
                    ui->pushButtonNode5->setEnabled(query.value(1).toBool());
                    break;
                case 6:
                    packet_6.setMax(query.value(2).toInt());
                    packet_6.setMin(query.value(3).toInt());
                    ui->pushButtonNode6->setEnabled(query.value(1).toBool());
                    break;
                }
            }
        }else{
            qDebug()<<query.lastError().text()<<endl<<query.executedQuery();
        }
    }
}

void MainWindow::saveRecord(Packet &packet)
{
    if(database.isOpen()){
        QSqlQuery query;
        if(packet.getValid() && !packet.getSaved()){
            query.exec(packet.getQueryCommand());
        }
    }
}

void MainWindow::manageNewPacket(QString packet)
{
    Packet pak;
    pak.setPacket(packet);
    if(nodeWindow.isOpen() && nodeWindow.getNode() == pak.getNode()){
        nodeWindow.setNewPoint(pak);
    }
    if(pak.getValid()){
        switch (pak.getNode()) {
        case 1:
            packet_1.setPacket(packet);
            ui->progressBar->setValue(pak.getValue());
            break;
        case 2:
            packet_2.setPacket(packet);
            ui->progressBar_2->setValue(pak.getValue());
            break;
        case 3:
            packet_3.setPacket(packet);
            ui->progressBar_3->setValue(pak.getValue());
            break;
        case 4:
            packet_4.setPacket(packet);
            ui->progressBar_4->setValue(pak.getValue());
            break;
        case 5:
            packet_5.setPacket(packet);
            ui->progressBar_5->setValue(pak.getValue());
            break;
        case 6:
            packet_6.setPacket(packet);
            ui->progressBar_6->setValue(pak.getValue());
            break;
        default:
            break;
        }
    }

    //if(!packet_1.getWarning() &&
           // !packet_2.getWarning() &&
           // !packet_3.getWarning() &&
          //  !packet_4.getWarning() &&
        //    !packet_5.getWarning() &&
      //      !packet_6.getWarning()){

        //packet_1.alarmOff();
        //sleep(2000);

    //}

}
