#include "settingnodewindow.h"
#include "ui_settingnodewindow.h"

#include <QFile>
#include<QDebug>
#include <QSqlQuery>
#include <QSqlError>

SettingNodeWindow::SettingNodeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingNodeWindow)
{
    ui->setupUi(this);

    QFile File(":/Dark.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);


    //    database = QSqlDatabase::addDatabase("QSQLITE");
    //    database.setDatabaseName("GasSensor.db");
    //    bool ok = database.open();
    //    qDebug()<<"database is open state : " << ok;



//    QSqlQuery query("select * from node_setting where 1");
//    if(query.exec()){
//        while (query.next()) {
//            switch (query.value(0).toInt()) {
//            case 1:
//                setButtonValue(ui->pbNode1 ,query.value(1).toInt());
//                break;
//            case 2:
//                setButtonValue(ui->pbNode2 ,query.value(1).toInt());
//                break;
//            case 3:
//                setButtonValue(ui->pbNode3 ,query.value(1).toInt());
//                break;
//            case 4:
//                setButtonValue(ui->pbNode4 ,query.value(1).toInt());
//                break;
//            case 5:
//                setButtonValue(ui->pbNode5 ,query.value(1).toInt());
//                break;
//            case 6:
//                setButtonValue(ui->pbNode6 ,query.value(1).toInt());
//                break;
//            }
//        }
//    }
}

SettingNodeWindow::~SettingNodeWindow()
{
    delete ui;
}

void SettingNodeWindow::setButtonValue(QPushButton *btn, int value)
{
    if(value == 0){
        btn->setStyleSheet("background-color : #ff0000;");
    }else{
        btn->setStyleSheet("background-color : #00ff00;");
    }
}

void SettingNodeWindow::toggleButtonStatus(QPushButton *btn)
{
    QString node = btn->text().split(" ")[1];
    int value = 0;
    qDebug()<<"select value from node_setting where id=" + node + " limit 1";

    QSqlQuery query("select value from node_setting where id=" + node + " limit 1");


    if(query.exec()){
        if(query.first()){
            value = query.value(0).toInt();
            query.exec("update node_setting set value="+QString::number(value == 1 ? 0 : 1)+" where id="+ node);
            if(value > 0){
                setButtonValue(btn,0);
            }else{
                setButtonValue(btn,1);
            }
        }
    }else{
        qDebug()<<"ERROR IS : "<<query.lastError().text();
    }
}

void SettingNodeWindow::showEvent(QShowEvent *event)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("GasSensor.db");
    bool ok = database.open();
    qDebug()<<"database is open state : " + this->windowTitle() + " ===> " << ok;

    if(ok){
        toggleButtonStatus(ui->pbNode1);
        toggleButtonStatus(ui->pbNode2);
        toggleButtonStatus(ui->pbNode3);
        toggleButtonStatus(ui->pbNode4);
        toggleButtonStatus(ui->pbNode5);
        toggleButtonStatus(ui->pbNode6);
    }
}

void SettingNodeWindow::closeEvent(QCloseEvent *event)
{
    closeAllconnection();
    return;
}
void SettingNodeWindow::closeAllconnection()
{
    database.close();
    QStringList list = QSqlDatabase::connectionNames();
    foreach (QString name,list) {
        qDebug()<<"Connection closed! "<<name;
        QSqlDatabase::removeDatabase(name);
    }
}

void SettingNodeWindow::on_pbNode1_clicked()
{
    toggleButtonStatus(ui->pbNode1);
}

void SettingNodeWindow::on_pbNode2_clicked()
{
    toggleButtonStatus(ui->pbNode2 );
}

void SettingNodeWindow::on_pbNode3_clicked()
{
    toggleButtonStatus(ui->pbNode3 );
}

void SettingNodeWindow::on_pbNode4_clicked()
{
    toggleButtonStatus(ui->pbNode4 );
}

void SettingNodeWindow::on_pbNode5_clicked()
{
    toggleButtonStatus(ui->pbNode5 );
}

void SettingNodeWindow::on_pbNode6_clicked()
{
    toggleButtonStatus(ui->pbNode6 );
}
