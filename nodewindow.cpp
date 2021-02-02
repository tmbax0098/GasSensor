#include "nodewindow.h"
#include "ui_nodewindow.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QPen>

NodeWindow::NodeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NodeWindow)
{
    ui->setupUi(this);


    QFile File(":/Dark.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(StyleSheet);
    
    node = new Packet;

    QPen pen(Qt::red , 3);

    axisX = new QValueAxis;
    axisX->setRange(0, 80);
    axisX->setMin(0);
    axisX->setMax(80);
    axisX->setTickCount(8);

    axisY = new QValueAxis;
    axisY->setRange(0, 10000);
    axisY->setMin(0);
    axisY->setMax(10000);
    axisY->setTickCount(5);

    axisTime = new QDateTimeAxis;
    axisTime->setFormat("hh:mm");
    //    axisTime->setTickCount(1);
    //    axisTime->setFormat("dd HH:mm");
    //    axisTime->setFormat("yyyy-MM-dd\nhh:mm:ss");


    this->series = new QLineSeries();
    this->series->setPointsVisible(true);
    this->series->setColor(Qt::red);
    this->series->setPen(pen);
    this->series->setUseOpenGL(true);



    this->chart = new QChart();
    this->chart->legend()->hide();
    this->chart->setTheme(QChart::ChartThemeDark);

    this->chart->addSeries(this->series);

    this->chart->addAxis(axisY , Qt::AlignLeft);
    this->chart->addAxis(axisX , Qt::AlignBottom);



    this->series->attachAxis(axisX);
    this->series->attachAxis(axisY);


    this->chartView = new QChartView(this->chart);
    layout = new QVBoxLayout;
    layout->addWidget(this->chartView);
    ui->widgetChart->setLayout(layout);

    QObject::connect(&keyboardWindow , &KeyboardWindow::onAccept ,[=](QString value){
        setKeyboardResult (value);
    });

    on_radioButtonHour_toggled(true);

}

NodeWindow::~NodeWindow()
{
    delete ui;
}

void NodeWindow::setNewPoint(Packet &packet)
{
    if(ui->radioButtonHour->isChecked())
        return;


    QList<QPointF> Points = this->series->points();

    while(Points.size()>= 60) {
        Points.removeFirst();
    }

    int counter=0;
    QList<QPointF>::iterator i;
    for (i=Points.begin(); i!=Points.end();i++)
    {
        i->setX(counter);
        counter++;
    }

    QPointF point(Points.size() , QRandomGenerator::global()->bounded(10000));
    Points.append(point);

    this->series->clear();
    this->series->append(Points);
    this->series->setPointsVisible();

    this->chart->removeSeries(this->series);
    this->chart->addSeries(this->series);


    this->series->attachAxis(axisX);
    this->series->attachAxis(axisY);
}

void NodeWindow::setArchive(QList<QPointF> list)
{
    this->series->clear();

    foreach (QPointF point, list) {
        this->series->append(point);
    }

    if(this->series->points().size() > 0){
        axisTime->setMin(QDateTime::fromMSecsSinceEpoch(this->series->points().first().x()));
        axisTime->setMax(QDateTime::fromMSecsSinceEpoch(this->series->points().last().x()));
    }

    this->series->attachAxis(axisY);
    this->series->attachAxis(axisTime);

    this->chart->removeAxis(axisX);
    this->chart->addAxis(axisTime , Qt::AlignBottom);

    this->chart->removeSeries(this->series);
    this->chart->addSeries(this->series);

    enableRadioButtons();

}

void NodeWindow::setKeyboardResult(QString value)
{
    switch (currentField) {
    case UpSet:
        node->setMax(value.toInt());
        ui->lineEditUpSet->setText(value);
        emit saveNodeSetting(node);
        break;
    case DownSet:
        node->setMin(value.toInt());
        ui->lineEditDownSet->setText(value);
        emit saveNodeSetting(node);
        break;
    default:
        break;
    }
}

void NodeWindow::on_pushButtonUpSet_clicked()
{
    currentField=UpSet;
    keyboardWindow.setPasswordMode(false);
    keyboardWindow.showFullScreen();
}

void NodeWindow::on_pushButtonDownset_clicked()
{
    currentField=DownSet;
    keyboardWindow.setPasswordMode(false);
    keyboardWindow.showFullScreen();
}

void NodeWindow::showEvent(QShowEvent *event)
{
    this->open = true;
    emit loadArchive(this->node->getNode());
}

void NodeWindow::closeEvent(QCloseEvent *event)
{
    this->open = false;
    this->series->points().clear();
}

bool NodeWindow::isOpen()
{
    return this->open;
}

void NodeWindow::on_radioButtonHour_toggled(bool checked)
{
    disableRadioButtons();
    if(checked){
        emit loadArchive(this->node->getNode());
    }
}

void NodeWindow::on_radioButtonReal_toggled(bool checked)
{
    disableRadioButtons();
    if(checked){

        this->series->clear();

        this->chart->removeAxis(axisTime);
        this->chart->addAxis(axisX , Qt::AlignBottom);

        this->chart->removeSeries(this->series);
        this->chart->addSeries(this->series);

        this->series->attachAxis(axisX);
        this->series->attachAxis(axisY);
    }
    enableRadioButtons();
}

Packet *NodeWindow::getNode() const
{
    return node;
}

void NodeWindow::setNode(Packet *value)
{
    node = value;
    ui->lineEditUpSet->setText(QString::number(value->getMax()));
    ui->lineEditDownSet->setText(QString::number(value->getMin()));
}

void NodeWindow::disableRadioButtons()
{
    ui->radioButtonHour->setEnabled(false);
    ui->radioButtonReal->setEnabled(false);
}

void NodeWindow::enableRadioButtons()
{
    ui->radioButtonHour->setEnabled(true);
    ui->radioButtonReal->setEnabled(true);
}
