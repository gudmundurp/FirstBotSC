#include <Oracle.h>

typedef int Step;

class SimpleStrategizer : Oracle {
public:
	SimpleStrategizer();
	 virtual Advice giveAdvice(Minerals minerals, Gas gas, Supply current, Supply maximum);
private :
	Step _buildOrderStep;

    void ChangeStage(Step stage);
};