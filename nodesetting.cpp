#include "nodesetting.h"

NodeSetting::NodeSetting(int node, bool active, int up, int down)
{
    this->node = node;
    this->active = active;
    this->up = up;
    this->down = down;
}

int NodeSetting::getDown() const
{
    return down;
}

int NodeSetting::getUp() const
{
    return up;
}

bool NodeSetting::getActive() const
{
    return active;
}

int NodeSetting::getNode() const
{
    return node;
}
