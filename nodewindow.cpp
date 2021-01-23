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

    QPen pen(Qt::red , 3);

    axisX = new QValueAxis;
    axisX->setRange(0, 80);
    axisX->setTickCount(10);

    axisY = new QValueAxis;
    axisY->setRange(0, 10000);
    axisY->setMin(0);
    axisY->setMax(10000);
    axisY->setTickCount(10);

    axisTime = new QDateTimeAxis;
    axisTime->setFormat("hh:mm");
    //    axisTime->setTickCount(1);
    //    axisTime->setFormat("dd HH:mm");
    //    axisTime->setFormat("yyyy-MM-dd\nhh:mm:ss");


    this->series = new QSplineSeries();
    this->series->setPointsVisible(true);
    this->series->setColor(Qt::red);
    this->series->setPen(pen);
    this->series->setUseOpenGL(true);
    this->series->attachAxis(axisX);
    this->series->attachAxis(axisY);


    this->chart = new QChart();
    this->chart->legend()->hide();
    this->chart->setTheme(QChart::ChartThemeDark);
    this->chart->addAxis(axisY , Qt::AlignLeft);
    this->chart->addAxis(axisX , Qt::AlignBottom);
    this->chart->addSeries(this->series);


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

int NodeWindow::getNode() const
{
    return node;
}

void NodeWindow::setNode(int value)
{
    if(value > 0 && value < 6){
        node = value;
        ui->lblNode->setText("Node " + QString::number(value));
    }
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
    
    qDebug()<<"Points ===> "<<Points.size();

    this->series->clear();
    this->series->append(Points);
    this->series->setPointsVisible();

    this->chart->removeSeries(this->series);
    this->chart->addSeries(this->series);
}

void NodeWindow::setKeyboardResult(QString value)
{
    switch (currentField) {
    case UpSet:
        ui->lineEditUpSet->setText(value);
        break;
    case DownSet:
        ui->lineEditDownSet->setText(value);
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
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("GasSensor.db");
    bool ok = database.open();
    qDebug()<<"NodeWindow ==> openDatabase ==> database is open state : "<<ok ;

    if(ok){
        QSqlQuery query;
        if(query.exec("select * from node_setting where node=" + QString::number(node))){
            if(query.first()){
                ui->lineEditUpSet->setText(query.value(2).toString());
                ui->lineEditDownSet->setText(query.value(3).toString());
                if(query.value(1).toInt() != 1){
                    this->close();
                }
            }else{
                this->close();
            }
        }else{
            qDebug()<<"ERROR ===> "<<query.lastError().text();
        }
    }
}

void NodeWindow::closeEvent(QCloseEvent *event)
{
    this->open = false;
    database.close();
    QStringList list = QSqlDatabase::connectionNames();
    foreach (QString name,list) {
        qDebug()<<"Connection closed! "<<name;
        QSqlDatabase::removeDatabase(name);
    }
}

bool NodeWindow::isOpen()
{
    return this->open;
}

void NodeWindow::on_radioButtonHour_toggled(bool checked)
{
    disableRadioButtons();

    this->series->clear();

    if(checked){
        QSqlQuery query("SELECT datetime , value FROM node WHERE id=" + QString::number(this->node) + " ORDER BY datetime ");
        if(query.exec()){
            while (query.next()) {
                this->series->append(
                            query.value(0).toDateTime().toMSecsSinceEpoch() ,
                            query.value(1).toDouble());
            }
        }else{
            qDebug()<<"ERROR : "<<query.lastError().text()<<endl;
        }
        query.clear();

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

void NodeWindow::on_radioButtonReal_toggled(bool checked)
{
    disableRadioButtons();
    if(checked){

        this->series->clear();

        this->series->attachAxis(axisX);
        this->series->attachAxis(axisY);

        this->chart->removeAxis(axisTime);
        this->chart->addAxis(axisX , Qt::AlignBottom);

        this->chart->removeSeries(this->series);
        this->chart->addSeries(this->series);
    }
    enableRadioButtons();
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
