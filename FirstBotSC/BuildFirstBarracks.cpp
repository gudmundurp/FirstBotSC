#include "BuildFirstBarracks.h"

namespace strategy {

BuildFirstBarracks::BuildFirstBarracks(void)
    : StrategyStage("BuildFirstBarracks")
{
}


BuildFirstBarracks::~BuildFirstBarracks(void)
{
}

Advice BuildFirstBarracks::GetAdvice()
{
    if(GetUnitCount(UnitTypeEnum::Terran_Barracks)) {
        Done();
        return Nothing;
    }

    if (_haveIssuedMyAdvice) {
        return Nothing;
    }

    if (GetCurrent() >= 22 && GetMaximum() == 36) {
        if(GetMinerals() >= 150) {
            _haveIssuedMyAdvice = true;
            return BuildBarracks;
        }
    }

    return Nothing;
}

}