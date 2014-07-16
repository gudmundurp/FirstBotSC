// This is the main DLL file.

#include "FirstBotSC.h"
#include <SimpleStrategizer.h>
#include "SCV\SCV.h"
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

typedef std::shared_ptr<SCV> SharedSCVPointer;
typedef std::map<int, SharedSCVPointer> SharedSCVPointerMap;

SharedSCVPointerMap scvs;
WorldImpl world;

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

void build(BWAPI::UnitType type) {
    // TODO scv_bw->build can fail for example if scv is in the supply depot. Also maybe scv_bw->train can also. 
	using namespace BWAPI;
    using namespace Filter;

    auto unitType = type.whatBuilds().first;

    Unit scv_bw = findTrainer(unitType);

    if(!scv_bw) {
        Broodwar->sendText("Enginn builder/trainer fannst");
        return;
    }

    if(scv_bw->getType().isWorker()) {
        TilePosition targetBuildLocation = Broodwar->getBuildLocation(type, scv_bw->getTilePosition());
        if ( targetBuildLocation && targetBuildLocation != TilePositions::Invalid ) {
            auto scv = scvs[scv_bw->getID()];
            scv->build(type, targetBuildLocation);
            //scv_bw->build( type, targetBuildLocation );
        } else {
            Broodwar->sendText("Found no build location");
            ++nobuildloc;
        }
    } else {
        scv_bw->train(type);
    }
}

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

        // If the unit is a worker unit
        if ( u->getType().isWorker() ) {
            int id = u->getID();

            SharedSCVPointerMap::iterator iter = scvs.find(id);
            if (iter == scvs.end()) {
                scvs[id] = SharedSCVPointer(new SCV(id, &world));
            }
            scvs[id]->Update();
        } else if ( u->getType().isResourceDepot() ) {
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

    for (;;) {
        if (advice == BuildSD) {
            Broodwar->sendText("Building supply depot");
            ::build(UnitTypes::Terran_Supply_Depot);
        }
        if (advice == BuildBarracks) {
            Broodwar->sendText("Building barracks");
            ::build(UnitTypes::Terran_Barracks);
        }
        break;
    }

    if (advice == TrainMarine) {
        ::build(UnitTypes::Terran_Marine);
    }
    if (advice == Attack) {
        Broodwar->sendText("Attacking");
        searchAndDestroy();
    }
}
