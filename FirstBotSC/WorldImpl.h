#ifndef WORLDIMPL_H
#define WORLDIMPL_H

#include "World.h"

class WorldImpl : public World {

public:
    void reduceReservedMinerals(int minerals);

    void reserveMinerals(int minerals);

    int getMinerals();
};

#endif