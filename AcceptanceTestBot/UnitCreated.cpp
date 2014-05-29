#include "UnitCreated.h"

namespace testcase {
namespace unittestcase {

UnitCreated::UnitCreated(UnitTypeEnum unit)
    : OnlineUnitTypeTestCase(BWAPI::UnitType(unit).getName()),
      _unitTypeID(unit)
{
}


UnitCreated::~UnitCreated(void)
{
}

TestResult UnitCreated::operator()(BWAPI::Unit unit)
{
    if (GetStatus() == PENDING && unit->getType().getID() == _unitTypeID) {
        Succeed();
    }

    return GetStatus();
}


}
}