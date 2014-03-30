#ifndef STATE_H
#define STATE_H

#include<string>

template<class unit_type>

class State
{
protected:
    State(const std::string& name) : name(name) {}
public:
    virtual void Enter(unit_type* t) =0;
    virtual void Execute(unit_type* t)=0;
    virtual void Exit(unit_type* t)=0;
	
    virtual std::string getName() { return name; };

    virtual ~State(){}

private:
    const std::string name;
};
#endif
