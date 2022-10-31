// Logic.h

#ifndef _LOGIC_h
#define _LOGIC_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#pragma once
#include "WebApp.h"

extern "C" {
#include "IR.h"
#include "UltraSonic.h"
#include "Motors.h"
}




typedef enum WorkingState {
  Slave = 0,
  Line,
  Random,
  Controlled
} WorkingState;

typedef struct LogicData {
  WorkingState state;
  int speed;  //from 0 to 100 %

} LogicData;



void CheckWorkingState(LogicData* data);


#pragma region LineMode
void LineMode(LogicData* data);

int CheckIRSensors();


void SetSide(LogicData* data, int signal);
#pragma endregion LineMode

#pragma region ControlledMode
void ControlledMode(LogicData* data);
#pragma endregion ControlledMode

#pragma region RandomMode

int timer = 0;
const int randomTimerDelay = 1000;  // in millis


int distanceFromObstacle = 15;  //distance in cm

void RandomMode(LogicData* data);

void CheckUSSensors(LogicData* data);

#pragma endregion RandomMode

#pragma region Motors

extern MovingSystem motSys;

int SetMotorsSpeed(WebUtil* util);
#pragma endregion Motors

#endif