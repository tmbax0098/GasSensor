#include "pinmanager.h"

#include <QDateTime>
#include <QFile>
#include <QTextStream>

PinManager::PinManager(QObject *parent) : QObject(parent)
{

}

void PinManager::alarmOn()
{
    createFile("PC4 1");
}

void PinManager::alarmOff()
{
    createFile("PC4 0");
}

QString PinManager::getFilePath() const
{
    return filePath;
}


void PinManager::createFile(QString data)
{
    QFile file(filePath + QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << data ;
        file.close();
    }
}

void PinManager::createSettingFile(bool input1, bool input2, bool output, bool alarm)
{
    QFile file(filePath + "setting.txt");
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << boolToString(input1)<<boolToString(input2)<<boolToString(output)<<boolToString(alarm , false);
        file.close();
    }
}

QString PinManager::boolToString(bool value , bool appendSpace )
{
    QString str(value ?"1":"0");
    if(appendSpace){
        str.append(" ");
    }
    return str;
}
