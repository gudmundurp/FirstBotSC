#include <Oracle.h>

#include "BuildFirstSupplyDepot.h"
#include "BuildFirstBarracks.h"
#include "BuildSecondBarracks.h"
#include "BuildSecondSupplyDepot.h"
#include "RushStrategy.h"

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
    BuildSecondBarracks stage2;
    BuildSecondSupplyDepot stage3;
    RushStrategy rush;
};

};