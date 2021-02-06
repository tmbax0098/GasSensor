#include "settingportwindow.h"
#include "ui_settingportwindow.h"

#include <QFile>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

SettingPortWindow::SettingPortWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingPortWindow)
{
    ui->setupUi(this);

    QFile File(":/Dark.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);

}

SettingPortWindow::~SettingPortWindow()
{
    delete ui;
}


void SettingPortWindow::setButtonValue(QPushButton *btn, int value)
{
    if(value == 0){
        btn->setStyleSheet("background-color : #ff0000;");
    }else{
        btn->setStyleSheet("background-color : #00ff00;");
    }
}

void SettingPortWindow::closeEvent(QCloseEvent *event)
{
    database.close();
    QStringList list = QSqlDatabase::connectionNames();
    foreach (QString name,list) {
        qDebug()<<"Connection closed! "<<name;
        QSqlDatabase::removeDatabase(name);
    }
}

void SettingPortWindow::showEvent(QShowEvent *event)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("GasSensor.db");
    bool ok = database.open();
    qDebug()<<"database is open state : "<<ok ;


    if(ok){
        QSqlQuery query("SELECT * FROM ports WHERE 1");
        if(query.exec()){
            if(query.next()){
                setButtonValue(ui->pushButtonInput1,query.value(0).toInt());
                setButtonValue(ui->pushButtonInput2,query.value(1).toInt());
                setButtonValue(ui->pushButtonOutput,query.value(2).toInt());
                setButtonValue(ui->pushButtonAlarm,query.value(3).toInt());
            }
        }else{
            qDebug()<<query.lastError().text();
        }
    }
}

void SettingPortWindow::on_pushButtonInput1_clicked()
{
    QSqlQuery query("select * from ports where 1 limit 1");
    if(query.exec()){
        if(query.first()){
            int value = query.value(0).toInt();
            if(value > 0){
                value = 0;
            }else{
                value = 1;
            }
            setButtonValue(ui->pushButtonInput1,value);
            query.exec("update ports set first=" + QString::number(value));
        }
    }
}

void SettingPortWindow::on_pushButtonInput2_clicked()
{
    QSqlQuery query("select * from ports where 1 limit 1");
    if(query.exec()){
        if(query.first()){
            int value = query.value(1).toInt();
            if(value > 0){
                value = 0;
            }else{
                value = 1;
            }
            setButtonValue(ui->pushButtonInput2,value);
            query.exec("update ports set second=" + QString::number(value));
        }
    }
}

void SettingPortWindow::on_pushButtonAlarm_clicked()
{
    QSqlQuery query("select * from ports where 1 limit 1");
    if(query.exec()){
        if(query.first()){
            int value = query.value(3).toInt();
            if(value > 0){
                value = 0;
            }else{
                value = 1;
            }
            setButtonValue(ui->pushButtonAlarm,value);
            query.exec("update ports set alarm=" + QString::number(value));
        }
    }
}

void SettingPortWindow::on_pushButtonOutput_clicked()
{
    QSqlQuery query("select * from ports where 1 limit 1");
    if(query.exec()){
        if(query.first()){
            int value = query.value(2).toInt();
            if(value > 0){
                value = 0;
            }else{
                value = 1;
            }
            setButtonValue(ui->pushButtonOutput,value);
            query.exec("update ports set output=" + QString::number(value));
        }
    }
}
