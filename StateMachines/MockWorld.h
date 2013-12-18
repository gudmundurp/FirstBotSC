#ifndef MOCKWORLD_H
#define MOCKWORLD_H

#include "World.h"

class MockWorld : public World {
private:
    int minerals;
    int reserved;
    int supplies;
    int usedSupplies;

public:
    MockWorld();

    void setMinerals(int minerals);
    void reduceReservedMinerals(int minerals);
    void setSupplies(int supplies);
    void setUsedSupplies(int usedSupplies);

    void reserveMinerals(int minerals);

    int getMinerals();

    void buildSupplyDepot();

    void reserve(SCV*, const Resource);
    void expend(SCV*);
    
    void order(SCV*, const Object&);
    void order(SCV*, const SupplyDepot&);
};

#endif