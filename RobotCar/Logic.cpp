// 
// 
// 
#include "Logic.h"


void CheckWorkingState(struct LogicData* data)
{
	switch (data->state)
	{
	case Line:
		LineMode(data);
		break;
	case Slave:
		break;
	case Random:
		break;
	case Controlled:
		ControlledMode(data);
		break;
	default:
		break;
	}
}

void ControlledMode(struct LogicData* data)
{
	//WebUtil* util = WebUtil.Instance;
}
void LineMode(struct LogicData* data)
{
	SetSide(data, CheckSensors());
}

int CheckSensors()
{
	const int l = IRLevel(IRLeft);
	const int c = IRLevel(IRCenter);
	const int r = IRLevel(IRRight);

	return (l > c ? (c > r ? 2 : 1) : (l > r ? 2 : 0));
}

void SetSide(struct LogicData* data, int signal)
{
	switch (signal)
	{
	case 0:

		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
}