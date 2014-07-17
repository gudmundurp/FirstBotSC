#pragma once

#include "Advice.h"
#include "EntityStateMachine.h"

namespace Bot {

class Entity {
public:
    virtual void EnterFrame()=0;
    //virtual void LeaveFrame(Advice advice)=0;

    virtual ~Entity() { return; }

    EntityStateMachine* GetSM() { return &_entitySM; }

protected:
    Entity(EntityState* pInitialState)
        : _entitySM(this, pInitialState)
    { return; }

    EntityStateMachine _entitySM;
};

};