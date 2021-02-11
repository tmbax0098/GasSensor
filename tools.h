#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>
#include <QSqlDatabase>

class Tools : public QObject
{
    Q_OBJECT
public:
    explicit Tools(QObject *parent = nullptr);

    QString getDbPath() const;

    QSqlDatabase openDatabase();
    void closeAllConnections();
    QString resetFactory();

    int getSaveTimer() const;

signals:


private:
    QString dbPath = "/home/koorosh/GasSensor/GasSensor.db";
    int saveTimer = 30000;
};

#endif // TOOLS_H
