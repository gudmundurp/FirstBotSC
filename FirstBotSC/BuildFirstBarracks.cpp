#include "BuildFirstBarracks.h"

namespace strategy {

BuildFirstBarracks::BuildFirstBarracks(void)
    : StrategyStage("BuildFirstBarracks")
{
}


BuildFirstBarracks::~BuildFirstBarracks(void)
{
}

Advice BuildFirstBarracks::GetAdvice()
{
    if(GetUnitCount(UnitTypeEnum::Terran_Barracks) >= 1) {
        Done();
        return Nothing;
    } else if (GetCurrent() >= 22) {
        if(GetMinerals() >= 150) {
			int countBarracksUnderConstruction = 0; // Take care of this here for now.
			for (auto unit : BWAPI::Broodwar->self()->getUnits()) {
				if (!unit->exists()) {
					continue;
				}

				if (unit->getType() == BWAPI::UnitTypes::Terran_SCV && unit->getBuildType() == BWAPI::UnitTypes::Terran_Barracks) {
					countBarracksUnderConstruction++;
				}
			}

			if (!countBarracksUnderConstruction) {
				return BuildBarracks;
			}
        }
    }

    return Nothing;
}

}