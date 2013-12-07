#include "World.h"

World::World() {}

void World::setMinerals(int minerals) {
    this->minerals = minerals;
}

void World::reduceReservedMinerals(int minerals) {
    this->minerals -= minerals;
}

int World::getMinerals() {
    return this->minerals;
}

void World::setSupplies(int supplies) {
    this->supplies = supplies;
}

void World::setUsedSupplies(int usedSupplies) {
    this->usedSupplies = usedSupplies;
}

void World::reserveMinerals(int minerals) {
    this->minerals-=minerals;
}
