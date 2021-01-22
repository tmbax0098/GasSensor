#ifndef NODESETTING_H
#define NODESETTING_H

#include <QObject>

class NodeSetting : public QObject
{
    Q_OBJECT
public:
    explicit NodeSetting(int node , bool active , int up , int down);

    int getDown() const;

    int getUp() const;

    bool getActive() const;

    int getNode() const;

signals:


private:
    int node;
    bool active;
    int up;
    int down;

};

#endif // NODESETTING_H
