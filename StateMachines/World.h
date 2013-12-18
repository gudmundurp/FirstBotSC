#ifndef WORLD_H
#define WORLD_H

class SCV;

class World {
public:
    typedef int Resource;

    class Object {
    };
    class SupplyDepot : public Object{
    };

    virtual void reduceReservedMinerals(int minerals) =0;

    virtual void reserveMinerals(int minerals) =0;

    virtual int getMinerals() =0;

    virtual void reserve(SCV*, const Resource) =0;
    virtual void expend(SCV*) =0;

    virtual void order(SCV*, const Object&) =0;
    virtual void order(SCV*, const SupplyDepot&) =0;
};

#endif
