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
    if (GetUnitCount(UnitTypeEnum::Terran_Supply_Depot) >= 2) {
        Done();
        return Nothing;
    }
    if (_haveIssuedMyAdvice) {
        return Nothing;
    }

    if (GetCurrent() >= 30 && GetMaximum() == 36) {
        if (GetMinerals() >= 100) {
            _haveIssuedMyAdvice = true;
            return BuildSD;
        }
    }

    return Nothing;
}

}