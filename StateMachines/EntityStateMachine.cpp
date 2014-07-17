#include "EntityStateMachine.h"
#include "State.h"
#include <cassert>

void EntityStateMachine::ChangeState(EntityState* pNewState) {
   //make sure both states are both valid before attempting to
  //call their methods
  assert (_pCurrentState && pNewState);

  //call the exit method of the existing state
  _pCurrentState->Exit(_pEntity);

  //change state to the new state
  _pCurrentState = pNewState;

  //call the entry method of the new state
  _pCurrentState->Enter(_pEntity);
}


EntityStateMachine::~EntityStateMachine() {
    return;
}

EntityStateMachine::EntityStateMachine(Bot::Entity* pEntity, EntityState* pCurrentState)
    : _pCurrentState(pCurrentState), _pEntity(pEntity)
{ 
    return;
}

void EntityStateMachine::Update() {
    if (_pCurrentState)
    {
        _pCurrentState->Execute(_pEntity);
    }
}
