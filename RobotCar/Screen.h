// Screen.h

#ifndef _SCREEN_h
#define _SCREEN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#pragma region ScreenPreferences
#define OLED_SCL A5
#define OLED_SDA A4
#pragma endregion ScreenPreferences


#endif
