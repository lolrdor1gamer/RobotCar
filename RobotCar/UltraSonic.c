// 
// 
// 

#include "UltraSonic.h"

double SonarDist(enum USSSide side)
{
	switch (side)
	{
	case USSLeft:
		digitalWrite(L_TRIG_PIN, LOW);
		delayMicroseconds(2);

		digitalWrite(L_TRIG_PIN, HIGH);
		delayMicroseconds(10);
		digitalWrite(L_TRIG_PIN, LOW);

		return pulseIn(L_ECHO_PIN, HIGH, 1000000UL) * 0.034 / 2;
		break;
	case USSCenter:
		digitalWrite(C_TRIG_PIN, LOW);
		delayMicroseconds(2);

		digitalWrite(C_TRIG_PIN, HIGH);
		delayMicroseconds(10);
		digitalWrite(C_TRIG_PIN, LOW);

		return pulseIn(C_ECHO_PIN, HIGH, 1000000UL) * 0.034 / 2;
		break;
	case USSRight:
		digitalWrite(R_TRIG_PIN, LOW);
		delayMicroseconds(2);

		digitalWrite(R_TRIG_PIN, HIGH);
		delayMicroseconds(10);
		digitalWrite(R_TRIG_PIN, LOW);

		return pulseIn(R_ECHO_PIN, HIGH, 1000000UL) * 0.034 / 2;
		break;
	default:
		break;
	}
	return 0;
}
