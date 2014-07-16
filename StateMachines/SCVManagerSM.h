#pragma once;

#include "ManagerSM.h"
#include "BWAPI.h"

using namespace BWAPI;

class SCVManagerSM : public ManagerSM
{
public:
    virtual void update(Advice advice);

private:
    Unit findTrainer(UnitType type);
    void build(BWAPI::UnitType type);
};

