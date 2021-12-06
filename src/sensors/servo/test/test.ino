#include "/root/Development/rom-623/src/sensors/servo/servo.c"

void setup() {
    aileronL.attach(2);
    aileronR.attach(4); 
    elevator.attach(6); 
    wingletZero();

}

void loop() {
    adjustPitch(-30);
    delay(1000);
}
