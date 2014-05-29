// This is the AcceptanceTestBot DLL file.

#include "AcceptanceTestBot.h"
#include <algorithm>
#include <memory>
#include "OnlineUnitTypeTestCase.h"
#include "UnitCreated.h"

using namespace BWAPI;
using namespace UnitTypes::Enum;
using namespace Filter;
using namespace testcase;

Unitset workerSet;
int AcceptanceTestBotWorker = 0;
int AcceptanceTestBotResourceDepot = 0;
int reservedMinerals = 0;
bool initialFrame = true;

std::vector<std::shared_ptr<OnlineUnitTypeTestCase>> testArray;

void AcceptanceTestBot :: onStart() {
    
    testArray.push_back(std::make_shared<unittestcase::UnitCreated>(Terran_Supply_Depot));
    testArray.push_back(std::make_shared<unittestcase::UnitCreated>(Terran_Marine));
    testArray.push_back(std::make_shared<unittestcase::UnitCreated>(Terran_Barracks));

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



#define SUPPLY_DEPOT_TEST 0
#define BARRACKS_TEST 1


void printTestResult(OnlineTestCase testcase, int yPos) {
    std::string resultMessage = testcase.GetName() + ": ";
    switch (testcase.GetStatus()) {
	case SUCCESS:
		resultMessage += "Success";
		break;
	case FAILED:
		resultMessage += "Failed";
		break;
	case PENDING:
	default:
		resultMessage += "In Progress";
		break;
	}

    Broodwar->drawTextScreen(300, yPos,  resultMessage.c_str());
}

void printTestResults() {
	for (auto iter = testArray.begin(); iter != testArray.end(); ++iter) {
		printTestResult(**iter, 20 * (iter - testArray.begin()));
	}
	
}

void AcceptanceTestBot :: onFrame() {
    printTestResults();

    if ( Broodwar->isPaused() || !Broodwar->self() )
        return;

    Unitset myUnits = Broodwar->getAllUnits();
    for ( auto u = myUnits.begin(); u != myUnits.end(); ++u ) {
        for (auto testCase = testArray.begin(); testCase != testArray.end(); ++testCase) {
            (**testCase)(*u);
        }
    }
}
