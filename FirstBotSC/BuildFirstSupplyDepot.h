#pragma once

#include "strategystage.h"

namespace strategy {

class BuildFirstSupplyDepot :
    public StrategyStage
{
public:
    BuildFirstSupplyDepot(void);
    virtual ~BuildFirstSupplyDepot(void);

    Advice GetAdvice();

};

}
