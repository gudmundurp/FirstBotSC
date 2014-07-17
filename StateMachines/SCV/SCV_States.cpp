#include "SCV_States.h"
#include "State.h"
#include "SCV.h"
#include <iostream>
#include <string>

/*#ifndef FIRSTBOT_UNIT_TEST
   #include "BWAPI.h"
   #define LOG(state, action, unit) do { BWAPI::Broodwar->printf("%08d %s %s", unit->getID(), state, action); } while(false)
#else*/
   #define LOG(state, action, unit) 
//#endif

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

void Idle::Enter(Entity *scv)
{
   std::cout << "Entering idle state ...";
}

void Idle::Execute(Entity *scv)
{
    std::cout << "Executing idle state ...";
    scv->GetSM()->ChangeState(Mining::Instance());
}

void Idle::Exit(Entity *scv)
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

void Mining::Enter(Entity *scv)
{
    LOG("Mining", "Enter", scv);
}

void Mining::Execute(Entity *scv)
{
    //LOG("Mining", "Execute", scv);
    /*
    if (scv->checkMinerals() >= 100 && scv->unusedSupply() <= 6) {
        scv->reserveMinerals(100);
        scv->ChangeState(GoingToBuildSupplyDepot::Instance());*/
    //else if !LackingSupply and
    //        SuppDep >=
    //        Minerals >= 150
    //   then Build Barracks
    /*
    } else {*/
        ((SCV*)scv)->startMining();
    //}
}

void Mining::Exit(Entity *scv)
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

void GoingToBuildSupplyDepot::Enter(Entity *scv)
{
    LOG("GoingToBuildSupplyDepot", "Enter", scv);
    World* world = ((SCV*)scv)->getWorld();

    world->order(((SCV*)scv), World::SupplyDepot);
}

void GoingToBuildSupplyDepot::Execute(Entity *scv)
{
    //LOG("GoingToBuildSupplyDepot", "Execute", scv);
    if(((SCV*)scv)->hasBuildUnit()) {
        ((SCV*)scv)->unreserveMinerals();
    } else if(!((SCV*)scv)->isConstructing()&&((SCV*)scv)->isIdle()) {
        ((SCV*)scv)->GetSM()->ChangeState(Mining::Instance());
    } else {
        // Is constructing or on way to site.
    }
}

void GoingToBuildSupplyDepot::Exit(Entity *scv)
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

void BuildingSupplyDepot::Enter(Entity *scv)
{
}

void BuildingSupplyDepot::Execute(Entity *scv)
{
}

void BuildingSupplyDepot::Exit(Entity *scv)
{
}
