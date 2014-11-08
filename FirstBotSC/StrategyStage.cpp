#include "StrategyStage.h"
#include "FirstBotSC.h"
#include <BWAPI.h>

using namespace BWAPI;

namespace strategy {

StrategyStage::StrategyStage(const std::string& name)
    : _name(name), _isDone(false)
{
}


StrategyStage::~StrategyStage(void)
{
}

std::string StrategyStage::GetName() const
{
    return _name;
}

bool StrategyStage::isDone()
{
    return _isDone;
}


Supply StrategyStage::GetCurrent()
{
    return BWAPI::Broodwar->self()->supplyUsed();
}

Supply StrategyStage::GetMaximum()
{
    return BWAPI::Broodwar->self()->supplyTotal();
}

Minerals StrategyStage::GetMinerals()
{
    return BWAPI::Broodwar->self()->minerals();
}

Gas StrategyStage::GetGas()
{
    return BWAPI::Broodwar->self()->gas();
}

void StrategyStage::Done()
{
    _isDone = true;
}

int StrategyStage::GetUnitCount(UnitTypeEnum unitTypeID)
{
	int count = 0;
	Unitset myUnits = Broodwar->self()->getUnits();
	for (Unitset::iterator u = myUnits.begin(); u != myUnits.end(); ++u) {
		if (!u->exists()) {
			continue;
		}
		if (u->getType() == unitTypeID && u->isCompleted()) {
			count++;
		}
	}
	return count;
}

// Manhattan distance is a good enough estimate of distances for SCVs in crowded bases.
int StrategyStage::manhattanDistance(const BWAPI::TilePosition& a, const BWAPI::TilePosition& b)
{
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

const double SCV_THROTLE_APPROXIMATION = 0.8;

// unittype must be a building
int StrategyStage::estimateConstructionTime(UnitTypeEnum id)
{
	using namespace BWAPI;

	BWAPI::UnitType unittype(id);
	
	BWAPI::Unit scv = findTrainer(BWAPI::UnitTypes::Terran_SCV);
	if (!scv) { 
		return -1;
	}
	TilePosition position = Broodwar->getBuildLocation(unittype, scv->getTilePosition());
	if (position != TilePositions::Invalid) {
		int distance = manhattanDistance(position, scv->getTilePosition());
		double approxSpeed = SCV_THROTLE_APPROXIMATION * UnitTypes::Terran_SCV.topSpeed();
		int travelTime = ceil(distance / approxSpeed);
		char buf[100] = {0};
		errno = 0;
		if (_snprintf(buf, sizeof(buf), "Travel time is %d", travelTime) > 0 || errno == ERANGE) {
			buf[sizeof(buf) - 1] = '\0';
			Broodwar->sendText(buf);
		}
		return ceil(distance / approxSpeed) + unittype.buildTime();
	} else {
		return -1;
	}
}

}
