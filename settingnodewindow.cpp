#include "settingnodewindow.h"
#include "ui_settingnodewindow.h"

#include <QFile>
#include<QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>

SettingNodeWindow::SettingNodeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingNodeWindow)
{
    ui->setupUi(this);

    QFile File(":/Dark.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);

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
    database =tools.openDatabase();

    if(database.isOpen()){
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
   tools.closeAllConnections();
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
