#include "BuildSecondBarracks.h"

namespace strategy {

BuildSecondBarracks::BuildSecondBarracks(void)
    : StrategyStage("BuildSecondBarracks")
{
}


BuildSecondBarracks::~BuildSecondBarracks(void)
{
}

Advice BuildSecondBarracks::GetAdvice()
{
    if (GetUnitCount(UnitTypeEnum::Terran_Barracks) >= 2) {
        Done();
        return Nothing;
    } else if (GetCurrent() >= 18) {
        if(GetMinerals() >= 100) {
			int countBarracksUnderConstruction = 0; // Take care of this here for now.
			for (auto unit : BWAPI::Broodwar->self()->getUnits()) {
				if (!unit->exists()) {
					continue;
				}

				if (unit->getType() == BWAPI::UnitTypes::Terran_SCV && unit->getBuildType() == BWAPI::UnitTypes::Terran_Barracks) {
					countBarracksUnderConstruction++;
				}
			}

			if (countBarracksUnderConstruction + GetUnitCount(UnitTypeEnum::Terran_Barracks) < 2) {
				return BuildBarracks;
			}
        }
    }

    return Nothing;
}

}