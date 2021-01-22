#ifndef KEYBOARDWINDOW_H
#define KEYBOARDWINDOW_H

#include <QMainWindow>

namespace Ui {
class KeyboardWindow;
}

class KeyboardWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit KeyboardWindow(QWidget *parent = nullptr);
    ~KeyboardWindow();

    QString getData() const;
    void setData(const QString &value);

    bool getCancel() const;
    void setCancel(bool value);

    void reset();

    bool getPasswordMode() const;
    void setPasswordMode(bool value);

signals:
    void onAccept(QString value);


private slots:
    void on_pushButtonClose_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

    void on_pushButton5_clicked();

    void on_pushButton6_clicked();

    void on_pushButton7_clicked();

    void on_pushButton8_clicked();

    void on_pushButton9_clicked();

    void on_pushButtonDot_clicked();

    void on_pushButton0_clicked();

    void on_pushButtonBackSpace_clicked();

private:
    Ui::KeyboardWindow *ui;
    QString data;
    bool cancel;
    void append(QString value = "");
    bool PasswordMode;

};

#endif // KEYBOARDWINDOW_H
