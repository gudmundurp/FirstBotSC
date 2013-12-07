#ifndef WORLD_H
#define WORLD_H

class World {
private:
    int minerals;
    int supplies;
    int usedSupplies;

public:
    World();
    void setMinerals(int minerals);
    void reduceReservedMinerals(int minerals);
    void setSupplies(int supplies);
    void setUsedSupplies(int usedSupplies);

    void reserveMinerals(int minerals);

    int getMinerals();
};

#endif
