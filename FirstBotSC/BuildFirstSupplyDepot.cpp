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
	if (GetCurrent() >= 18 && GetMaximum() == 20) {
	    if(GetMinerals() >=100) {
	        Done();
	        return BuildSD;
	    }
	}

    return Nothing;
}

}