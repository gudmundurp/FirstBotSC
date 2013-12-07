#ifndef SCV_STATES_H
#define SCV_STATES_H
#include "../State.h"

#include <string>

class SCV;

//------------------------------------

#define CreateState(stateName) \
   class stateName : public State<SCV> \
   { \
private: \
  stateName(){} \
  stateName(const stateName&); \
  stateName& operator=(const stateName&); \
public: \
  static stateName* Instance(); \
  virtual void Enter(SCV* scv); \
  virtual void Execute(SCV* scv); \
  virtual void Exit(SCV* scv); \
  virtual std::string getName(); \
};

CreateState(Idle);
CreateState(Mining);

class GoingToBuildSupplyDepot : public State<SCV>
{
private:
     GoingToBuildSupplyDepot(){}
     GoingToBuildSupplyDepot(const GoingToBuildSupplyDepot&);
     GoingToBuildSupplyDepot& operator=(const GoingToBuildSupplyDepot&);
public:
  static GoingToBuildSupplyDepot* Instance();
  virtual void Enter(SCV* scv);
  virtual void Execute(SCV* scv);
  virtual void Exit(SCV* scv);
  virtual std::string getName();
};

class BuildingSupplyDepot : public State<SCV>
{
private:
     BuildingSupplyDepot(){}
     BuildingSupplyDepot(const BuildingSupplyDepot&);
     BuildingSupplyDepot& operator=(const BuildingSupplyDepot&);
public:
  static BuildingSupplyDepot* Instance();
  virtual void Enter(SCV* scv);
  virtual void Execute(SCV* scv);
  virtual void Exit(SCV* scv);
  virtual std::string getName();
};

#endif
