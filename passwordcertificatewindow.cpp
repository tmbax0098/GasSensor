#include "passwordcertificatewindow.h"
#include "ui_passwordcertificatewindow.h"
#include<QDebug>
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>


PasswordCertificateWindow::PasswordCertificateWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PasswordCertificateWindow)
{
    ui->setupUi(this);


    QFile File(":/Dark.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);

    QObject::connect(&keyboardWindow , &KeyboardWindow::onAccept , ui->lineEdit , &QLineEdit::setText);

}

PasswordCertificateWindow::~PasswordCertificateWindow()
{
    delete ui;
}

bool PasswordCertificateWindow::reset() const
{
    ui->lineEdit->setText("");
    ui->lblMessage->setText("");
    return true;
}

void PasswordCertificateWindow::on_pushButtonEditPassword_clicked()
{
    keyboardWindow.reset();
    keyboardWindow.setPasswordMode(true);
    keyboardWindow.showFullScreen();
}

void PasswordCertificateWindow::on_btnCertificate_clicked()
{
    if(database.isOpen()){
        QSqlQuery query("SELECT count(password) FROM users WHERE password='"+ui->lineEdit->text()+"'");
        if(query.exec()){
            query.first();
            if(query.value(0).toLongLong() >= 1){
                login();
                return;
            }
        }else{
            qDebug()<<"error : " << query.lastError().text();
        }
    }
    ui->lblMessage->setText("Login  fail!");
}

void PasswordCertificateWindow::closeAllconnection()
{
    database.close();
    QStringList list = QSqlDatabase::connectionNames();
    foreach (QString name,list) {
        qDebug()<<"Connection closed! "<<name;
        QSqlDatabase::removeDatabase(name);
    }
}

QSqlDatabase PasswordCertificateWindow::getDatabase() const
{
    return database;
}

void PasswordCertificateWindow::setDatabase(const QSqlDatabase &value)
{
    database = value;
}

void PasswordCertificateWindow::closeEvent(QCloseEvent *event)
{
    closeAllconnection();
    return;
}

void PasswordCertificateWindow::showEvent(QShowEvent *event)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("GasSensor.db");
    bool ok = database.open();
    qDebug()<<"PasswordCertificateWindow ==> database is open state : "<<ok;
}
