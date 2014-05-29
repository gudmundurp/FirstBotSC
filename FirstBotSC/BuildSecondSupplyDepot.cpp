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
    if (_haveIssuedMyAdvice) {
        return Nothing;
    }

    if (GetUnitCount(UnitTypeEnum::Terran_Supply_Depot) < 2) {
	    if (GetCurrent() >= 30 && GetMaximum() == 36) {
	        if (GetMinerals() >= 100) {
                _haveIssuedMyAdvice = true;
	            return BuildSD;
	        }
	    }
    } else {
        Done();
    }

    return Nothing;
}

}