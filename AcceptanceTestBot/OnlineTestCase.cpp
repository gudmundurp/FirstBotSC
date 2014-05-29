#include "OnlineTestCase.h"


namespace testcase {
    
    OnlineTestCase::OnlineTestCase(const std::string& name)
        : _name(name), _status(PENDING)
    {
    }
    

std::string testcase::OnlineTestCase::GetName(void)
{
    return _name;
}


TestResult testcase::OnlineTestCase::GetStatus(void)
{
    return _status;
}


void testcase::OnlineTestCase::Fail(void)
{
    if (_status != SUCCESS) {
        _status = FAILED;
    }
}

void OnlineTestCase::Succeed(void) {
    _status = SUCCESS;
}

};


