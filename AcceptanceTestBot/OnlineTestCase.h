#pragma once

#include <string>

namespace testcase {
    typedef enum { PENDING, FAILED, SUCCESS } TestResult;
    
    class OnlineTestCase
    {
    public:
        OnlineTestCase(const std::string& name);

    private:
        const std::string _name;
        TestResult _status;
    public:
        std::string GetName(void);
        TestResult GetStatus(void);
        void Fail(void);

        // TODO Remove this method.
        void Succeed(void);

        };
}