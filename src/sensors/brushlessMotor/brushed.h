//
//
//
//Lowest throttle 1200
//Max Throttle 2300
#include"/root/Development/rom-623/src/sensors/servo/Servo.h"

Servo esc;

void throttle(int value) {
if(value < 1300) {
    esc.writeMicroseconds(1300);
    delay(100);
} else if(value > 2300) {
    esc.writeMicroseconds(2300);
    delay(100);
} else {
    esc.writeMicroseconds(value);
    delay(100);
}
}

void range(int start_val, int end_val, int step) {

    if(start_val > end_val) {

        int i = start_val;
        while(i > end_val) {
            throttle(i);
            i -= step;
        }

    } else {
        int i = start_val;
        while(i < end_val) {
            throttle(i);
            i += step;
        }
    }
}

void pwmTest(){

    for(int i = 2000; i > 1000; i-=100){

        esc.writeMicroseconds(i);
        delay(700);
    }
}


void arm(){
    delay(700);
    esc.writeMicroseconds(2000);
    delay(700);
    esc.writeMicroseconds(700);
    delay(1500);
    esc.writeMicroseconds(2000);
    delay(700);
    esc.writeMicroseconds(700);
    delay(1500);

}
