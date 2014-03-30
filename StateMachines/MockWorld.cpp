#include "MockWorld.h"

MockWorld::MockWorld()
  : minerals(0)
  , reserved(0)
  , supplies(0)
  , usedSupplies(0)
{
}

void MockWorld::setMinerals(int minerals) {
    this->minerals = minerals;
}

int MockWorld::getMinerals() {
    return minerals - reserved;
}

void MockWorld::setSupplies(int supplies) {
    this->supplies = supplies;
}

void MockWorld::setUsedSupplies(int usedSupplies) {
    this->usedSupplies = usedSupplies;
}

World::ResourceTicket MockWorld::reserve(const Resource resource){
  reserved += resource;
  return resource;
}

void MockWorld::expend(ResourceTicket ticket){
  this->reserved = 0;
}

void MockWorld::order(SCV*, Object){}


bool MockWorld::startedBuilding(SCV*) {
  return false;
}

void MockWorld::startMining(SCV*) {}

int MockWorld::unusedSupply() {
    return 2;
}
