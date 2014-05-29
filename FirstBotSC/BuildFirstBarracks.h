#pragma once

#include "strategystage.h"

namespace strategy {

class BuildFirstBarracks :
    public StrategyStage
{
public:
    BuildFirstBarracks(void);
    virtual ~BuildFirstBarracks(void);

    Advice GetAdvice();

};

}
