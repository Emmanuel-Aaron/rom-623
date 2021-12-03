void setup() {
    Serial.begin(9600);

    int j = 0;
    while(1) {
        digitalWrite(5, HIGH);
        delay(1000);
        digitalWrite(5, LOW);
        delay(1000);
    }
}

void loop() {
}
