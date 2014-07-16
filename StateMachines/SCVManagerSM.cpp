#include "SCVManagerSM.h"
#include "BWAPI.h"
#include "SCV\SCV.h"
#include "WorldImpl.h"
#include "../FirstBotSC/FirstBotSC.h"

using namespace BWAPI;

void SCVManagerSM::update(Advice advice) {
    if (advice == BuildSD) {
        Broodwar->sendText("Building supply depot");
        build(UnitTypes::Terran_Supply_Depot);
    }
    if (advice == BuildBarracks) {
        Broodwar->sendText("Building barracks");
        build(UnitTypes::Terran_Barracks);
    }
}


Unit SCVManagerSM::findTrainer(UnitType type) {
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

void SCVManagerSM::build(BWAPI::UnitType type) {
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
            auto scv = microStateMachines[scv_bw->getID()];
            scv->build(type, targetBuildLocation);
        } else {
            Broodwar->sendText("Found no build location");
        }
    } else {
        Broodwar->sendText("Not a building?");
    }
}
