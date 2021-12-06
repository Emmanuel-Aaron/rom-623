#include "/root/Development/rom-623/src/sensors/servo/servo.c"
Servo ESC;



void motorStart(){

ESC.attach(12);
    ESC.write(180);
    delay(500);
    ESC.write(0); 
    delay(500);
}

void motorUp(){

    for (int velocity = 0; velocity < 180; velocity += 10){
        
        ESC.write(velocity);
        delay(1500);
    }
}

void motorDown(){

    for (int velocity = 180; velocity > 0; velocity -= 10){
        
        ESC.write(velocity);
        delay(1500);
    }
}

void stop(){
    ESC.write(NULL);

}

