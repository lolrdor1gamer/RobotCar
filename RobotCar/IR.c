// 
// 
// 

#include "IR.h"

int IRLevel(enum IRSide side)
{
	switch (side)
	{
	case IRLeft:
		return analogRead(IR_SENSOR_L);
		break;
	case IRCenter:
		return analogRead(IR_SENSOR_C);
		break;
	case IRRight:
		return analogRead(IR_SENSOR_R);
		break;
	default:
		return 0;
		break;
	}
	return 0;
}



