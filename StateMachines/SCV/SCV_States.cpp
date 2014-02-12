#include "SCV_States.h"
#include "../State.h"
#include "SCV.h"
#include "BWAPI.h"
#include <iostream>
#include <string>

#define LOG(state, action, unit) do { BWAPI::Broodwar->printf("%08d %s %s", unit->getID(), state, action); } while(false)

Idle* Idle::instance;

//-------------------------------------------
Idle* Idle::Instance()
{
  if(!instance) instance = new Idle();
  return instance;
}

std::string Idle::getName()
{
    return "Idle";
}

void Idle::Enter(SCV* scv)
{
   std::cout << "Entering idle state ...";
}

void Idle::Execute(SCV* scv)
{
    std::cout << "Executing idle state ...";
    scv->ChangeState(Mining::Instance());
}

void Idle::Exit(SCV* scv)
{
    std::cout << "Leaving idle state ...";
}

//-------------------------------------------
Mining* Mining::instance;

//-------------------------------------------
Mining* Mining::Instance()
{
  if(!instance) instance = new Mining();
  return instance;
}

std::string Mining::getName()
{
    return "Mining";
}

void Mining::Enter(SCV* scv)
{
    LOG("Mining", "Enter", scv);
}

void Mining::Execute(SCV* scv)
{
    //LOG("Mining", "Execute", scv);
    if (scv->checkMinerals() >= 100 && scv->unusedSupply() <= 6) {
        scv->reserveMinerals(100);
        scv->ChangeState(GoingToBuildSupplyDepot::Instance());
    //else if !LackingSupply and
    //        SuppDep >=
    //        Minerals >= 150
    //   then Build Barracks
    } else {
        scv->startMining();
    }
}

void Mining::Exit(SCV* scv)
{
    LOG("Mining", "Exit", scv);
    //No action required
}

GoingToBuildSupplyDepot* GoingToBuildSupplyDepot::instance;

//-------------------------------------------
GoingToBuildSupplyDepot* GoingToBuildSupplyDepot::Instance()
{
  if(!instance) instance = new GoingToBuildSupplyDepot();
  return instance;
}


std::string GoingToBuildSupplyDepot::getName()
{
    return "GoingToBuildSupplyDepot";
}

void GoingToBuildSupplyDepot::Enter(SCV* scv)
{
    LOG("GoingToBuildSupplyDepot", "Enter", scv);
    World* world = scv->getWorld();

    world->order(scv, World::SupplyDepot);
}

void GoingToBuildSupplyDepot::Execute(SCV* scv)
{
    //LOG("GoingToBuildSupplyDepot", "Execute", scv);
    BWAPI::Unit scv_bw = BWAPI::Broodwar->getUnit(scv->getID());
    int x = scv_bw->getOrder();
    if(scv_bw->getBuildUnit()) {
        scv->unreserveMinerals();
    } else if(!scv_bw->isConstructing()) {
        scv->ChangeState(Mining::Instance());
    } else {
        // Is constructing or on way to site.
        int i=0;
    }
}

void GoingToBuildSupplyDepot::Exit(SCV* scv)
{
LOG("GoingToBuildSupplyDepot", "Exit", scv);
}

//-------------------------------------------
BuildingSupplyDepot* BuildingSupplyDepot::instance;

//-------------------------------------------
BuildingSupplyDepot* BuildingSupplyDepot::Instance()
{
  if(!instance) instance = new BuildingSupplyDepot();
  return instance;
}

std::string BuildingSupplyDepot::getName()
{
    return "BuildingSupplyDepot";
}

void BuildingSupplyDepot::Enter(SCV* scv)
{
}

void BuildingSupplyDepot::Execute(SCV* scv)
{
}

void BuildingSupplyDepot::Exit(SCV* scv)
{
}
