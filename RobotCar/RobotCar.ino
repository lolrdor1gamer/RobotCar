#include "WebApp.h"
//#include "LED.h"
#include "Logic.h"
extern "C" {
#include "Screen.h"
#include "Encoder.h"
#include "IR.h"
#include "Motors.h"
#include "UltraSonic.h"
}

//struct LED Leds;


//WebUtil* WebUtil::Instance = nullptr;


int incomingByte = 0;
int incomingByteLast = 0;
static WiFiServer server(80);

MovingSystem motSys;
Motor motLeft;
Motor motRight;

LogicData ld;

void setup() {
  ld.state = 2;
  ld.speed = 100;

  InitMotorsSystem(&motSys, &motLeft, &motRight);


  Serial.begin(115200);
  Serial.println();

  WebUtil::GetInstance().WebUtilSetup(&server);

  Serial.begin(115200);
  analogWriteRange(65535 / 2);
}

void loop() {
  /*while (Serial.available() == 0) {}
    String input = Serial.readString();
    input.trim();
    Turning(&movingSystem, Left, input.toInt());
    
    */
  WebUtil::GetInstance().WebUtilUpdate(&server);
  CheckWorkingState(&ld);
}