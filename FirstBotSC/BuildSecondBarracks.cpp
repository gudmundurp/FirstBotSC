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
			int countSCVsGoingToBuildBarracks = 0; // Take care of this here for now.
			for (auto unit : BWAPI::Broodwar->self()->getUnits()) {
				if (!unit->exists()) {
					continue;
				}

				if (unit->getType() == BWAPI::UnitTypes::Terran_SCV) {
					if (unit->getBuildType() == BWAPI::UnitTypes::Terran_Barracks) {
						countBarracksUnderConstruction++;
					} else if (unit->getLastCommand().getType() == BWAPI::UnitCommandTypes::Build
							&& unit->getLastCommand().getUnitType() == BWAPI::UnitTypes::Terran_Barracks) {
						// Naive accounting for SCVs that have possible been commanded to build barracks but not yet started.
						countSCVsGoingToBuildBarracks++;
					}
				}
			}

			if (countSCVsGoingToBuildBarracks + countBarracksUnderConstruction + GetUnitCount(UnitTypeEnum::Terran_Barracks) < 2) {
				return BuildBarracks;
			}
        }
    }

    return Nothing;
}

}