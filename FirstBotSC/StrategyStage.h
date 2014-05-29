#pragma once

#include <string>

#include "Oracle.h"
#include "BWAPINice.h"

namespace strategy {

using namespace BWAPINice;

class StrategyStage
{
public:
    virtual ~StrategyStage(void);

    virtual std::string GetName() const;

    virtual Advice GetAdvice() = 0;

    virtual bool isDone();


protected:
    StrategyStage(const std::string& name);


	Supply GetCurrent();
    Supply GetMaximum();
	Minerals GetMinerals();
    Gas GetGas();
    int GetUnitCount(UnitTypeEnum unitTypeID);

    bool _haveIssuedMyAdvice;

    void Done();

private:
    const std::string _name;
    bool _isDone;
};

}
