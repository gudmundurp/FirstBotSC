// FirstBotSC.h
#pragma once
#include <BWAPI.h>
#include "Advice.h"
#include "SCV/SCV.h"
#include <memory>

typedef std::shared_ptr<SCV> SharedMicroSMPtr;
typedef std::map<int, SharedMicroSMPtr> SharedMicroSMPtrMap;
extern SharedMicroSMPtrMap microStateMachines;

BWAPI::Unit findTrainer(BWAPI::UnitType type);

class FirstBot : public BWAPI::AIModule
{
	public:
    virtual void onStart();
    virtual void onFrame();

    virtual void updateMicroStateMachines();
    virtual void updateManagerStateMachines(Advice advice);
    /*
        virtual void onUnitComplete(BWAPI::Unit unit);
    virtual void onUnitCreate(BWAPI::Unit unit);

    virtual void onEnd(bool isWinner);
    virtual void onFrame();
    virtual void onSendText(std::string text);
    virtual void onReceiveText(BWAPI::Player player, std::string text);
    virtual void onPlayerLeft(BWAPI::Player player);
    virtual void onNukeDetect(BWAPI::Position target);
    virtual void onUnitDiscover(BWAPI::Unit unit);
    virtual void onUnitEvade(BWAPI::Unit unit);
    virtual void onUnitShow(BWAPI::Unit unit);
    virtual void onUnitHide(BWAPI::Unit unit);
    virtual void onUnitCreate(BWAPI::Unit unit);
    virtual void onUnitDestroy(BWAPI::Unit unit);
    virtual void onUnitMorph(BWAPI::Unit unit);
    virtual void onUnitRenegade(BWAPI::Unit unit);
    virtual void onSaveGame(std::string gameName);
    virtual void onUnitComplete(BWAPI::Unit unit);*/
};