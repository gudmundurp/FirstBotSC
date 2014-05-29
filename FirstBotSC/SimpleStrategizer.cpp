#include "SimpleStrategizer.h"
#include "BuildFirstSupplyDepot.h"
#include <BWAPI.h>

using namespace strategy;

SimpleStrategizer::SimpleStrategizer() {
	_buildOrderStep = 0;
}

Advice SimpleStrategizer::giveAdvice(Minerals minerals, Gas gas, Supply current, Supply maximum) {
	BWAPI::Broodwar->printf("Build step: %d",_buildOrderStep);

	switch(_buildOrderStep) {
	case(0): {
        BuildFirstSupplyDepot stage1;
        Advice advice = stage1.GetAdvice();
        if (stage1.isDone()) {
            ++_buildOrderStep;
        }
        return advice;
    }
	break;

	case(1):
	if(current>=22 && maximum==36) {
		if(minerals >=150) {
			_buildOrderStep++;
		    return BuildBarracks;
	    }
	}
	break;

	case(2):
	if(current>=26 && maximum==36) {
		if(minerals >=150) {
			_buildOrderStep++;
		    return BuildBarracks;
	    }
	}
	break;

	case(3):
	    if(current >= 30 && maximum == 36) {
	        if(minerals >=100) {
	            _buildOrderStep++;
	            return BuildSD;
	        }
	    }
	break;

	default:
		if ((minerals >= 50) && (current < maximum)) {
		    return TrainMarine;
	    } else {
		    return Nothing;
        }
    };
	return Nothing;
};