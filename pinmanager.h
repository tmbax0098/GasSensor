#ifndef PINMANAGER_H
#define PINMANAGER_H

#include <QObject>

class PinManager : public QObject
{
    Q_OBJECT
public:
    explicit PinManager(QObject *parent = nullptr);

    QString getFilePath() const;

public slots:
    void alarmOn();
    void alarmOff();

signals:

private:
    QString filePath = "/home/koorosh/files/";
    void createFile(QString data);
    void createSettingFile(bool input1,bool input2,bool output ,bool alarm);
    QString boolToString(bool value , bool appendSpace = true);
};

#endif // PINMANAGER_H
