#ifndef WORLD_H
#define WORLD_H

class World {
public:
    virtual void reduceReservedMinerals(int minerals) =0;

    virtual void reserveMinerals(int minerals) =0;

    virtual int getMinerals() =0;
};

#endif
