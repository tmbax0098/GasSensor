#include "settingwindow.h"
#include "ui_settingwindow.h"

#include <QFile>



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
    exportWindow.showFullScreen();
}

void SettingWindow::closeEvent(QCloseEvent *event)
{
    emit onClose();
}
