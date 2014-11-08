// FirstBotSC.h
#pragma once
#include <BWAPI.h>
#include "Advice.h"
#include "SCV/SCV.h"
#include <memory>
#include <set>

using namespace BWAPI;

typedef std::shared_ptr<SCV> SharedMicroSMPtr;
typedef std::map<int, SharedMicroSMPtr> SharedMicroSMPtrMap;
extern SharedMicroSMPtrMap microStateMachines;

Unit findTrainer(BWAPI::UnitType type);

bool operator<(const PositionOrUnit& lhs, const PositionOrUnit& rhs);

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
	void searchAndDestroy(bool defend);

private:
	class PointOfInterest {
	public:
		PointOfInterest(const PositionOrUnit& u) :m_position(u) {};
		PointOfInterest(const TilePosition& p) :m_position(Position(p)) {};
		PointOfInterest(const Unit& u) :m_position(u) {};

		operator TilePosition() const {
			if (m_position.isPosition())
				return TilePosition(m_position.getPosition());
			else
				return m_position.getUnit()->getTilePosition();
		}

		operator Unit() const {
			if (m_position.isPosition())
				return NULL;
			else
				return m_position.getUnit();
		}

		bool isUnit() { return m_position.isUnit(); }
		bool isPosition() { return m_position.isPosition(); }
		Unit getUnit() { return m_position.getUnit(); }
		//bool isPosition() { return m_position.isPosition(); }

		bool operator<(const PointOfInterest& rhs) const {
			return m_position < rhs.m_position;
		}
	private:
		PositionOrUnit m_position;
	};

	class PointOfInterestSet {
	public:
		PointOfInterestSet()
		{ }

		PointOfInterestSet(const TilePosition::set& tilePositions) 
			: m_members(tilePositions.begin(), tilePositions.end())
		{ }

		typedef std::set<PointOfInterest>::iterator iterator;
		typedef std::set<PointOfInterest>::size_type size_type;
		iterator begin() {
			return m_members.begin();
		};
		iterator end(){
			return m_members.end();
		};

		size_type size() {
			return m_members.size();
		}

		std::pair<iterator, bool> insert(const PointOfInterest& point) {
			return m_members.insert(point);
		}

		bool erase(const PointOfInterest& point) {
			return m_members.erase(point);
		}

	private:
		std::set<PointOfInterest> m_members;
	};

	PointOfInterestSet pointsOfInterest;
	std::map<Unit, PointOfInterest> enemyBuildings;
};