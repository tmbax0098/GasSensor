#ifndef SETTINGPORTWINDOW_H
#define SETTINGPORTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSqlDatabase>

namespace Ui {
class SettingPortWindow;
}

class SettingPortWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingPortWindow(QWidget *parent = nullptr);
    ~SettingPortWindow();

private slots:
    void on_pushButtonInput1_clicked();

    void on_pushButtonInput2_clicked();

    void on_pushButtonAlarm_clicked();

    void on_pushButtonOutput_clicked();

private:
    Ui::SettingPortWindow *ui;


    QSqlDatabase database;

    void setButtonValue(QPushButton *btn, int value);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
};

#endif // SETTINGPORTWINDOW_H
