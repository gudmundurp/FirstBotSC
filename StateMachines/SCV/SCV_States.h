#pragma once

#include "State.h"
#include <string>

//namespace Bot {
//class Entity;
//};
using Bot::Entity;

//------------------------------------
class Idle : public EntityState
{
private:
  static Idle* instance;
  Idle(): EntityState("Idle"){}
public:
  static Idle* Instance();
  virtual void Enter(Entity *scv);
  virtual void Execute(Entity *scv);
  virtual void Exit(Entity *scv);
  virtual std::string getName();
};

class Mining : public EntityState
{
private:
  static Mining* instance;
  Mining(): EntityState("Mining"){}
public:
  static Mining* Instance();
  virtual void Enter(Entity *scv);
  virtual void Execute(Entity *scv);
  virtual void Exit(Entity *scv);
  virtual std::string getName();
};

class GoingToBuildSupplyDepot : public EntityState
{
private:
    static GoingToBuildSupplyDepot* instance;
     GoingToBuildSupplyDepot(): EntityState("GoingToBuildSupplyDepot"){}
public:
  static GoingToBuildSupplyDepot* Instance();
  virtual void Enter(Entity *scv);
  virtual void Execute(Entity *scv);
  virtual void Exit(Entity *scv);
  virtual std::string getName();
};

class BuildingSupplyDepot : public EntityState
{
private:
  static BuildingSupplyDepot* instance;
     BuildingSupplyDepot(): EntityState("BuildingSupplyDepot"){}
public:
  static BuildingSupplyDepot* Instance();
  virtual void Enter(Entity *scv);
  virtual void Execute(Entity *scv);
  virtual void Exit(Entity *scv);
  virtual std::string getName();
};

