#pragma once

#include "Advice.h"

class ManagerSM
{
public:
    virtual void update(Advice advice) = 0;

protected:
    ManagerSM() { return; };
    virtual ~ManagerSM() { return; }

};
