#pragma once

#include <string>

#include "Oracle.h"
#include "BWAPINice.h"

namespace strategy {

using namespace BWAPINice;

class StrategyStage
{
public:
    virtual ~StrategyStage(void);

    virtual std::string GetName() const;

    virtual Advice GetAdvice() = 0;

    virtual bool isDone();


protected:
    StrategyStage(const std::string& name);


	Supply GetCurrent();
    Supply GetMaximum();
	Minerals GetMinerals();
    Gas GetGas();
    int GetUnitCount(UnitTypeEnum unitTypeID);

    void Done();

	static int StrategyStage::manhattanDistance(const BWAPI::TilePosition& a, const BWAPI::TilePosition& b);

	// unittype must be a building
	static int StrategyStage::estimateConstructionTime(UnitTypeEnum id);

private:
    const std::string _name;
    bool _isDone;
};

}
