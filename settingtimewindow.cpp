#include "settingtimewindow.h"
#include "ui_settingtimewindow.h"

#include <QFile>
#include<QSlider>

SettingTimeWindow::SettingTimeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingTimeWindow)
{
    ui->setupUi(this);

    QFile File(":/Dark.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);

    connect(ui->horizontalSliderHour , &QSlider::valueChanged , [=](int value){
        hour = value;
        ui->labelTime->setText(format(hour) + ":" + format(minute));
    });
    connect(ui->horizontalSliderMinute , &QSlider::valueChanged , [=](int value){
        minute= value;
        ui->labelTime->setText(format(hour) + ":" + format(minute));
    });

}

SettingTimeWindow::~SettingTimeWindow()
{
    delete ui;
}

void SettingTimeWindow::on_pushButtonSetTime_clicked()
{

    // ui->labelMessage->setText("");

    QString hour = QString::number(ui->horizontalSliderHour->value());
    QString minute =QString::number(ui->horizontalSliderMinute->value());
    // QString second = QString::number(ui->horizontalSliderSecond->value());

    QString time  = hour + ":" + minute ;

    //  ui->labelMessage->setText("Time set successfully!");

}

QString SettingTimeWindow::format(int value)
{
    if(value< 10){
        return "0"+ QString::number(value);
    }else{
        return QString::number(value);
    }
}
