// IR.h

#ifndef _IR_h
#define _IR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#pragma region IRPreferences



#define IR_SENSOR_L A2
#define IR_SENSOR_C A1
#define IR_SENSOR_R A0

typedef enum IRSide {
  IRLeft = 0,
  IRCenter,
  IRRight
} IRSide;


#pragma endregion IRPreferences
#pragma once


int IRLevel(IRSide side);



#endif