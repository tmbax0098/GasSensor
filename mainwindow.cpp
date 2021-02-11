#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QFile>
#include <QLayout>
#include <QDebug>
#include <QSqlError>
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
        manageAlarm();
    });
    timer.start(1000);


    QObject::connect(&passwordCertificateWindow, &PasswordCertificateWindow::login , [=](){
        switch (certificateMode) {
        case SETTING:
            database = tools.openDatabase();
            settingWindow.showFullScreen();
            break;
        case RESET_FACTORY:
            messageWindow.showMessage(tools.resetFactory());
            database = tools.openDatabase();
            break;
        }
    });
    QObject::connect(&passwordCertificateWindow, &PasswordCertificateWindow::login, &passwordCertificateWindow , &PasswordCertificateWindow::close);

    QObject::connect(&nodeWindow , &NodeWindow::loadArchive,this , &MainWindow::getNodeArchive);
    QObject::connect(&nodeWindow , &NodeWindow::saveNodeSetting,this , &MainWindow::saveNodeSetting);


    QObject::connect(&settingWindow , &SettingWindow::resetFactory , [=](){

        certificateMode = RESET_FACTORY;
        passwordCertificateWindow.reset();
        passwordCertificateWindow.showFullScreen();

    });

    QObject::connect(&settingWindow , &SettingWindow::showMessage ,&messageWindow , &MessageWindow::showMessage);


    QObject::connect(ui->pushButtonNode1 , &QPushButton::clicked ,[=](){
        nodeWindow.setNode(&packet_1);
        nodeWindow.showFullScreen();
    });
    QObject::connect(ui->pushButtonNode2 , &QPushButton::clicked ,[=](){
        nodeWindow.setNode(&packet_2);
        nodeWindow.showFullScreen();
    });
    QObject::connect(ui->pushButtonNode3 , &QPushButton::clicked ,[=](){
        nodeWindow.setNode(&packet_3);
        nodeWindow.showFullScreen();
    });
    QObject::connect(ui->pushButtonNode4 , &QPushButton::clicked ,[=](){
        nodeWindow.setNode(&packet_4);
        nodeWindow.showFullScreen();
    });
    QObject::connect(ui->pushButtonNode5 , &QPushButton::clicked ,[=](){
        nodeWindow.setNode(&packet_5);
        nodeWindow.showFullScreen();
    });
    QObject::connect(ui->pushButtonNode6 , &QPushButton::clicked ,[=](){
        nodeWindow.setNode(&packet_6);
        nodeWindow.showFullScreen();
    });

    loadNodeSetting();

    //when packet recieved
    QObject::connect(&portManager , &PortManager::newPacket ,this, &MainWindow::manageNewPacket);


    QObject::connect(&settingWindow , &SettingWindow::onClose , [=](){
        loadNodeSetting();
    });

    timerDatabase.setInterval(tools.getSaveTimer());
    QObject::connect(&timerDatabase , &QTimer::timeout , [=](){
        saveRecord(packet_1);
        saveRecord(packet_2);
        saveRecord(packet_3);
        saveRecord(packet_4);
        saveRecord(packet_5);
        saveRecord(packet_6);
        removeOldRecords();
    });
    timerDatabase.start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    database.close();
    tools.closeAllConnections();
}

void MainWindow::on_btnSetting_clicked()
{
    QCloseEvent *event;
    closeEvent(event);
    certificateMode = SETTING;
    passwordCertificateWindow.reset();
    passwordCertificateWindow.showFullScreen();
}

void MainWindow::on_btnAbout_clicked()
{
    aboutWindow.showFullScreen();
}

void MainWindow::loadNodeSetting()
{
    if(!database.isOpen()){
        database = tools.openDatabase();
    }
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

            query.clear();
            if(query.exec("SELECT * FROM ports WHERE 1")){
                if(query.next()){
                    input1 = query.value(0).toInt();
                    input2 = query.value(1).toInt();
                    output = query.value(2).toInt();
                    alarm = query.value(3).toInt();
                    pinManager.createSettingFile(input1 , input2 ,output , alarm);
                }
            }
        }else{
            qDebug()<<query.lastError().text()<<endl<<query.executedQuery();
        }
    }
}

void MainWindow::manageAlarm()
{
    bool p1 =false;
    bool p2=false;
    bool p3=false;
    bool p4=false;
    bool p5=false;
    bool p6=false;
    if(packet_1.getValid() && packet_1.getWarning()){
        p1 = true;
    }
    if(packet_2.getValid() && packet_2.getWarning()){
        p2 = true;
    }
    if(packet_3.getValid() && packet_3.getWarning()){
        p3 = true;
    }
    if(packet_4.getValid() && packet_4.getWarning()){
        p4 = true;
    }
    if(packet_5.getValid() && packet_5.getWarning()){
        p5 = true;
    }
    if(packet_6.getValid() && packet_6.getWarning()){
        p6 = true;
    }
    if(alarm){
        if(p1 || p2 || p3 || p4 || p5 || p6){
            pinManager.alarmOn();
        }else{
            pinManager.alarmOff();
        }
    }else{
        pinManager.alarmOff();
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

void MainWindow::removeOldRecords()
{
    if(database.isOpen()){
        QSqlQuery query;
        QDateTime dt = QDateTime::currentDateTime();
        dt = dt.addSecs(-24*60*60);
        query.exec("DELETE FROM `node` WHERE `datetime` < \'" + dt.toString("yyyy-MM-dd HH:mm:ss") +"\'");
    }
}

void MainWindow::getNodeArchive(int node)
{
    QList<QPointF> list;
    QSqlQuery query("SELECT datetime , value FROM node WHERE id=" + QString::number(node) + " ORDER BY datetime ");
    if(query.exec()){
        while (query.next()) {
            list.append(
                        QPointF(
                            query.value(0).toDateTime().toMSecsSinceEpoch() ,
                            query.value(1).toDouble()
                            )
                        );
        }
    }else{
        qDebug()<<"ERROR : "<<query.lastError().text()<<endl;
    }
    query.clear();

    nodeWindow.setArchive(list);

}

void MainWindow::saveNodeSetting(Packet *packet)
{
    QSqlQuery query;
    if(database.isOpen()){

        query.prepare("UPDATE node_setting SET up=" +
                      QString::number(packet->getMax()) +
                      " , down="+ QString::number(packet->getMin()) +
                      "WHERE id=" + QString::number(packet->getNode()));

        query.exec();
        query.clear();
    }
    loadNodeSetting();
}

void MainWindow::manageNewPacket(QString packet)
{

//    qDebug()<<"new packet ==> "<<packet;

    Packet pak;
    pak.setPacket(packet);
    if(nodeWindow.isOpen() && nodeWindow.getNode()->getNode() == pak.getNode()){
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

}
