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

    void setSupplies(int supplies);
    void setUsedSupplies(int usedSupplies);

    int getMinerals();

    void buildSupplyDepot();

    World::ResourceTicket reserve(const Resource);
    void expend(ResourceTicket);
    
    void order(SCV*, Object);

    bool startedBuilding(SCV*);
    void startMining(SCV*);

    int unusedSupply();
};

#endif