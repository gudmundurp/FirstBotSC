#include "MockWorld.h"

void MockWorld::setMinerals(int minerals) {
    this->minerals = minerals;
}

void MockWorld::reduceReservedMinerals(int minerals) {
    this->minerals -= minerals;
}

int MockWorld::getMinerals() {
    return this->minerals;
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