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
  bool _startedBuilding;
  SCV(int id, World* world);

  void Update();
  void ChangeState(State<SCV>* new_state);

  void TryToBuildSupplyDepot();

  int checkMinerals();
  int unusedSupply();
  void nothing();
  void startedBuilding();

  void reserveMinerals(int minerals);
  void unreserveMinerals(int minerals);

  bool DidTryToBuildSupplyDepot();
  std::string GetStateName();

};

#endif // SCV_H
