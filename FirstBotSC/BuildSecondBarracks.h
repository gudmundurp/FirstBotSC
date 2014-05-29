#pragma once

#include "strategystage.h"

namespace strategy {

class BuildSecondBarracks :
    public StrategyStage
{
public:
    BuildSecondBarracks(void);
    virtual ~BuildSecondBarracks(void);

    Advice GetAdvice();

};

}
