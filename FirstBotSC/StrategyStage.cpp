#include "StrategyStage.h"
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
		if (u->getType() == unitTypeID) {
			count++;
		}
	}
	return count;
}

}
