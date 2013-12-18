#include "WorldImpl.h"

void WorldImpl::reduceReservedMinerals(int minerals) {}
void WorldImpl::reserveMinerals(int minerals) {}
int  WorldImpl::getMinerals() { return 0; }
void WorldImpl::reserve(SCV*, const Resource) {}
void WorldImpl::expend(SCV*) {}
void WorldImpl::order(SCV*, const Object&) {}
void WorldImpl::order(SCV*, const SupplyDepot&) {}