#ifndef SETTINGNODEWINDOW_H
#define SETTINGNODEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <tools.h>

namespace Ui {
class SettingNodeWindow;
}

class SettingNodeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingNodeWindow(QWidget *parent = nullptr);
    ~SettingNodeWindow();

private slots:
    void on_pbNode1_clicked();

    void on_pbNode2_clicked();

    void on_pbNode3_clicked();

    void on_pbNode4_clicked();

    void on_pbNode5_clicked();

    void on_pbNode6_clicked();

private:
    Ui::SettingNodeWindow *ui;

    Tools tools;
    QSqlDatabase database;

    void setButtonValue(QPushButton *btn , int node = 0);

    void toggleButtonStatus(QPushButton *btn);
    void closeAllconnection();

    // QWidget interface
protected:
    void showEvent(QShowEvent *event);

    void closeEvent(QCloseEvent *event);
};

#endif // SETTINGNODEWINDOW_H
