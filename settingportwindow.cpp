#include "settingportwindow.h"
#include "ui_settingportwindow.h"

#include <QFile>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>

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

void SettingPortWindow::updateValue(QString fieldName, int fieldIndex, QPushButton *button)
{
    QSqlQuery query("select * from ports where 1 limit 1");
    if(query.exec()){
        if(query.first()){
            int value = query.value(fieldIndex).toInt();
            if(value > 0){
                value = 0;
            }else{
                value = 1;
            }
            setButtonValue(button,value);
            query.exec("update ports set "+fieldName+"=" + QString::number(value));
        }
    }
}

void SettingPortWindow::closeEvent(QCloseEvent *event)
{
    database.close();
    tools.closeAllConnections();
}

void SettingPortWindow::showEvent(QShowEvent *event)
{
    database =tools.openDatabase();

    if(database.isOpen()){
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
    updateValue("first" , 0,ui->pushButtonInput1);
}

void SettingPortWindow::on_pushButtonInput2_clicked()
{
    updateValue("second" , 1,ui->pushButtonInput2);
}

void SettingPortWindow::on_pushButtonAlarm_clicked()
{
    updateValue("alarm" , 3,ui->pushButtonAlarm);
}

void SettingPortWindow::on_pushButtonOutput_clicked()
{
    updateValue("output" , 2,ui->pushButtonOutput);
}
