#pragma once

typedef enum { Nothing, Attack, BuildSD, BuildBarracks, TrainMarine } Advice;

typedef int Minerals;
typedef int Gas;
typedef int Supply;

class Oracle {
public:
	 virtual Advice giveAdvice(Minerals minerals, Gas gas, Supply current, Supply maximum)=0;
};