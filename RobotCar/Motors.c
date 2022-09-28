// 
// 
// 

#include "Motors.h"


long mapp(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void MotorInit(struct Motor* mot, int forward_pin, int backward_pin)
{
	mot->forward_pin = forward_pin;
	mot->backward_pin = backward_pin;

	mot->speed = 0;

}
void MovingSystemInit(struct MovingSystem* mot, struct Motor* mot1, struct Motor* mot2)
{
	mot->motor_left = mot1;
	mot->motor_right = mot2;
}


void SetSpeed(struct MovingSystem* mot, enum MotorsSide side, int percentage)
{
	TurnOffMotor(mot, side);
	switch (side)
	{
	case Left:
		analogWrite(percentage >= 0 ? mot->motor_left->forward_pin : mot->motor_left->backward_pin, percentage < 0 ? mapp(percentage, -100, 0, 255, 0) : mapp(percentage, 0, 100, 0, 255));
		break;
	case Both:
		analogWrite(percentage >= 0 ? mot->motor_left->forward_pin : mot->motor_left->backward_pin, percentage < 0 ? mapp(percentage, -100, 0, 255, 0) : mapp(percentage, 0, 100, 0, 255));
		analogWrite(percentage >= 0 ? mot->motor_right->forward_pin : mot->motor_right->backward_pin, percentage < 0 ? mapp(percentage, -100, 0, 255, 0): mapp(percentage, 0, 100, 0, 255));
		break;
	case Right:
		analogWrite(percentage >= 0 ? mot->motor_right->forward_pin : mot->motor_right->backward_pin, percentage < 0 ? mapp(percentage, -100, 0, 255, 0) : mapp(percentage, 0, 100, 0, 255));
	default:
		break;
	}
}
void Turning(struct MovingSystem* mot, enum MotorsSide side, int percentage)
{
	TurnOffMotor(mot, Both);
	switch (side)
	{
	case Left:
		analogWrite(mot->motor_left->backward_pin, mapp(percentage, 0, 100, 0, 255));
		analogWrite(mot->motor_right->forward_pin, mapp(percentage, 0, 100, 0, 255));
		break;
	case Right:
		analogWrite(mot->motor_left->forward_pin, mapp(percentage, 0, 100, 0, 255));
		analogWrite(mot->motor_right->backward_pin, mapp(percentage, 0, 100, 0, 255));
		break;
	default:
		break;
	}
}
void TurnOffMotor(struct MovingSystem* mot, enum MotorsSide side)
{
	switch (side)
	{
	case Left:
		analogWrite(mot->motor_left->backward_pin, 0);
		analogWrite(mot->motor_left->forward_pin, 0);
		break;
	case Both:
		analogWrite(mot->motor_left->backward_pin, 0);
		analogWrite(mot->motor_left->forward_pin, 0);

		analogWrite(mot->motor_right->backward_pin, 0);
		analogWrite(mot->motor_right->forward_pin, 0);
		break;
	case Right:
		analogWrite(mot->motor_right->backward_pin, 0);
		analogWrite(mot->motor_right->forward_pin, 0);
		break;
	default:
		break;
	}
}
void TurningOnMOving(struct MovingSystem* mot, enum MotorsSide side, int percentage)
{
	TurnOffMotor(mot, side);
	switch (side)
	{
	case Left:
		analogWrite(mot->motor_left->forward_pin, mapp(percentage, 0, 100, 255, 0));
		break;
	case Right:
		analogWrite(mot->motor_right->forward_pin, mapp(percentage, 0, 100, 255, 0));
		break;
	default:
		break;
	}
}