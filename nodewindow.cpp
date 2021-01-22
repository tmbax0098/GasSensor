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


    this->series = new QSplineSeries();

    this->series->append(0,5000);
    this->series->append(1,5000);
    this->series->append(2,5000);
    this->series->append(3,5000);
    this->series->append(4,5000);
    this->series->append(5,6000);
    this->series->append(6,6000);
    this->series->append(7,6000);
    this->series->append(8,6000);
    this->series->append(9,6000);
    this->series->setPointsVisible(true);
    series->setColor(Qt::red);
    QPen pen(Qt::red , 3);
    series->setPen(pen);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 80);
    axisX->setTickCount(10);
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 10000);
    axisY->setTickCount(10);


    this->series->setUseOpenGL(true);

    this->chart = new QChart ();

    this->chart->setTheme(QChart::ChartThemeDark);
    this->chart->addSeries(this->series);
    this->chart->addAxis(axisX , Qt::AlignBottom);
    this->chart->addAxis(axisY , Qt::AlignLeft);

    this->chartView = new QChartView(this->chart);
    this->chartView->setRenderHint(QPainter::Antialiasing);

    vLayout = new QVBoxLayout();
    vLayout->addWidget(chartView);

    this->ui->widgetChart->setLayout(vLayout);


    QObject::connect(&keyboardWindow , &KeyboardWindow::onAccept ,[=](QString value){
        setKeyboardResult (value);
    });



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
    this->chart->addSeries(series);

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
