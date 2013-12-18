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

void MockWorld::reduceReservedMinerals(int minerals) {
      this->minerals -= minerals;
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

void MockWorld::reserveMinerals(int minerals) {
    this->minerals-=minerals;
}

void MockWorld::reserve(SCV*, const Resource resource){
  reserved += resource;
}

void MockWorld::expend(SCV*){
  this->minerals -= this->reserved;
  this->reserved = 0;
}

void MockWorld::order(SCV*, const Object&){}
void MockWorld::order(SCV*, const SupplyDepot&){}