#pragma once

#include "BWAPI.h"
#include "World.h"
#include "Entity.h"
#include <string>

class SCV : public Bot::Entity {

private:

    EntityState* _pCurrentState;
    bool _triedToBuildSupplyDepot;
    World* const _world;
    int _id;

public:
    int getID();
    SCV(int id, World* world);

    void Update();
    //void ChangeState(EntityState* new_state);

    void TryToBuildSupplyDepot();

    int checkMinerals();
    int unusedSupply();
    void nothing();
    void startMining();
    bool startedBuilding();

    void reserveMinerals(int minerals);
    void unreserveMinerals();

    void build(BWAPI::UnitType type, BWAPI::TilePosition targetBuildLocation);

    void buildSupplyDepot();

    World* getWorld();

    bool DidTryToBuildSupplyDepot();
    std::string GetStateName();

    virtual void EnterFrame();
    virtual void LeaveFrame(Advice advice);

    bool hasBuildUnit();
    bool isConstructing();
    bool isIdle();

private:
#ifdef FIRSTBOT_UNIT_TEST
    int unittest_state;
#endif
};

