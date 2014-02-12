#ifndef WORLD_H
#define WORLD_H

class SCV;

class World {
public:
    typedef int Resource;
    typedef Resource ResourceTicket;

    typedef enum  {
        SupplyDepot
    } Object;

    virtual int getMinerals() =0;

    virtual ResourceTicket reserve(const Resource) =0;
    virtual void expend(ResourceTicket) =0;

    virtual void order(SCV*, Object) =0;

    virtual bool startedBuilding(SCV*) =0;

    virtual void startMining(SCV*) = 0;

    virtual int unusedSupply() = 0;
};

#endif
