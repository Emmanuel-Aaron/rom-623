#include "./interupt.h"

char data[] = "JOB1";

void job1(void* data) {
delay(10);
    Serial.print("Hello I'm George\n");
    digitalWrite(11, LOW);
    delay(10);
    Serial.print((char*)data);
    delay(10);
    digitalWrite(11,HIGH);

    setJobTime(job1, &data, 2);
}

void setup() {
Serial.begin(9500);
    setJobTime(job1, &data, 2);
}

void loop() {
Serial.print("Im larry\n");
}
