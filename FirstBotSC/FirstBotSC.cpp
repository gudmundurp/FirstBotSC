// This is the main DLL file.

#include "FirstBotSC.h"
#include <SimpleStrategizer.h>
#include "SCV\SCV.h"
#include "SCVManagerSM.h"
#include "WorldImpl.h"
#include <map>
#include <ctime>

using namespace BWAPI;
using namespace UnitTypes::Enum;
using namespace Filter;

strategy::SimpleStrategizer *oracle;
Unitset workerSet;
int mainWorker = 0;
int mainResourceDepot = 0;
int reservedMinerals = 0;
bool initialFrame = true;
SharedMicroSMPtrMap microStateMachines;

typedef std::shared_ptr<ManagerSM> SharedManagerSMPointer;
typedef std::map<int, SharedManagerSMPointer> SharedManagerSMPointerMap;

SharedManagerSMPointerMap managers;

Unit findTrainer(UnitType type) {
  Unitset myUnits = Broodwar->self()->getUnits();
	for ( Unitset::iterator u = myUnits.begin(); u != myUnits.end(); ++u ) {
        // Ignore the unit if it no longer exists
        // Make sure to include this block when handling any Unit pointer!
        if ( !u->exists() )
            continue;

        // Ignore the unit if it has one of the following status ailments
        if ( u->isLockedDown() || u->isMaelstrommed() || u->isStasised() )
            continue;

        // Ignore the unit if it is in one of the following states
        if ( u->isLoaded() || !u->isPowered() || u->isStuck() )
            continue;

        // Ignore the unit if it is incomplete or busy constructing
        if ( !u->isCompleted() || u->isConstructing() || u->isTraining() )
            continue;

        if ( u->getType() == type ) {
            return *u;
        }
    }
	return 0;
}



int nobuildloc = 0;

void searchAndDestroy() {
    auto locations = Broodwar->getStartLocations();

  Unitset myUnits = Broodwar->self()->getUnits();
	for ( Unitset::iterator u = myUnits.begin(); u != myUnits.end(); ++u ) {
        if(u->getType() == Terran_Marine && !u->isAttacking()) {
            for(auto location = locations.begin(); location != locations.end(); ++location) {
                u->attack(Position(*location), true);
            }
        }
    }
}

int getAvailableMinerals() {
  int retInt = Broodwar->self()->minerals() - reservedMinerals;
  /*if(retInt < 0) {
    retInt += reservedMinerals;
    reservedMinerals = 0;
  }*/
  return retInt;
}

int speed = 0;
void FirstBot :: onStart() {
    Broodwar->sendText("Hello world!");
    
    Broodwar->setLocalSpeed(speed);
    //Broodwar->setFrameSkip(16);
    Broodwar->setGUI(true);
  

    Broodwar->enableFlag(Flag::UserInput);

    // Uncomment the following line and the bot will know about everything through the fog of war (cheat).
    Broodwar->enableFlag(Flag::CompleteMapInformation);

    // Set the command optimization level so that common commands can be grouped
    // and reduce the bot's APM (Actions Per Minute).
    Broodwar->setCommandOptimizationLevel(2);

    oracle = new strategy::SimpleStrategizer();

    managers[0] = std::make_shared<SCVManagerSM>();
}

void slowOrSpeedForKeyboardState(bool increasing, bool decreasing) {
    if(!increasing && !decreasing) return;
    if(increasing && decreasing) return;

    int factor = (increasing ? 1 : -1);
    speed += 4*factor;
    if(speed < 0) speed = 0;
    Broodwar->setLocalSpeed(speed);
}

