#include "SCVManagerSM.h"
#include "BWAPI.h"
#include "SCV/SCV.h"
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



void SCVManagerSM::build(BWAPI::UnitType type) {
    // TODO scv_bw->build can fail for example if scv is in the supply depot. Also maybe scv_bw->train can also. 
	using namespace BWAPI;
    using namespace Filter;

    auto unitType = type.whatBuilds().first;

    Unit scv_bw = findTrainer(unitType);

    if(!scv_bw) {
        Broodwar->sendText("Enginn SCV er tiltækur");
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
