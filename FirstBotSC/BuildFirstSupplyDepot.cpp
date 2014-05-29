#include "BuildFirstSupplyDepot.h"

namespace strategy {

BuildFirstSupplyDepot::BuildFirstSupplyDepot(void)
    : StrategyStage("BuildFirstSupplyDepot")
{
}


BuildFirstSupplyDepot::~BuildFirstSupplyDepot(void)
{
}

Advice BuildFirstSupplyDepot::GetAdvice()
{
    if (_haveIssuedMyAdvice) {
        return Nothing;
    }

    if (!GetUnitCount(UnitTypeEnum::Terran_Supply_Depot)) {
	    if (GetCurrent() >= 18 && GetMaximum() == 20) {
	        if(GetMinerals() >=100) {
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