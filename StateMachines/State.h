#pragma once

#include "Entity.h"
#include <string>


class EntityState {
protected:
    EntityState(const std::string& name) : name(name) {}
public:
    virtual void Enter(Bot::Entity* t) =0;
    virtual void Execute(Bot::Entity* t)=0;
    virtual void Exit(Bot::Entity* t)=0;
	
    virtual std::string getName() { return name; }

    virtual ~EntityState(){}

private:
    const std::string name;
};
