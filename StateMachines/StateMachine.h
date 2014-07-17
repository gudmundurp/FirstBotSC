#pragma once

class StateMachine {
public:
    virtual void ChangeState(void* new_state) = 0;
    virtual ~StateMachine() { return; }

protected:
    StateMachine() { return; }
};