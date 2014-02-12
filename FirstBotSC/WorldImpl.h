#ifndef WORLDIMPL_H
#define WORLDIMPL_H

#include "World.h"
#include "BWAPI/Game.h"
#include "BWAPI/Player.h"

class WorldImpl : public World {

  typedef BWAPI::PlayerInterface Player;
  typedef BWAPI::Game Game;

public:
    WorldImpl();

    int getMinerals() ;

    ResourceTicket reserve(const Resource);
    void expend(ResourceTicket);

    void order(SCV*, Object);

    void startMining(SCV*);

    bool startedBuilding(SCV*);

    int unusedSupply();

private:
    int reservedMinerals;
};

#endif