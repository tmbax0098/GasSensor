#ifndef NODEWINDOW_H
#define NODEWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include<QtCharts>
#include <keyboardwindow.h>
#include <packet.h>

namespace Ui {
class NodeWindow;
}

class NodeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NodeWindow(QWidget *parent = nullptr);
    ~NodeWindow();

    int getNode() const;
    void setNode(int value);

public slots:
    void setNewPoint(Packet &packet);
    bool isOpen();

private slots:
    void setKeyboardResult(QString value = "");

    void on_pushButtonUpSet_clicked();

    void on_pushButtonDownset_clicked();

private:
    Ui::NodeWindow *ui;

    QSqlDatabase database;

    int node =1;
    bool open ;

    KeyboardWindow keyboardWindow;

    enum Field {
        None=0,
        UpSet,
        DownSet
    };



    Field currentField = Field::None;

    QChart *chart;
    QChartView *chartView;
    QSplineSeries *series;
    QVBoxLayout *vLayout;


    // QWidget interface
protected:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
};

#endif // NODEWINDOW_H
