#include"/home/inventor/rom-623/src/sensors/brushlessMotor/Servo.h"

Servo esc;

void pwmTest(){

	for(int i = 0; i < 2000; i+=10){
		
		esc.writeMicroseconds(i);
		delay(50);
	}
}

void arm(){

}

void setup(){

	esc.attach(9);
	pwmTest();
}

void loop(){

}
