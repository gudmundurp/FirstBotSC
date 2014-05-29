#pragma once

#include "onlineunittypetestcase.h"
#include "BWAPI.h"

namespace testcase {
namespace unittestcase {

typedef BWAPI::UnitTypes::Enum::Enum UnitTypeEnum;

class UnitCreated : public OnlineUnitTypeTestCase
{
public:
    UnitCreated(UnitTypeEnum unit);
    virtual ~UnitCreated(void);

    TestResult operator()(BWAPI::Unit unit);

private:
    const UnitTypeEnum _unitTypeID;
};

}
}

