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

	int countBarracks = GetUnitCount(UnitTypeEnum::Terran_Barracks);
	int countMarines = GetUnitCount(UnitTypeEnum::Terran_Marine);

	int timeToBuildSD = BWAPI::Broodwar->getRemainingLatencyFrames() + estimateConstructionTime(UnitTypeEnum::Terran_Supply_Depot);
	double marineProductionToNewSupplyDepot = timeToBuildSD * countBarracks / (double)BWAPI::UnitTypes::Terran_Marine.buildTime();
	double scvProductionToNewSupplyDepot = timeToBuildSD * 1.0 / (double)BWAPI::UnitTypes::Terran_SCV.buildTime();
	
	if (GetMinerals() >= 100) {
		if (8 * countSDUnderConstruction + supply <= std::ceil(marineProductionToNewSupplyDepot + scvProductionToNewSupplyDepot)) {
			return BuildSD;
		}
	}

	if ( GetMinerals() >= std::max(200, 50 * countBarracks)) {
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
	if (countMarines >= 10) {
		return Attack;
	} else {
		return Nothing; // Defend
	}
}

}