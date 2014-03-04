// This is the AcceptanceTestBot DLL file.

#include "AcceptanceTestBot.h"

using namespace BWAPI;
using namespace UnitTypes::Enum;
using namespace Filter;

Unitset workerSet;
int AcceptanceTestBotWorker = 0;
int AcceptanceTestBotResourceDepot = 0;
int reservedMinerals = 0;
bool initialFrame = true;


void AcceptanceTestBot :: onStart() {
  Broodwar->sendText("Hello world!");

  Broodwar->enableFlag(Flag::UserInput);

  // Uncomment the following line and the bot will know about everything through the fog of war (cheat).
  Broodwar->enableFlag(Flag::CompleteMapInformation);

  // Set the command optimization level so that common commands can be grouped
  // and reduce the bot's APM (Actions Per Minute).
  Broodwar->setCommandOptimizationLevel(2);
}

typedef enum { PENDING, FAILED, SUCCESS } TestResult;

TestResult result = PENDING;

void AcceptanceTestBot :: onFrame() {
    // Called once every game frame

	const char* testResult;
	switch (result) {
	case SUCCESS:
		testResult = "Success";
		break;
	case FAILED:
		testResult = "Failed";
		break;
	case PENDING:
	default:
		testResult = "In Progress";
		break;
	}

	Broodwar->drawTextScreen(300, 0,  "Test result: %s", testResult );

  // Return if the game is a replay or is paused
  if ( Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self() )
    return;

  // Prevent spamming by only running our onFrame once every number of latency frames.
  // Latency frames are the number of frames before commands are processed.
  if ( Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0 )
    return;

  if ( Broodwar->getFrameCount() >= (int)((3*60*1000)/42.0 + 0.5) ) {
	  Broodwar->leaveGame();
  }

  // Iterate through all the units that we own
  Unitset myUnits = Broodwar->getAllUnits();
  for ( Unitset::iterator u = myUnits.begin(); u != myUnits.end(); ++u )
  {
	  if( u->getType() == UnitTypes::Terran_Supply_Depot ) {
	       Broodwar->sendText("Supply Depot! Awesome!");     
	  }
	  if( u->getType() == UnitTypes::Terran_Barracks ) {
	       Broodwar->sendText("Barracks! Awesome!");     
	  }
  } // closure: unit iterator
}