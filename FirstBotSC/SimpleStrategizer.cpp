#include "SimpleStrategizer.h"

#include <BWAPI.h>

using namespace strategy;

SimpleStrategizer::SimpleStrategizer()
    : _buildOrderStep(0) 
{
    ChangeStage(0);
}

void SimpleStrategizer::ChangeStage(Step stage) {
    _buildOrderStep = stage;
    BWAPI::Broodwar->printf("Build step: %d", _buildOrderStep);
}

Advice SimpleStrategizer::giveAdvice(Minerals minerals, Gas gas, Supply current, Supply maximum) {

	switch(_buildOrderStep) {
	case(0): {
        Advice advice = stage1.GetAdvice();
        if (stage1.isDone()) {
            ChangeStage(1);
        }
        return advice;
    }
	break;

	case(1): {
        Advice advice = stage2.GetAdvice();
        if (stage2.isDone()) {
            ChangeStage(2);
        }
        return advice;
    }
	break;

	case(2): {
        Advice advice = stage3.GetAdvice();
        if (stage3.isDone()) {
            ChangeStage(3);
        }
        return advice;
    }
	break;


	case(3): {
        Advice advice = stage4.GetAdvice();
        if (stage4.isDone()) {
            ChangeStage(4);
        }
        return advice;
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