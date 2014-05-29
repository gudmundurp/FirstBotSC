#pragma once

#include "strategystage.h"

namespace strategy {

class RushStrategy :
    public StrategyStage
{
public:
    RushStrategy(void);
    virtual ~RushStrategy(void);

    Advice GetAdvice();

};

}
