#include "settingwindow.h"
#include "ui_settingwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QStorageInfo>



SettingWindow::SettingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);

    QFile File(":/Dark.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);

    QObject::connect(&settingTimeWindow , &SettingTimeWindow::showMessage ,[=](QString message){
        emit showMessage(message);
    });

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

    QString sourcePath = tools.getDbPath();

    QFile source(sourcePath);
    if(source.exists()){

        foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
            if (storage.isReadOnly()){
                 emit showMessage("Drive is readonly!");
            }else{
                QString destinationPath = storage.rootPath();
                destinationPath.append("/GasSensor_");
                destinationPath.append(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
                destinationPath.append(".db");

                if(QFile::copy(sourcePath,destinationPath)){
                    emit showMessage("Data export successfully.");
                }else{
                    emit showMessage("Export failed!");
                }
            }
        }
    }else{
        emit showMessage("Source is not exist!");
    }
}

void SettingWindow::closeEvent(QCloseEvent *event)
{
    emit onClose();
}

void SettingWindow::on_pushButtonResetFactory_clicked()
{
    emit resetFactory();
}
