#include "RushStrategy.h"

namespace strategy {

RushStrategy::RushStrategy(void)
    : StrategyStage("RushStrategy")
{
}


RushStrategy::~RushStrategy(void)
{
}

Advice RushStrategy::GetAdvice()
{
    if((GetCurrent() >= GetMaximum())) return Attack;

    if ((GetMinerals() >= 50)) {
        return TrainMarine;
    }

    return Nothing;
}

}