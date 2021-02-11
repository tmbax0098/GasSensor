#ifndef PACKET_H
#define PACKET_H

#include <QObject>
#include <qdatetime.h>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Packet : public QObject
{
    Q_OBJECT
public:
    explicit Packet(QObject *parent = nullptr);

    double getValue() const;

    short getNode() const;

    bool getValid() const;

    void setNode(short value);

    void setValue(double value);

    void setValid(bool value);

    void setPacket(QString packet);

    QString getQueryCommand();

    bool getSaved() const;

    int getMin() const;
    void setMin(int value);

    int getMax() const;
    void setMax(int value);

    bool getWarning() const;

private:
    double value;
    short node;
    bool valid;
    bool saved;
    bool warning;
    QDateTime date;
    int min = 0;
    int max = 10000;
};

#endif // PACKET_H
