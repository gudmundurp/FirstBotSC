#pragma once

class EntityState;

namespace Bot {
class Entity;
};

class EntityStateMachine {
public:
    EntityStateMachine(Bot::Entity* pEntity, EntityState* pCurrentState);
    virtual void ChangeState(EntityState* new_state);
    void Update();
    virtual ~EntityStateMachine();

private:
   EntityState* _pCurrentState;
   Bot::Entity* _pEntity;
};
