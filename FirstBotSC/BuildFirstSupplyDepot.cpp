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
    if (GetUnitCount(UnitTypeEnum::Terran_Supply_Depot)) {
         Done();
         return Nothing;
    }

    if (_haveIssuedMyAdvice) {
        return Nothing;
    }
    
	if (GetCurrent() >= 18 && GetMaximum() == 20) {
	    if(GetMinerals() >=100) {
            _haveIssuedMyAdvice = true;
	        return BuildSD;
	    }
	}

    return Nothing;
}

}