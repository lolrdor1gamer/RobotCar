// UltraSonic.h

#ifndef _ULTRASONIC_h
#define _ULTRASONIC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#pragma region UltrasonicPreferences
#define L_TRIG_PIN 8
#define L_ECHO_PIN 7

#define C_TRIG_PIN 13
#define C_ECHO_PIN 12

#define R_TRIG_PIN 4
#define R_ECHO_PIN 3

enum USSSide
{
	USSLeft = 0,
	USSCenter,
	USSRight
};
#pragma endregion Ultrasonic

double SonarDist(enum USSSide side);


#endif
