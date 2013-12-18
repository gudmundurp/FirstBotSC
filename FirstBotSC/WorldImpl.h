#ifndef WORLDIMPL_H
#define WORLDIMPL_H

#include "World.h"

class WorldImpl : public World {

public:
void reduceReservedMinerals(int minerals) ;

void reserveMinerals(int minerals) ;

int getMinerals() ;

void reserve(SCV*, const Resource) ;
void expend(SCV*) ;

void order(SCV*, const Object&) ;
void order(SCV*, const SupplyDepot&) ;
};

#endif