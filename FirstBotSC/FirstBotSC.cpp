// This is the main DLL file.

#include "FirstBotSC.h"
#include <SimpleStrategizer.h>
#include "SCV\SCV.h"
#include "SCVManagerSM.h"
#include "WorldImpl.h"
#include "FrameTime.h"
#include <map>
#include <ctime>
#include <random>
#include <set>

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

int nobuildloc = 0;


Unit findTrainer(UnitType type) {
  Unitset myUnits = Broodwar->self()->getUnits();
	for ( Unitset::iterator u = myUnits.begin(); u != myUnits.end(); ++u ) {
        if ( u->getType() != type ) {
            continue;
        }

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

		if (u->getType() == UnitTypes::Terran_SCV) {
			if ( u->isIdle() || u->getOrder() == Orders::MoveToMinerals ) {
				return *u;
			}
		} else {
			// Assuming for now that we look for a barracks.
			if ( u->getOrderTimer() < 2 ) {
				UnitType::set trainingQueue = u->getTrainingQueue();
				if ( trainingQueue.size() > 1 ) {
					// TODO consider canceling something in the queue
					continue;
				}

				return *u;
			}
		}
    }
	return 0;
}

void cleanUpDeadScouts(std::set<Unit> scoutingUnits) {
	std::vector<Unit> deadScouts;
	for (Unit u : scoutingUnits) {
		if (!u->exists()) {
			deadScouts.push_back(u);
		}
	}
	for (Unit u : deadScouts) {
		scoutingUnits.erase(u);
	}
}

void FirstBot::searchAndDestroy(bool defend)
{
	static std::random_device rd;
    static std::mt19937 gen(rd());
	static std::uniform_real_distribution<> ruin;

	static std::set<Unit> scoutingUnits;
	static std::set<Unit> attackingUnits;

	for (Unit u : BWAPI::Broodwar->enemy()->getUnits()) {
		if (Broodwar->getStartLocations().find(u->getTilePosition()) != Broodwar->getStartLocations().end()) {
			continue;
		}
		if (!u->getType().isBuilding()) {
			continue;
		}
		if (u->exists() && u->isVisible()) {
		   pointsOfInterest.insert(u);
		}
		else if(!u->exists() && Broodwar->isVisible(u->getTilePosition())) {
			pointsOfInterest.erase(u);
		}
		if (u->getPosition().x > Broodwar->mapWidth() || u->getPosition().y > Broodwar->mapHeight()) {
			pointsOfInterest.erase(u);
		}
	}

	TilePosition defencePosition = Broodwar->self()->getStartLocation();
	TilePosition attackPosition = *pointsOfInterest.begin();
	TilePosition scoutPosition = *(std::next(pointsOfInterest.begin(), ruin(gen) * pointsOfInterest.size()));
	for (PointOfInterest location : pointsOfInterest) {
		if (static_cast<TilePosition>(location) != defencePosition) {
			attackPosition = location;
		}
	}
	Broodwar->sendText("x %d; y %d", attackPosition.x, attackPosition.y);

	cleanUpDeadScouts(scoutingUnits);

	int countMarines = 0;
	for (auto unit : BWAPI::Broodwar->self()->getUnits()) {
		if (!unit->exists()) {
			continue;
		}
		if (unit->getType() == BWAPI::UnitTypes::Terran_Marine) {
			countMarines++;
		}
	}


	Unitset myUnits = Broodwar->self()->getUnits();
	for (Unitset::iterator u = myUnits.begin(); u != myUnits.end(); ++u) {
		if (u->getType() != Terran_Marine) {
			continue;
		}
		if (!u->exists()) {
			continue;
		}

		Order order = u->getOrder();
		if ((order == Orders::AttackMove || order == Orders::AttackTile || order == Orders::AttackUnit)
			&& (Broodwar->getFrameCount() - u->getLastCommandFrame() < LOGICAL_FRAME(1000))) {
			// Try not to spam too much.
			continue;
		}

		if (scoutingUnits.count(*u) && order == Orders::Move && (Broodwar->getFrameCount() - u->getLastCommandFrame() < LOGICAL_FRAME(1000))) {
			// Scouting takes time.
			continue;
		}

		if (u->isAttackFrame()) {
			// The unit is firing on the enemy.
			continue;
		}

		// Checking if there is a present danger.
		if (u->getOrderTarget() && u->getTarget() != u->getOrderTarget()) {
			// The Unit is engaging the enemy.
			continue;
		}
		
		if (!attackingUnits.count(*u) && (scoutingUnits.size() / (double)countMarines) <= 0.04) {
			// Use some of our available forces to scout.)

			std::vector<PointOfInterestSet::iterator> indexes;
			indexes.reserve(pointsOfInterest.size());
			for (PointOfInterestSet::iterator iter = pointsOfInterest.begin(); iter != pointsOfInterest.end(); ++iter) {
				if (static_cast<TilePosition>(*iter) != Broodwar->self()->getStartLocation()) {
					indexes.push_back(iter);
				}
			}

			for (size_t n = 0; n < indexes.size(); ++n) {
				int m = int(indexes.size() * ruin(gen));
				std::swap(indexes[n], indexes[m]);
			}

			bool hasIssuedCommand = false;
			for (auto iter : indexes) {
				u->move(Position(static_cast<TilePosition>(*iter)), hasIssuedCommand);
				hasIssuedCommand = true;
			}
			scoutingUnits.insert(*u);
		} else {

			if (defend) {
				u->attack(Position(defencePosition), false);
			} else {
				attackingUnits.insert(*u);
				u->attack(Position(attackPosition), false);
			}
			scoutingUnits.erase(*u);
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

	pointsOfInterest = Broodwar->getStartLocations();

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
        Unit trainer = findTrainer(UnitTypes::Terran_Barracks);
        if(!trainer) {
            Broodwar->sendText("Enginn builder/trainer fannst");
        } else {
            trainer->train(UnitTypes::Terran_Marine);
        }
    }
    if (advice == Attack) {
        //Broodwar->sendText("Attacking");
    }
	searchAndDestroy(advice != Attack);
}

bool operator<(const PositionOrUnit& lhs, const PositionOrUnit& rhs) {
	if (lhs.isPosition()) {
		return rhs.isUnit() || lhs.getPosition() < rhs.getPosition();
	}
	else {
		return rhs.isUnit() && lhs.getUnit() < rhs.getUnit();
	}
}