void FirstBot :: onFrame() {
    // Called once every game frame

    Broodwar->drawTextScreen(0, 0,  "No build location: %d", nobuildloc );
    // Display the game frame rate as text in the upper left area of the screen
    Broodwar->drawTextScreen(200, 0,  "FPS: %d", Broodwar->getFPS() );
    Broodwar->drawTextScreen(200, 20, "Average FPS: %f", Broodwar->getAverageFPS() );
    Broodwar->drawTextScreen(200, 40,  "Reserved: %d",  reservedMinerals);
    Broodwar->drawTextScreen(200, 60, "Elapsed time: %d", Broodwar->elapsedTime());
    BWAPI::Broodwar->drawTextScreen(200, 80, "Minerals: %d Gas: %d Supply: %d/%d",
        Broodwar->self()->minerals(),
        Broodwar->self()->gas(),
        Broodwar->self()->supplyUsed()/2,
        Broodwar->self()->supplyTotal()/2);
    Broodwar->drawTextScreen(200, 100, "Game speed: %d", speed);

    auto mousePosition = Broodwar->getMousePosition();
    auto mouseState = Broodwar->getMouseState(MouseButton::M_LEFT);
    auto increasing = Broodwar->getKeyState(K_ADD) || Broodwar->getKeyState(K_OEM_PLUS);
    auto decreasing = Broodwar->getKeyState(K_SUBTRACT) || Broodwar->getKeyState(K_OEM_MINUS);
    Broodwar->drawTextScreen(400,20, "Mouse x: %d Mouse y: %d", mousePosition.x, mousePosition.y);
    Broodwar->drawTextScreen(400,40, "Left mouse pressed %s", (mouseState? "true" : "false"));


    //slowOrSpeedForMouseState(mousePosition,mouseState);
    slowOrSpeedForKeyboardState(increasing,decreasing);

    std::time_t t = std::time(nullptr);
    char buf[100];
    std::size_t len = std::strftime(buf, (sizeof buf) - 1, "%c %Z", std::gmtime(&t));
    buf[len] = 0;
    //Broodwar->drawTextScreen(200, 80, "Hello world: %s", buf);

    // Return if the game is a replay or is paused
    if ( Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self() )
        return;

    // Prevent spamming by only running our onFrame once every number of latency frames.
    // Latency frames are the number of frames before commands are processed.
    if ( Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0 )
        return;

    Advice advice = oracle->giveAdvice(
        Broodwar->self()->minerals(),
        Broodwar->self()->gas(),
        Broodwar->self()->supplyUsed(),
        Broodwar->self()->supplyTotal());

    updateManagerStateMachines(advice);
    updateMicroStateMachines();
}


void FirstBot::updateMicroStateMachines() {
    // Iterate through all the units that we own
    Unitset myUnits = Broodwar->self()->getUnits();
    for ( Unitset::iterator u = myUnits.begin(); u != myUnits.end(); ++u )
    {
        int id = u->getID();
        if (!microStateMachines.count(id)) {
            microStateMachines[id] = std::make_shared<SCV>(id, &world);
        }
    }

    for (auto iter = microStateMachines.begin(); iter != microStateMachines.end(); ++iter) {
        auto u = Broodwar->getUnit(iter->first);
        auto sm = iter->second;
        // Ignore the unit if it no longer exists
        // Make sure to include this block when handling any Unit pointer!
        if ( !u->exists() )
            continue;

        // Ignore the unit if it has one of the following status ailments
        if ( u->isLockedDown() || u->isMaelstrommed() || u->isStasised() )
            continue;

        // Ignore the unit if it is in one of the following states
        if ( u->isLoaded() || !u->isPowered() || u->isStuck() )
            continue;

        // Ignore the unit if it is incomplete or busy constructing
        if ( !u->isCompleted() || u->isConstructing() )
            continue;

        if ( u->getType().isWorker() ) {
            int id = u->getID();
            sm->Update();
        }
        if ( u->getType().isResourceDepot() ) {
            // A resource depot is a Command Center, Nexus, or Hatchery
            // Order the depot to construct more workers! But only when it is idle.
            if ( u->isIdle() )
            {
                u->train(u->getType().getRace().getWorker());
            }
        }
    } 
}

void FirstBot::updateManagerStateMachines(Advice advice) {

    for (auto managerIter = managers.begin(); managerIter != managers.end(); ++managerIter) {
        managerIter->second->update(advice);
    }

    if (advice == TrainMarine) {
        Unit scv_bw = findTrainer(UnitTypes::Terran_Marine);
        if(!scv_bw) {
            Broodwar->sendText("Enginn builder/trainer fannst");
        } else {
            scv_bw->train(UnitTypes::Terran_Marine);
        }
    }
    if (advice == Attack) {
        Broodwar->sendText("Attacking");
        searchAndDestroy();
    }
}
