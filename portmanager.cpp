#include "portmanager.h"
#include<QIODevice>
#include<QDebug>

PortManager::PortManager(QObject *parent) : QObject(parent)
{
    sp.setPortName("/dev/ttyS3");
    sp.setBaudRate(QSerialPort::Baud115200);

    if(sp.open(QIODevice::ReadWrite)){

        qDebug()<<"PORT IS OPEN";
        emit  onStatusChanged(true);

    }else{

        qDebug()<<"PORT IS CLOSE";
        emit  onStatusChanged(false);
    }


    QObject::connect(&sp , &QSerialPort::readyRead , [=](){
		
		qDebug()<<"NEW PACKET READY FOR READ!";
		
        QString packet = sp.readLine();

         qDebug()<<"NEW PACKET \t"<<packet<<endl;

         emit newPacket(packet);
    });

    QObject::connect(&sp , &QSerialPort::errorOccurred , [=](){
        if(!sp.isOpen()){
            sp.open(QIODevice::ReadWrite);
        }
    });


}
