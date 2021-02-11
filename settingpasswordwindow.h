#ifndef SETTINGPASSWORDWINDOW_H
#define SETTINGPASSWORDWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <keyboardwindow.h>
#include <tools.h>

namespace Ui {
class SettingPasswordWindow;
}

class SettingPasswordWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingPasswordWindow(QWidget *parent = nullptr);
    ~SettingPasswordWindow();

private slots:
    void on_pushButton_5_clicked();

    void on_btnCleanCurrentPassword_clicked();

    void on_btnCleanNewPassword_clicked();

    void on_btnCleanRepeatPassword_clicked();

private:
    Ui::SettingPasswordWindow *ui;

    Tools tools;
    QSqlDatabase database;
    KeyboardWindow keyboardWindow ;
    void closeAllconnection();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);

    enum KeyboardMode {
        currentPassword= 0,
        newPassword,
        repeatPassword
    };

    KeyboardMode mode;

    void openKeyBoard(int mode);



    void showEvent(QShowEvent *event);
};

#endif // SETTINGPASSWORDWINDOW_H
