#include<SimpleStrategizer.h>

Advice SimpleStrategizer::giveAdvice(Minerals minerals, Gas gas, Supply current, Supply maximum) {

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
		    return BuildBarracks;
	    }
	}
	break;

	case(2):
	if(current>=13 && maximum==18) {
		if(minerals >=150) {
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
		return Nothing;
    };
	return Nothing;
};