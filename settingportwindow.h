#ifndef SETTINGPORTWINDOW_H
#define SETTINGPORTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSqlDatabase>
#include <tools.h>

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

    Tools tools;

    QSqlDatabase database;

    void setButtonValue(QPushButton *btn, int value);

    void updateValue(QString fieldName , int fieldIndex , QPushButton *button);


    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
};

#endif // SETTINGPORTWINDOW_H
