#ifndef _MOTORS_h
#define _MOTORS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#pragma once

#pragma region MotorsPreferences

#define L_MOTOR_FORWARD 3
#define L_MOTOR_BACKWARD 11

#define R_MOTOR_FORWARD 10
#define R_MOTOR_BACKWARD 9

typedef enum MotorsSide {
  Left = 0,
  Both,
  Right
} MotorsSide;
typedef struct Motor {
  int forward_pin;
  int backward_pin;

  int speed;
} Motor;
typedef struct MovingSystem {
  Motor* motor_left;
  Motor* motor_right;
} MovingSystem;
#pragma endregion MotorsPreferences


void MotorInit(Motor* mot, int forward_pin, int backward_pin);
void MovingSystemInit(MovingSystem* mot, Motor* mot1, Motor* mot2);
void InitMotorsSystem(MovingSystem* mot, Motor* mot1, Motor* mot2);


void SetSpeed(MovingSystem* mot, MotorsSide side, int percentage);
void Turning(MovingSystem* mot, MotorsSide side, int percentage);
void TurningOnMOving(MovingSystem* mot, MotorsSide side, int percentage);
void TurnOffMotor(MovingSystem* mot, MotorsSide side);


#endif