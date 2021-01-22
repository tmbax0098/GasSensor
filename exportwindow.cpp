#include "exportwindow.h"
#include "ui_exportwindow.h"

#include <QFile>
#include <QDir>
#include <QDateTime>

ExportWindow::ExportWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExportWindow)
{
    ui->setupUi(this);

    QFile File(":/Dark.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);


    setButtonValue(ui->pbNode1 , node1);
    setButtonValue(ui->pbNode2 , node2);
    setButtonValue(ui->pbNode3 , node3);
    setButtonValue(ui->pbNode4 , node4);
    setButtonValue(ui->pbNode5 , node5);
    setButtonValue(ui->pbNode6 , node6);


}

ExportWindow::~ExportWindow()
{
    delete ui;
}


void ExportWindow::setButtonValue(QPushButton *btn, bool value)
{
    if(value){
        btn->setStyleSheet("background-color : #00ff00;color:#000000;");
    }else{
        btn->setStyleSheet("background-color : #ff0000;color:#ffffff;");
    }
}

void ExportWindow::on_btnExport_clicked()
{

    QString sourcePath = QDir::currentPath()+"/GasSensor.db";
    QString destinationPath =  "/media/rad/CEB2-BA58/";
    destinationPath.append("GasSensor");
    destinationPath.append(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    destinationPath.append(".db");
    if(QFile::copy(sourcePath,destinationPath)){
        ui->labelMessage->setText("Data export successfully.");
    }else{
        ui->labelMessage->setText("Export failed!");
    }

}

void ExportWindow::on_pbNode1_clicked()
{
    node1 = !node1;
    setButtonValue(ui->pbNode1 , node1);
}

void ExportWindow::on_pbNode2_clicked()
{
    node2 = !node2;
    setButtonValue(ui->pbNode2 , node2);
}

void ExportWindow::on_pbNode3_clicked()
{
    node3 = !node3;
    setButtonValue(ui->pbNode3 , node3);
}

void ExportWindow::on_pbNode4_clicked()
{
    node4 = !node4;
    setButtonValue(ui->pbNode4 , node4);
}

void ExportWindow::on_pbNode5_clicked()
{
    node5= !node5;
    setButtonValue(ui->pbNode5 , node5);
}

void ExportWindow::on_pbNode6_clicked()
{
    node6 = !node6;
    setButtonValue(ui->pbNode6 , node6);
}
