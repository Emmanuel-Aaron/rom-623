#include "./interupt.h"

int data = 5;

bool on = false;
void func1(void* data) {
digitalWrite(11, HIGH);
delay(1000);
digitalWrite(11, LOW);
}

void func2(void* data) {
digitalWrite(10, HIGH);
delay(100);
digitalWrite(10, LOW);
}

void func3(void* data) {
digitalWrite(9, HIGH);
delay(100);
digitalWrite(9, LOW);
}


void setup() {
    Serial.begin(9600);
    int i = 0;
    Interupt nothing;
    nothing.ready = false;
    while(i < 15) {
        interupt_que[i] = nothing;
        i += 1;
    }
        addJob2Que(func1, &data, 1);
        setIntTimer(1);
}

bool isRun = false;
void loop() {

}
