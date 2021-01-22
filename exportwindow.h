#ifndef EXPORTWINDOW_H
#define EXPORTWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class ExportWindow;
}

class ExportWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExportWindow(QWidget *parent = nullptr);
    ~ExportWindow();

private slots:
    void on_btnExport_clicked();

    void on_pbNode1_clicked();

    void on_pbNode2_clicked();

    void on_pbNode3_clicked();

    void on_pbNode4_clicked();

    void on_pbNode5_clicked();

    void on_pbNode6_clicked();

private:
    Ui::ExportWindow *ui;

    void setButtonValue(QPushButton *btn, bool value);

    bool node1 = false;
    bool node2 = false;
    bool node3 = false;
    bool node4 = false;
    bool node5 = false;
    bool node6 = false;



};

#endif // EXPORTWINDOW_H
