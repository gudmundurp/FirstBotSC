#include "StrategyStage.h"
#include <BWAPI.h>

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

}
