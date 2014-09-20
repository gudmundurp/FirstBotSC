#include "RushStrategy.h"
#include "FirstBotSC.h"

namespace strategy {

RushStrategy::RushStrategy(void)
    : StrategyStage("RushStrategy")
{
}


RushStrategy::~RushStrategy(void)
{
}

Advice RushStrategy::GetAdvice()
{
	int supply = GetMaximum() - GetCurrent();
	int countSDUnderConstruction = 0; // Take care of this here for now.
	int countBarracksUnderConstruction = 0; // Take care of this here for now.
	for (auto unit : BWAPI::Broodwar->self()->getUnits()) {
		if (!unit->exists()) {
			continue;
		}

		if (unit->getType() == BWAPI::UnitTypes::Terran_SCV) {
			switch (unit->getBuildType()) {
				case BWAPI::UnitTypes::Enum::Terran_Supply_Depot :
					countSDUnderConstruction++;
					break;
				case BWAPI::UnitTypes::Enum::Terran_Barracks :
					countBarracksUnderConstruction++;
					break;
				default :
					break;
			}
		}
	}

	
	if ( supply < 2 && GetMinerals() >= 100 && !countSDUnderConstruction ) {
		return BuildSD;
	}

	int countBarracks = 0;
	int countMarines = 0;
	for (auto unit : BWAPI::Broodwar->self()->getUnits()) {
		if (!unit->exists()) {
			continue;
		}

		if (unit->getType() == BWAPI::UnitTypes::Terran_Barracks) {
			countBarracks++;
		} else if (unit->getType() == BWAPI::UnitTypes::Terran_Marine) {
			countMarines++;
		}
	}

	if ( GetMinerals() >= std::max(150, 50 * countBarracks) && countMarines / (double)countBarracks > 2.5 ) {
		if (!countBarracksUnderConstruction) {
			return BuildBarracks;
		}
	}

    if ( supply > 0 && GetMinerals() >= 50 ) {
		if (findTrainer(BWAPI::UnitTypes::Terran_Barracks)) {
			return TrainMarine;
		}
    }

	// Collect forces and attack in force.
	if (countMarines > 2 * supply) {
		return Attack;
	} else {
		return Nothing; // Defend
	}
}

}