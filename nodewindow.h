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

    Packet *getNode() const;
    void setNode(Packet *value);

signals:
    void loadArchive(int node);
    void saveNodeSetting(Packet *packet);

public slots:
    void setNewPoint(Packet &packet);
    void setArchive(QList<QPointF> list);
    bool isOpen();

private slots:
    void setKeyboardResult(QString value = "");

    void on_pushButtonUpSet_clicked();

    void on_pushButtonDownset_clicked();

    void on_radioButtonHour_toggled(bool checked);

    void on_radioButtonReal_toggled(bool checked);

private:
    Ui::NodeWindow *ui;

    QSqlDatabase database;

//    int node =1;
    Packet *node;
    bool open ;

    KeyboardWindow keyboardWindow;

    enum Field {
        None=0,
        UpSet,
        DownSet
    };


    Field currentField = Field::None;

    QChart *chart;

    QLineSeries *series;

    QVBoxLayout *layout;
    QChartView *chartView;

    QValueAxis *axisX;
    QValueAxis *axisY;
    QDateTimeAxis *axisTime ;


    void disableRadioButtons();
    void enableRadioButtons();


    // QWidget interface
protected:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
};

#endif // NODEWINDOW_H
