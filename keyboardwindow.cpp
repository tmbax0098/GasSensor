#include "keyboardwindow.h"
#include "ui_keyboardwindow.h"

#include <QFile>

KeyboardWindow::KeyboardWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KeyboardWindow)
{
    ui->setupUi(this);
    setData("");
    setCancel(true);



    QFile File(":/Dark.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);

}

KeyboardWindow::~KeyboardWindow()
{
    delete ui;
}

void KeyboardWindow::on_pushButtonClose_clicked()
{
    setCancel(true);
    setData("");
    this->close();
}

QString KeyboardWindow::getData() const
{
    return data;
}

void KeyboardWindow::setData(const QString &value)
{
    data = value;
}

void KeyboardWindow::on_pushButton_14_clicked()
{
    onAccept(data);
    setCancel(false);
    this->close();
}

bool KeyboardWindow::getCancel() const
{
    return cancel;
}

void KeyboardWindow::setCancel(bool value)
{
    cancel = value;
}

void KeyboardWindow::reset()
{
    data="";
    ui->labelValue->setText(data);
}

void KeyboardWindow::on_pushButton1_clicked()
{
    append("1");
}

void KeyboardWindow::on_pushButton2_clicked()
{
    append("2");
}

void KeyboardWindow::on_pushButton3_clicked()
{
    append("3");
}

void KeyboardWindow::on_pushButton4_clicked()
{
    append("4");
}

void KeyboardWindow::on_pushButton5_clicked()
{
    append("5");
}

void KeyboardWindow::on_pushButton6_clicked()
{
    append("6");
}

void KeyboardWindow::on_pushButton7_clicked()
{
    append("7");
}

void KeyboardWindow::on_pushButton8_clicked()
{
    append("8");
}

void KeyboardWindow::on_pushButton9_clicked()
{
    append("9");
}

void KeyboardWindow::on_pushButtonDot_clicked()
{
    append(".");
}

void KeyboardWindow::on_pushButton0_clicked()
{
    append("0");
}

void KeyboardWindow::on_pushButtonBackSpace_clicked()
{
    data = data.left(data.length() - 1);
    if(getPasswordMode()){
        QString val = "";
        for (int i=0;i<data.length();i++ ) {
            val +="*";
        }
        ui->labelValue->setText(val);
    }else{
        ui->labelValue->setText(data);
    }
}

void KeyboardWindow::append(QString value)
{
    data += value;
    if(getPasswordMode()){
        QString val = "";
        for (int i=0;i<data.length();i++ ) {
            val +="*";
        }
        ui->labelValue->setText(val);
    }else{
        ui->labelValue->setText(data);
    }
}

bool KeyboardWindow::getPasswordMode() const
{
    return PasswordMode;
}

void KeyboardWindow::setPasswordMode(bool value)
{
    PasswordMode = value;
}
