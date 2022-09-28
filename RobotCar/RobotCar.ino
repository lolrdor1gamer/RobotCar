#include "WebApp.h"
//#include "LED.h"
extern "C"
{
#include "Logic.h"
#include "Screen.h"
#include "Encoder.h"
#include "IR.h"
#include "Motors.h"
#include "UltraSonic.h"
}




//struct LED Leds;
struct MovingSystem movingSystem;
struct Motor mot1;
struct Motor mot2;


int incomingByte = 0;
int incomingByteLast = 0;
WebUtilll wu();
void setup() {
	  
      MotorInit(&mot1, L_MOTOR_FORWARD, L_MOTOR_BACKWARD);
      MotorInit(&mot2, R_MOTOR_FORWARD, R_MOTOR_BACKWARD);
      MovingSystemInit(&movingSystem, &mot1,  &mot2);

      Serial.begin(9600);
}

void loop() {
    while (Serial.available() == 0) {}
    String input = Serial.readString();
    input.trim();
    Turning(&movingSystem, Left, input.toInt());
    Serial.println(input.toInt());

    
}
