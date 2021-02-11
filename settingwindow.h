#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QMainWindow>
//#include <exportwindow.h>
#include <settingnodewindow.h>
#include <settingpasswordwindow.h>
#include <settingportwindow.h>
#include <settingtimewindow.h>
#include<tools.h>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

signals:
    void onClose();
    void resetFactory();
    void showMessage(QString message);

private slots:
    void on_btnBack_clicked();

    void on_pushButton_clicked();

    void on_btnSettingNode_clicked();

    void on_pushButton_3_clicked();

    void on_pushButtonPorts_clicked();

    void on_pushButton_2_clicked();

    void on_pushButtonResetFactory_clicked();

private:
    Ui::SettingWindow *ui;

    Tools tools;

    SettingTimeWindow settingTimeWindow;
    SettingNodeWindow settingNodeWindow;
    SettingPasswordWindow settingPasswordWindow;
    SettingPortWindow settingPortWindow;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // SETTINGWINDOW_H
