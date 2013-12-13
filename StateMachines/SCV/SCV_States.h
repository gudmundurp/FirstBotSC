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
  Idle(){}
  Idle(const Idle&);
  Idle& operator=(const Idle&);
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
  Mining(){}
  Mining(const Mining&);
  Mining& operator=(const Mining&);
public: \
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
  static BuildingSupplyDepot* instance;
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
