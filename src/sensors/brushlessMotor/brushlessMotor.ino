//
//
//
//Lowest throttle 1300
//Max Throttle 2300
#include"/root/Development/rom-623/src/sensors/brushlessMotor/brushed.h"

void setup(){

    esc.attach(12);
    arm();
}

void loop(){
throttle(1200);
}
