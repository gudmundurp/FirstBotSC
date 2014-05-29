#pragma once

#include "strategystage.h"

namespace strategy {

class BuildSecondSupplyDepot :
    public StrategyStage
{
public:
    BuildSecondSupplyDepot(void);
    virtual ~BuildSecondSupplyDepot(void);

    Advice GetAdvice();

};

}
