#include "settingwindow.h"
#include "ui_settingwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QDateTime>



SettingWindow::SettingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);

    QFile File(":/Dark.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);

}

SettingWindow::~SettingWindow()
{
    delete ui;
}

void SettingWindow::on_btnBack_clicked()
{
    this->close();
}

void SettingWindow::on_pushButton_clicked()
{
    settingPasswordWindow.showFullScreen();
}

void SettingWindow::on_btnSettingNode_clicked()
{
    settingNodeWindow.showFullScreen();
}

void SettingWindow::on_pushButton_3_clicked()
{
    settingTimeWindow.showFullScreen();
}

void SettingWindow::on_pushButtonPorts_clicked()
{
    settingPortWindow.showFullScreen();
}

void SettingWindow::on_pushButton_2_clicked()
{

//    QFileDialog fileDialog;
//    fileDialog.setWindowState(Qt::WindowFullScreen);
//    fileDialog.setDirectory("/home");
//    fileDialog.setOptions(QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
//    fileDialog.setWindowState(Qt::WindowFullScreen | Qt::WindowMaximized);
//    fileDialog.exec();

    //fileDialog.showFullScreen();




    QString destinationPath = QFileDialog::getExistingDirectory(this, tr("Choose save path"),
                                                                "/home",
                                                                QFileDialog::ShowDirsOnly
                                                                | QFileDialog::ReadOnly
                                                                | QFileDialog::DontResolveSymlinks);
    if(destinationPath != ""){
        QString sourcePath = QDir::currentPath()+"/GasSensor.db";
        destinationPath.append("GasSensor");
        destinationPath.append(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
        destinationPath.append(".db");
//        qDebug()<<"destinationPath = "<<destinationPath;
//        qDebug()<<"sourcePath = "<<sourcePath;
        if(QFile::copy(sourcePath,destinationPath)){
            emit showMessage("Data export successfully.");
        }else{
            emit showMessage("Export failed!");
        }
    }

    //QFileDialog::ope
    // exportWindow.showFullScreen();
}

void SettingWindow::closeEvent(QCloseEvent *event)
{
    emit onClose();
}

void SettingWindow::on_pushButtonResetFactory_clicked()
{
    emit resetFactory();
}
