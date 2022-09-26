#ifndef _MOTORS_h
#define _MOTORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif



#pragma region MotorsPreferences


enum MotorsSide
{
	Left = 0,
	Both,
	Right
};
struct Motor
{
	int forward_pin;
	int backward_pin;

	int speed;
};
struct MovingSystem
{
	struct Motor* motor_left;
	struct Motor* motor_right;
};
#pragma endregion MotorsPreferences


void MotorInit(struct Motor* mot, int forward_pin, int backward_pin);
void MovingSystemInit(struct MovingSystem* mot, struct Motor* mot1, struct Motor* mot2);

void SetSpeed(struct MovingSystem* mot, enum MotorsSide side, int percentage);
void Turning(struct MovingSystem* mot, enum MotorsSide side, int percentage);
void TurningOnMOving(struct MovingSystem* mot, enum MotorsSide side, int percentage);
void TurnOffMotor(struct MovingSystem* mot, enum MotorsSide side);


#endif
