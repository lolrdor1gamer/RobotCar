// Logic.h

#ifndef _LOGIC_h
#define _LOGIC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IR.h"
#include "Motors.h"


enum WorkingState
{
	Slave =0,
	Line,
	Random,
	Controlled
};

struct LogicData
{
	enum WorkingState state;
	int speed; //from 0 to 100 %
};



void CheckWorkingState(struct LogicData* data);

#pragma region LineMode
void LineMode(struct LogicData* data);

int CheckSensors();


void SetSide(struct LogicData* data, int signal);
#pragma endregion LineMode
#endif

