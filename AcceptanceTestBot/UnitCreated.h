#pragma once

#include "onlineunittypetestcase.h"
#include "../FirstBotSC/BWAPINice.h"

namespace testcase {
namespace unittestcase {

using namespace BWAPINice;

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

