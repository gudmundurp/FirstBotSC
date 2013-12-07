#include "SCV_States.h"
#include "../State.h"
#include "SCV.h"
#include <iostream>
#include <string>

#define Implement(state, name) \
state* state::Instance() \
{ \
  static state instance; \
  return &instance; \
} \
std::string state::getName() \
{ \
    return name; \
}


//-------------------------------------------
Implement(Idle, "Idle")
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
Implement(Mining,"Mining");

void Mining::Enter(SCV* scv)
{
    //Gather gas/minerals
}

void Mining::Execute(SCV* scv)
{
    scv->TryToBuildSupplyDepot();
    scv->TryToBuildSupplyDepot();
    scv->checkMinerals() >= 100 &&
    scv->unusedSupply() <= 2
    ? scv->ChangeState(GoingToBuildSupplyDepot::Instance())
    : scv->nothing();
    //check if LackingSupply and if minerals > 100
    //   then Build Supply Depot
    //else if !LackingSupply and
    //        SuppDep >=
    //        Minerals >= 150
    //   then Build Barracks
    //else nothing
}

void Mining::Exit(SCV* scv)
{
    //No action required
}

Implement(GoingToBuildSupplyDepot,"GoingToBuildSupplyDepot")
void GoingToBuildSupplyDepot::Enter(SCV* scv)
{
    scv->reserveMinerals(100);
}

void GoingToBuildSupplyDepot::Execute(SCV* scv)
{
    if(scv->_startedBuilding) {
        scv->ChangeState(BuildingSupplyDepot::Instance());
    }
}

void GoingToBuildSupplyDepot::Exit(SCV* scv)
{
    scv->unreserveMinerals(100);
}

Implement(BuildingSupplyDepot,"BuildingSupplyDepot");
void BuildingSupplyDepot::Enter(SCV* scv)
{
}

void BuildingSupplyDepot::Execute(SCV* scv)
{
}

void BuildingSupplyDepot::Exit(SCV* scv)
{
}
