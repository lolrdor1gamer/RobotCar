// LED.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#pragma once
//#include "FastLED.h"

//#pragma region LEDPreferences
#define LED_COUNT 5

#define LEFT_LED 5
#define RIGHT_LED 6
enum LEDSide {
  LEDLeft = 0,
  LEDRight,
  LEDBoth
};
/*
class  Blinking
{
public:
	boolean IsNeededToBlink;
	enum LEDSide Side;
	struct CRGB Color;
	int LEDCounter;
	int LEDAmount;
	int LEDStart;
	Blinking(LEDSide side, CRGB color, int ledAmount, int ledStart) : Side(side), IsNeededToBlink(true), Color(color), LEDAmount(ledAmount), LEDCounter(0), LEDStart(ledStart)
	{

	}
};
//#pragma endregion LEDPreferences


class LED
{
public:
	LED()
	{
		SetupLEDs();
	}
	~LED()
	{

	}

	struct CRGB l_leds[LED_COUNT];
	struct CRGB r_leds[LED_COUNT];
	struct CLEDController* controllers[2];

	void OneColorStripe(LEDSide side, byte cr, byte cg, byte cb);
	void OneColorStripe(LEDSide side, CRGB color);
	void SetupLEDs();

	void Blink(Blinking* blinking);
private:

};*/

#endif