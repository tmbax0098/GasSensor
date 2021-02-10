#include "settingpasswordwindow.h"
#include "ui_settingpasswordwindow.h"

#include <QFile>
#include<QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>

SettingPasswordWindow::SettingPasswordWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingPasswordWindow)
{
    ui->setupUi(this);

    QFile File(":/Dark.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);


    connect(&keyboardWindow , &KeyboardWindow::onAccept,[=](QString value){

        switch (mode) {

        case currentPassword:
            ui->lineEditCurrentPassword->setText(value);
            break;
        case newPassword:
            ui->lineEditNewPassword->setText(value);
            break;
        case repeatPassword:
            ui->lineEditRepeatPassword->setText(value);
            break;
        default:
            break;

        }

    });

}

SettingPasswordWindow::~SettingPasswordWindow()
{
    delete ui;
}

void SettingPasswordWindow::on_pushButton_5_clicked()
{
    ui->labelMessage->setText("Change password ...");

    QString cPass = ui->lineEditCurrentPassword->text();//current password
    QString nPass = ui->lineEditNewPassword->text();//new password
    QString rPass = ui->lineEditRepeatPassword->text();//repeat password


    //message show to user!
    QString message = "Change password ...";

    if(cPass.length() < 5){
        message = "Please enter password!";
    }else if(nPass != rPass){
        message = "New password an it repeat is not equal";
    }else if(nPass.length()<5){
        message = "New password must be bigger than 5 character!";
    }else{
        //database connection state

        if(!database.isOpen()){
          //  database = QSqlDatabase::addDatabase("QSQLITE");
         //   database.setDatabaseName("users.db");
            bool ok = database.open();
            qDebug()<<"setting password window database is open state 2 : " << ok;
        }

        if(database.isOpen()){
            qDebug()<<"SELECT COUNT(password) FROM users WHERE password='"+cPass+"'";
            QSqlQuery query("SELECT COUNT(password) FROM users WHERE password='"+cPass+"'");
            if(query.exec()){
                query.first();
                if(query.value(0).toLongLong() > 0){
                    query.clear();
                    if(query.exec("UPDATE users SET password= '"+nPass+"' WHERE 1")){
                        message = "Password changed successfully!";

                        ui->lineEditCurrentPassword->setText("");
                        ui->lineEditNewPassword->setText("");
                        ui->lineEditRepeatPassword->setText("");

                    }else{
                        message = "Database error(2)!";
                    }
                }
            }else{
                qDebug()<<query.lastError();
                message = query.lastError().text();
            }
        }else{
            message = "Database connection lost!";
        }
    }
    ui->labelMessage->setText(message);
}

void SettingPasswordWindow::closeEvent(QCloseEvent *event)
{
    closeAllconnection();
    ui->lineEditCurrentPassword->setText("");
    ui->lineEditNewPassword->setText("");
    ui->lineEditRepeatPassword->setText("");
}

void SettingPasswordWindow::on_btnCleanCurrentPassword_clicked()
{
    openKeyBoard(KeyboardMode::currentPassword);
}

void SettingPasswordWindow::on_btnCleanNewPassword_clicked()
{
    openKeyBoard(KeyboardMode::newPassword);
}

void SettingPasswordWindow::on_btnCleanRepeatPassword_clicked()
{
    openKeyBoard(KeyboardMode::repeatPassword);
}

void SettingPasswordWindow::openKeyBoard(int mode){
    keyboardWindow.setPasswordMode(true);
    this->mode =(KeyboardMode)mode;
    keyboardWindow.showFullScreen();
}

void SettingPasswordWindow::showEvent(QShowEvent *event)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QDir::currentPath()+"/GasSensor.db");
    bool ok = database.open();
    qDebug()<<"setting password window database is open state : " << ok;
}

void SettingPasswordWindow::closeAllconnection()
{
    database.close();
    QStringList list = QSqlDatabase::connectionNames();
    foreach (QString name,list) {
        qDebug()<<"Connection closed! "<<name;
        QSqlDatabase::removeDatabase(name);
    }
}
