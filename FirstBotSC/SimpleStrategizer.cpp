#include<SimpleStrategizer.h>
#include <BWAPI.h>

SimpleStrategizer::SimpleStrategizer() {
	_buildOrderStep = 0;
}

Advice SimpleStrategizer::giveAdvice(Minerals minerals, Gas gas, Supply current, Supply maximum) {
	BWAPI::Broodwar->printf("Build step: %d",_buildOrderStep);
    if(current>5) {
		int x = 1+1;
	}

	switch(_buildOrderStep) {
	case(0):
	    if(current>=9 && maximum==10) {
	        if(minerals >=100) {
	            _buildOrderStep++;
	            return BuildSD;
	        }
	    }
	break;

	case(1):
	if(current>=11 && maximum==18) {
		if(minerals >=150) {
			_buildOrderStep++;
		    return BuildBarracks;
	    }
	}
	break;

	case(2):
	if(current>=13 && maximum==18) {
		if(minerals >=150) {
			_buildOrderStep++;
		    return BuildBarracks;
	    }
	}
	break;

	case(3):
	    if(current >=15 && maximum == 18) {
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