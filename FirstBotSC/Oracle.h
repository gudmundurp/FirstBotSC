#pragma once

#include "Advice.h"

typedef int Minerals;
typedef int Gas;
typedef int Supply;

class Oracle {
public:
	 virtual Advice giveAdvice(Minerals minerals, Gas gas, Supply current, Supply maximum)=0;
};