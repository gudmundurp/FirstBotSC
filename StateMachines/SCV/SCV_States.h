#ifndef SCV_STATES_H
#define SCV_STATES_H
#include "../State.h"

#include <string>

class SCV;

//------------------------------------
class Idle : public State<SCV>
{
private:
  static Idle* instance;
  Idle(): State<SCV>("Idle"){}
public:
  static Idle* Instance();
  virtual void Enter(SCV* scv);
  virtual void Execute(SCV* scv);
  virtual void Exit(SCV* scv);
  virtual std::string getName();
};

class Mining : public State<SCV>
{
private:
  static Mining* instance;
  Mining(): State<SCV>("Mining"){}
public:
  static Mining* Instance();
  virtual void Enter(SCV* scv);
  virtual void Execute(SCV* scv);
  virtual void Exit(SCV* scv);
  virtual std::string getName();
};

class GoingToBuildSupplyDepot : public State<SCV>
{
private:
    static GoingToBuildSupplyDepot* instance;
     GoingToBuildSupplyDepot(): State<SCV>("GoingToBuildSupplyDepot"){}
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
  static BuildingSupplyDepot* instance;
     BuildingSupplyDepot(): State<SCV>("BuildingSupplyDepot"){}
public:
  static BuildingSupplyDepot* Instance();
  virtual void Enter(SCV* scv);
  virtual void Execute(SCV* scv);
  virtual void Exit(SCV* scv);
  virtual std::string getName();
};

#endif
