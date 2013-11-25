// This is the main DLL file.

#include "FirstBotSC.h"

using namespace BWAPI;
using namespace UnitTypes::Enum;
using namespace Filter;

Unitset workerSet;
int mainWorker = 0;
int mainResourceDepot = 0;
int reservedMinerals = 0;
bool initialFrame = true;

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

  if(getAvailableMinerals() >= 150) {
    reservedMinerals += 150;
    Unit main = Broodwar->getUnit(mainWorker);
    TilePosition targetBuildLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, main->getTilePosition());
              if ( targetBuildLocation )
              {
                  main->build( UnitTypes::Terran_Barracks, targetBuildLocation );
              }
    
  }

  if(mainResourceDepot < 0) return;

  Unit u = Broodwar->getUnit(mainResourceDepot);

  if (u->exists() && u->getType().isResourceDepot() ) // A resource depot is a Command Center, Nexus, or Hatchery
    {
      // Order the depot to construct more workers! But only when it is idle.
      if ( u->isIdle() && getAvailableMinerals() >= 50 && !u->train(u->getType().getRace().getWorker()) )
      {
              
        // If that fails, draw the error at the location so that you can visibly see what went wrong!
        // However, drawing the error once will only appear for a single frame
        // so create an event that keeps it on the screen for some frames
        Error lastErr = Broodwar->getLastError();
        if(lastErr == Errors::Insufficient_Minerals || lastErr == Errors::Insufficient_Gas) return;

        // Retrieve the supply provider type in the case that we have run out of supplies
        UnitType supplyProviderType = u->getType().getRace().getSupplyProvider();
        static int lastChecked = 0;

        // If we are supply blocked and haven't tried constructing more recently
        if (  lastErr == Errors::Insufficient_Supply &&
              lastChecked + 400 < Broodwar->getFrameCount() &&
              Broodwar->self()->incompleteUnitCount(supplyProviderType) == 0 )
        {
          lastChecked = Broodwar->getFrameCount();

          // Retrieve a unit that is capable of constructing the supply needed

          //Unit supplyBuilder = Broodwar->getUnit(mainWorker);

          Unit supplyBuilder = u->getClosestUnit(  GetType == supplyProviderType.whatBuilds().first &&
                                                    (IsIdle || IsGatheringMinerals) &&
                                                    IsOwned);

          // If a unit was found
          if ( supplyBuilder )
          {
            if ( supplyProviderType.isBuilding() )
            {
              TilePosition targetBuildLocation = Broodwar->getBuildLocation(supplyProviderType, supplyBuilder->getTilePosition());
              if ( targetBuildLocation )
              {
                // Register an event that draws the target build location
                /*Broodwar->registerEvent([targetBuildLocation,supplyProviderType](Game*)
                                        {
                                          Broodwar->drawBoxMap( Position(targetBuildLocation),
                                                                Position(targetBuildLocation + supplyProviderType.tileSize()),
                                                                Colors::Blue);
                                        },
                                        nullptr,  // condition
                                        supplyProviderType.buildTime() + 100 );  // frames to run
                                        */
                // Order the builder to construct the supply structure
                supplyBuilder->build( supplyProviderType, targetBuildLocation );
              }
            }
            else
            {
              // Train the supply provider (Overlord) if the provider is not a structure
              supplyBuilder->train( supplyProviderType );
            }
          } // closure: supplyBuilder is valid
          else {
            //Broodwar -> sendText("WTF! mainWorker was %d", mainWorker);

          }
        } // closure: insufficient supply
      } // closure: failed to train idle unit

    }
}
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