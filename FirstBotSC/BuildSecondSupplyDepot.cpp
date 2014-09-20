#include "BuildSecondSupplyDepot.h"

namespace strategy {

BuildSecondSupplyDepot::BuildSecondSupplyDepot(void)
    : StrategyStage("BuildSecondSupplyDepot")
{
}


BuildSecondSupplyDepot::~BuildSecondSupplyDepot(void)
{
}

Advice BuildSecondSupplyDepot::GetAdvice()
{
    if (GetUnitCount(UnitTypeEnum::Terran_Supply_Depot) >= 2) {
        Done();
        return Nothing;
    } else if (GetCurrent() >= 30) {
        if (GetMinerals() >= 100) {
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