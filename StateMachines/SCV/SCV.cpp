#include "SCV_States.h"
#include "SCV.h"
#include "BWAPI.h"
#include "World.h"
#include <string>
#include <cassert>

SCV::SCV(int id, World* world) 
    : Entity(Idle::Instance()),
      _id(id),
      _pCurrentState(Idle::Instance()),
      _world(world)
{
  _triedToBuildSupplyDepot = false;
}

int  SCV::getID() { return _id; }

void SCV::Update()
{
    if (GetSM())
    {
        GetSM()->Update();
    }
}

std::string SCV::GetStateName()
{
    //return _pCurrentState->getName();
    return "";
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
    return _world->unusedSupply();
}

void SCV::build(BWAPI::UnitType type, BWAPI::TilePosition targetBuildLocation)
{
    _world->reserve(type.mineralPrice());
    auto u = BWAPI::Broodwar->getUnit(_id);
    GetSM()->ChangeState(GoingToBuildSupplyDepot::Instance());
    u->build(type,targetBuildLocation);
    //Dispatch
}

void SCV::nothing()
{

}

bool SCV::startedBuilding()
{
    return _world->startedBuilding(this);
}

void SCV::reserveMinerals(int minerals)
{
    _world->reserve(100);
}

void SCV::unreserveMinerals()
{
    _world->expend(100);
}

void SCV::buildSupplyDepot() {
    
}

void SCV::startMining() {
    _world->startMining(this);
}

World* SCV::getWorld() {
    return _world;
}

bool SCV::hasBuildUnit() {
    BWAPI::Unit scv_bw = BWAPI::Broodwar->getUnit(getID());
	return scv_bw->getBuildUnit();
}

bool SCV::isConstructing() {
	BWAPI::Unit scv_bw = BWAPI::Broodwar->getUnit(getID());
    return scv_bw->isConstructing();
}

bool SCV::isIdle() {
	BWAPI::Unit scv_bw = BWAPI::Broodwar->getUnit(getID());
	return scv_bw->isIdle();
}

void SCV::EnterFrame() {
    
}

void SCV::LeaveFrame(Advice advice) {
    
}
