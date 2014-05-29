#pragma once

#include "OnlineTestCase.h"
#include "BWAPI.h"

namespace testcase {
    
    class OnlineUnitTypeTestCase :
        public OnlineTestCase
    {
    public:
        OnlineUnitTypeTestCase(const std::string& name);

        virtual testcase::TestResult operator()(BWAPI::Unit unit) = 0;
    };
};