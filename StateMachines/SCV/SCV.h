#ifndef SCV_H
#define SCV_H

#include "../State.h"
#include "../World.h"
#include <string>

class SCV {

private:

State<SCV>* _pCurrentState;
bool _triedToBuildSupplyDepot;
World* const _world;
int _id;

public:
  int getID();
  SCV(int id, World* world);

  void Update();
  void ChangeState(State<SCV>* new_state);

  void TryToBuildSupplyDepot();

  int checkMinerals();
  int unusedSupply();
  void nothing();
  void startMining();
  bool startedBuilding();

  void reserveMinerals(int minerals);
  void unreserveMinerals();
  void buildSupplyDepot();

  World* getWorld();

  bool DidTryToBuildSupplyDepot();
  std::string GetStateName();


  /////////////////////


  bool hasBuildUnit();
  bool isConstructing();

private:
#ifdef FIRSTBOT_UNIT_TEST
	int unittest_state;
#endif
};

#endif // SCV_H
