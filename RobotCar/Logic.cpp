//
//
//
#include "Logic.h"



void CheckWorkingState(LogicData* data) {
  switch (data->state) {
    case Line:
      LineMode(data);
      break;
    case Slave:
      break;
    case Random:
      RandomMode(data);
      break;
    case Controlled:
      ControlledMode(data);
      break;
    default:
      break;
  }
}
#pragma region ControlledMode
void ControlledMode(LogicData* data) {
  WebUtil* util = &WebUtil::GetInstance();
  data->speed = SetMotorsSpeed(util);
}

void RandomMode(LogicData* data) {
  if (millis() - timer > randomTimerDelay) {
    timer = millis();
    CheckUSSensors(data);
  }
}

void CheckUSSensors(LogicData* data) {
  Serial.println(SonarDist(USSLeft));
  if (SonarDist(USSLeft) < distanceFromObstacle) {
    data->speed = 100;
    SetSide(data, 0);
  }
  if (SonarDist(USSCenter) < distanceFromObstacle) {
    data->speed = -100;
    SetSide(data, 1);
  }
  if (SonarDist(USSRight) < distanceFromObstacle) {
    data->speed = 100;
    SetSide(data, 2);
  }
}


int SetMotorsSpeed(WebUtil* util) {
  util->SplitData(util->GetData());
  auto speed = util->GetSpeed();

  SetSpeed(&motSys, MotorsSide::Left, std::get<0>(speed));
  SetSpeed(&motSys, MotorsSide::Right, std::get<1>(speed));

  return (std::get<0>(speed) + std::get<1>(speed)) / 2;
}
#pragma endregion ControlledMode

void LineMode(LogicData* data) {
  SetSide(data, CheckIRSensors());
}

int CheckIRSensors() {
  const int l = IRLevel(IRLeft);
  const int c = IRLevel(IRCenter);
  const int r = IRLevel(IRRight);

  return (l < c ? (c < r ? 2 : 1) : (l < r ? 2 : 0));
}

void SetSide(LogicData* data, int signal) {
  switch (signal) {
    case 0:
      SetSpeed(&motSys, MotorsSide::Left, 20);
      SetSpeed(&motSys, MotorsSide::Right, -20);
      break;
    case 1:
      SetSpeed(&motSys, MotorsSide::Left, data->speed);
      SetSpeed(&motSys, MotorsSide::Right, data->speed);
      break;
    case 2:
      SetSpeed(&motSys, MotorsSide::Left, -20);
      SetSpeed(&motSys, MotorsSide::Right, 20);
      break;
    default:
      break;
  }
}