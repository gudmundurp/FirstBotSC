#include <Oracle.h>

#include "BuildFirstSupplyDepot.h"
#include "BuildFirstBarracks.h"
#include "BuildSecondBarracks.h"
#include "BuildSecondSupplyDepot.h"

namespace strategy {

class SimpleStrategizer : Oracle {
public:
    typedef int Step;

	SimpleStrategizer();
	 virtual Advice giveAdvice(Minerals minerals, Gas gas, Supply current, Supply maximum);
private :
	Step _buildOrderStep;

    void ChangeStage(Step stage);

    BuildFirstSupplyDepot stage1;
    BuildFirstBarracks stage2;
    BuildSecondBarracks stage3;
    BuildSecondSupplyDepot stage4;
};

};