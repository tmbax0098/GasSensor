#ifndef PORTMANAGER_H
#define PORTMANAGER_H

#include <QObject>
#include<QSerialPort>

class PortManager : public QObject
{
    Q_OBJECT
public:
    explicit PortManager(QObject *parent = nullptr);

signals:
    void onStatusChanged(bool value = false);
    void newPacket(QString packet = "");

private:
    QSerialPort sp;

};

#endif // PORTMANAGER_H
