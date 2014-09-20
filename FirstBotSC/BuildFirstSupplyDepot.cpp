#include "BuildFirstSupplyDepot.h"

namespace strategy {

BuildFirstSupplyDepot::BuildFirstSupplyDepot(void)
    : StrategyStage("BuildFirstSupplyDepot")
{
}


BuildFirstSupplyDepot::~BuildFirstSupplyDepot(void)
{
}

Advice BuildFirstSupplyDepot::GetAdvice()
{
    if (GetUnitCount(UnitTypeEnum::Terran_Supply_Depot)) {
         Done();
         return Nothing;
    } else if (GetCurrent() >= 18) {
	    if(GetMinerals() >=100) {

			int countSDUnderConstruction = 0; // Take care of this here for now.
			for (auto unit : BWAPI::Broodwar->self()->getUnits()) {
				if (!unit->exists()) {
					continue;
				}

				if (unit->getType() == BWAPI::UnitTypes::Terran_SCV && unit->getBuildType() == BWAPI::UnitTypes::Terran_Supply_Depot) {
					countSDUnderConstruction++;
				}
			}

			if (!countSDUnderConstruction) {
				return BuildSD;
			}
	    }
	}

    return Nothing;
}

}