// This is the main DLL file.

#include "FirstBotSC.h"

using namespace BWAPI;

Unitset workerSet;
bool initialFrame = true;

void FirstBot :: onStart() {
  Broodwar->sendText("Hello world!");
}

void FirstBot :: onFrame() {
    // Called once every game frame

  // Display the game frame rate as text in the upper left area of the screen
  Broodwar->drawTextScreen(200, 0,  "FPS: %d", Broodwar->getFPS() );
  Broodwar->drawTextScreen(200, 20, "Average FPS: %f", Broodwar->getAverageFPS() );

  // Return if the game is a replay or is paused
  if ( Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self() )
    return;

  // Prevent spamming by only running our onFrame once every number of latency frames.
  // Latency frames are the number of frames before commands are processed.
  if ( Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0 )
    return;

  if(initialFrame) {

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

    if ( u->getType().isWorker() )
      workerSet.insert(u);
  }
  initialFrame = false;

  std::stringstream ss;

  ss << "We have " << workerSet.size() << " workers!";

  Broodwar->sendText(ss.str().c_str());

  workerSet.gather( workerSet.getClosestUnit( Filter::IsMineralField ) );
  }
}