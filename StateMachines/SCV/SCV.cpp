#include "SCV_States.h"
#include "SCV.h"
#include "../World.h"
#include <string>
#include <cassert>

SCV::SCV(int id, World* world) : _pCurrentState(Idle::Instance()), _world(world) {_triedToBuildSupplyDepot = false;}

void SCV::Update()
{
  if (_pCurrentState)
  {
    _pCurrentState->Execute(this);
  }
}

std::string SCV::GetStateName()
{
    return _pCurrentState->getName();
}

void SCV::ChangeState(State<SCV>* pNewState)
{
  //make sure both states are both valid before attempting to
  //call their methods
  assert (_pCurrentState && pNewState);

  //call the exit method of the existing state
  _pCurrentState->Exit(this);

  //change state to the new state
  _pCurrentState = pNewState;

  //call the entry method of the new state
  _pCurrentState->Enter(this);
}

void SCV::TryToBuildSupplyDepot()
{
    this->_triedToBuildSupplyDepot = true;
}

bool SCV::DidTryToBuildSupplyDepot()
{
    return this->_triedToBuildSupplyDepot;
}

int SCV::checkMinerals()
{
    return _world->getMinerals();
}

int SCV::unusedSupply()
{
    return 2;
}

void SCV::nothing()
{

}

void SCV::startedBuilding()
{
    this->_startedBuilding = true;
}

void SCV::reserveMinerals(int minerals)
{
    _world->reserveMinerals(100);
}

void SCV::unreserveMinerals(int minerals)
{
    _world->reduceReservedMinerals(100);
}
