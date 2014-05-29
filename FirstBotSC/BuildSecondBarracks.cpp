#include "BuildSecondBarracks.h"

namespace strategy {

BuildSecondBarracks::BuildSecondBarracks(void)
    : StrategyStage("BuildSecondBarracks")
{
}


BuildSecondBarracks::~BuildSecondBarracks(void)
{
}

Advice BuildSecondBarracks::GetAdvice()
{
    if (_haveIssuedMyAdvice) {
        return Nothing;
    }

    if (GetUnitCount(UnitTypeEnum::Terran_Barracks) < 2) {
	    if (GetCurrent() >= 26 && GetMaximum() == 36) {
	        if(GetMinerals() >= 150) {
	            _haveIssuedMyAdvice = true;
	            return BuildBarracks;
	        }
	    }
    } else {
        Done();
    }

    return Nothing;
}

}