#include "./interupt.h"

int data = 5;

bool on = false;
void func1() {
digitalWrite(11, HIGH);
delay(1500);
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
instr = func1;
setIntTimer(2000);
}

void loop() {
}
