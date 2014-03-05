// This is the AcceptanceTestBot DLL file.

#include "AcceptanceTestBot.h"
#include <algorithm>

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

  Broodwar->setLocalSpeed(0);
  Broodwar->setFrameSkip(16);

  Broodwar->enableFlag(Flag::UserInput);

  // Uncomment the following line and the bot will know about everything through the fog of war (cheat).
  Broodwar->enableFlag(Flag::CompleteMapInformation);

  // Set the command optimization level so that common commands can be grouped
  // and reduce the bot's APM (Actions Per Minute).
  Broodwar->setCommandOptimizationLevel(2);
}

typedef enum { PENDING, FAILED, SUCCESS } TestResult;

std::vector<TestResult> testArray(2, PENDING);

#define SUPPLY_DEPOT_TEST 0
#define BARRACKS_TEST 1

void printTestResult(TestResult res, int yPos) {
	
		const char* testResult;
	switch (res) {
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

	Broodwar->drawTextScreen(300, yPos,  "Test result: %s", testResult );
}

void printTestResults() {
	for (auto iter = testArray.begin(); iter != testArray.end(); ++iter) {
		printTestResult(*iter, 20 * (iter - testArray.begin()));
	}
	
}

void AcceptanceTestBot :: onFrame() {
  printTestResults();

  if ( Broodwar->isPaused() || !Broodwar->self() )
    return;

  if ( Broodwar->getFrameCount() >= (int)((30*1000)/42.0 + 0.5) ) {
	  std::for_each(testArray.begin(), testArray.end(),
		  [](TestResult& res) -> void {if (res == PENDING) res = FAILED;});
  }

  Unitset myUnits = Broodwar->getAllUnits();
  for ( auto u = myUnits.begin(); u != myUnits.end(); ++u )
  {
	  if( u->getType() == UnitTypes::Terran_Supply_Depot ) {
	       Broodwar->sendText("%s", "Supply Depot! Awesome!");     
		   testArray[SUPPLY_DEPOT_TEST] = SUCCESS;
	  }
	  if( u->getType() == UnitTypes::Terran_Barracks ) {
	       Broodwar->sendText("%s", "Barracks! Awesome!");     
		   testArray[BARRACKS_TEST] = SUCCESS;
	  }
  }
}