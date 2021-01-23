#include "packet.h"


Packet::Packet(QObject *parent)
{
    this->value =0;
    this->node = 0;
    this->valid = false;
    this->saved=false;
    this->warning = false;
}

double Packet::getValue() const
{
    return value;
}

short Packet::getNode() const
{
    return node;
}

bool Packet::getValid() const
{
    return valid;
}

void Packet::setNode(short value)
{
    node = value;
}

void Packet::setValue(double value)
{
    value = value;
}

void Packet::setValid(bool value)
{
    valid = value;
}

void Packet::setPacket(QString packet)
{
    if(packet.length() >=5 && packet.mid(0,1) == "#" && packet.right(1) == "$"){
        node = packet.mid(2,1).toShort();
        value = packet.mid(3,packet.length() - 1).toDouble();
        value -=280;
        if(value > 0){
            value/=0.3815;
        }else{
            value = 0;
        }
        valid = true;
    }else{
        valid= false;
        node = 0;
        value = 0;
    }
    saved = false;

    if(value < min || value > max){
        warning = true;
        this->alarmOn();
    }else{
        warning = false;
    }

}

QString Packet::getQueryCommand()
{
    saved = true;
    return "INSERT INTO node (id , value) VALUES ("+QString::number( node )+", " + QString::number(value) + ")";
}

bool Packet::getSaved() const
{
    return saved;
}

int Packet::getMin() const
{
    return min;
}

void Packet::setMin(int value)
{
    min = value;
}

int Packet::getMax() const
{
    return max;
}

void Packet::setMax(int value)
{
    max = value;
}

bool Packet::getWarning() const
{
    return warning;
}

void Packet::alarmOff()
{
    QProcess process;
    process.start("sudo python pin.py PA20 0");
    process.waitForStarted();
}

void Packet::alarmOn()
{
    QProcess process;
    process.start("sudo python pin.py PA20 1");
    process.waitForStarted();
}

//QPointF Packet::getPoint()
//{
//    QPoint point;

//    return *point;
//    //return new ();
//}
