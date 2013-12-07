#include "State.h"

class SCV;

//------------------------------------

class Idle : public State<SCV>
{
private:

  EnterMineAndDigForNugget(){}

  EnterMineAndDigForNugget(const EnterMineAndDigForNugget&);
  EnterMineAndDigForNugget& operator=(const EnterMineAndDigForNugget&);

};
