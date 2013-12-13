#ifndef MOCKWORLD_H
#define MOCKWORLD_H

#include "World.h"

class MockWorld : public World {
private:
    int minerals;
    int supplies;
    int usedSupplies;

public:
    void setMinerals(int minerals);
    void reduceReservedMinerals(int minerals);
    void setSupplies(int supplies);
    void setUsedSupplies(int usedSupplies);

    void reserveMinerals(int minerals);

    int getMinerals();
};

#endif