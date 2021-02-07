#include "messagewindow.h"
#include "ui_messagewindow.h"

#include <QFile>

MessageWindow::MessageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MessageWindow)
{
    ui->setupUi(this);

    QFile File(":/Dark.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);
}

MessageWindow::~MessageWindow()
{
    delete ui;
}

void MessageWindow::showMessage(QString message)
{
    ui->labelMessage->setText(message);
    this->showFullScreen();
}
