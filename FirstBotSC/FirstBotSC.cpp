// This is the main DLL file.

#include "FirstBotSC.h"
#include "SCV\SCV.h"
#include "World.h"
#include <map>

using namespace BWAPI;
using namespace UnitTypes::Enum;
using namespace Filter;

Unitset workerSet;
int mainWorker = 0;
int mainResourceDepot = 0;
int reservedMinerals = 0;
bool initialFrame = true;

std::map<int, SCV*> scvs;
std::vector<SCV> _scvs;
World world;

int getAvailableMinerals() {
  int retInt = Broodwar->self()->minerals() - reservedMinerals;
  /*if(retInt < 0) {
    retInt += reservedMinerals;
    reservedMinerals = 0;
  }*/
  return retInt;
}

void FirstBot :: onStart() {
  Broodwar->sendText("Hello world!");

  Broodwar->enableFlag(Flag::UserInput);

  // Uncomment the following line and the bot will know about everything through the fog of war (cheat).
  Broodwar->enableFlag(Flag::CompleteMapInformation);

  // Set the command optimization level so that common commands can be grouped
  // and reduce the bot's APM (Actions Per Minute).
  Broodwar->setCommandOptimizationLevel(2);
}

void FirstBot :: onFrame() {
    // Called once every game frame

  // Display the game frame rate as text in the upper left area of the screen
  Broodwar->drawTextScreen(200, 0,  "FPS: %d", Broodwar->getFPS() );
  Broodwar->drawTextScreen(200, 20, "Average FPS: %f", Broodwar->getAverageFPS() );
  Broodwar->drawTextScreen(200, 40,  "Reserved: %d",  reservedMinerals);
  Broodwar->drawTextScreen(200, 60, "Elapsed time: %d", Broodwar->elapsedTime());

  // Return if the game is a replay or is paused
  if ( Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self() )
    return;

  // Prevent spamming by only running our onFrame once every number of latency frames.
  // Latency frames are the number of frames before commands are processed.
  if ( Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0 )
    return;

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
    if ( u->getType().isWorker() )
    {
      int id = u->getID();

      std::map<int,SCV*>::iterator iter = scvs.find(id);
      if (iter == scvs.end()) {
        _scvs.push_back( SCV(id, &world) );
        scvs[id] = &_scvs.back();
      }
      scvs[id]->Update();
    }
  } // closure: unit iterator
}
/*
  void FirstBot :: onUnitComplete(Unit unit)
  {
    if(unit->getType() == Terran_Barracks) Broodwar->sendText("Finally we got a Barracks");

    if( unit->getPlayer() != Broodwar->self() ) return;

    if(unit->getType().isWorker()) {
      workerSet.insert(unit);

      mainWorker = unit->getID();

      unit->gather(unit->getClosestUnit(Filter::IsMineralField));

      std::stringstream ss;

      ss << "We have " << workerSet.size() << " workers!";

      Broodwar->sendText(ss.str().c_str());
    } else if(unit->getType().isBuilding()) {
      if(unit->getType().isResourceDepot()){
          mainResourceDepot = unit->getID();
          unit->train(unit->getType().getRace().getWorker());
      }
      if (Broodwar->elapsedTime() >= 10) {
          Broodwar->sendText("When the fuck is this actually called?");
          reservedMinerals -= unit->getType().mineralPrice();
      }
    } else {
      switch(unit->getType()) {
    case Terran_Marine:
    case Zerg_Zergling:
    case Protoss_Zealot:
      Broodwar->sendText("Basic warrior created");
      return;
    default:
      break;
      }
    }
  }
  */