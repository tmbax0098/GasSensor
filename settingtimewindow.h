#ifndef SETTINGTIMEWINDOW_H
#define SETTINGTIMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class SettingTimeWindow;
}

class SettingTimeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingTimeWindow(QWidget *parent = nullptr);
    ~SettingTimeWindow();

signals:
    void showMessage(QString message);

private slots:
    void on_pushButtonSetTime_clicked();

private:
    Ui::SettingTimeWindow *ui;
    int minute = 0;
    int hour = 0;

    QString format(int value);
};

#endif // SETTINGTIMEWINDOW_H
