// Encoder.h

#ifndef _ENCODER_h
#define _ENCODER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#pragma region EncoderPreferences
#define ENCODER_L A3
#define ENCODER_R A6
#define ENCODER_BUTTON A7
#pragma endregion EncoderPreferences
#pragma once
#endif