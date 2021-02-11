#include "tools.h"

#include <QSqlQuery>
#include <QDir>
#include <QDebug>

Tools::Tools(QObject *parent) : QObject(parent)
{

}

QString Tools::getDbPath() const
{
    return dbPath;
}

QSqlDatabase Tools::openDatabase()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(getDbPath());
    database.open();
    return database;
}

void Tools::closeAllConnections()
{
    QStringList list = QSqlDatabase::connectionNames();
    foreach (QString name,list) {
        QSqlDatabase::removeDatabase(name);
    }
}

QString Tools::resetFactory()
{
    QString message = "";
    QSqlDatabase database = openDatabase();
    if(database.isOpen()){
        QSqlQuery query;
        if(query.exec("DELETE FROM node WHERE 1")){
            query.clear();
            if(query.exec("UPDATE `node_setting` SET `value`=1 , `up`=10000 , `down`=0 WHERE 1")){
                query.clear();
                if(query.exec("UPDATE `ports` SET `first`=1 , `second`=1 , `output`=1 , `alarm`=1 WHERE 1")){
                    message =("Reset factory finish!");
                }else{
                    message = ("ports table reset fail!");
                }
            }else{
                message =("node_setting table reset fail!");
            }
        }else{
            message =("node table reset fail!");
        }
    }else{
        message =("databse connection fail!");
    }
    database.close();
    closeAllConnections();
    return message;
}

int Tools::getSaveTimer() const
{
    return saveTimer;
}
