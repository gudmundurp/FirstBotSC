#include "WorldImpl.h"
#include "SCV/SCV.h"
#include "BWAPI.h"
#include "BWAPI/Unit.h"

WorldImpl::WorldImpl() 
    : reservedMinerals(0)
{}

int  WorldImpl::getMinerals() {
    return BWAPI::Broodwar->self()->minerals() - reservedMinerals;
}

World::ResourceTicket WorldImpl::reserve(const Resource minerals) {
    reservedMinerals += minerals;
    return minerals;
}
void WorldImpl::expend(World::ResourceTicket ticket) {
    reservedMinerals -= ticket;
}

void WorldImpl::order(SCV* scv, Object obj) {
  using namespace BWAPI;
  using namespace Filter;

    if (obj != SupplyDepot) {
        Broodwar << "Error not building supplydepot." << std::endl;
        return;
    }

    Unit scv_bw = Broodwar->getUnit(scv->getID());

    TilePosition targetBuildLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, scv_bw->getTilePosition());
              if ( targetBuildLocation )
              {
                scv_bw->build( UnitTypes::Terran_Supply_Depot, targetBuildLocation );
              }
}

bool WorldImpl::startedBuilding(SCV*) { return false; }
void WorldImpl::startMining(SCV* scv) {
  using namespace BWAPI;
  using namespace Filter;

  Unit u = Broodwar->getUnit(scv->getID());

  if ( u->isIdle() )
  {
        if ( u->isCarryingGas() || u->isCarryingMinerals() )
        {
          u->returnCargo();
        }
        u->gather( u->getClosestUnit( IsMineralField || IsRefinery ));
  }
}

int WorldImpl::unusedSupply() {
    return 2;
}
