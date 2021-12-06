#include "/root/Development/rom-623/src/sensors/ultrasonic/ultra.c"

int first_run_clearance = 0;

void groundClearance() {
    digitalWrite(9, HIGH);
    delay(100);
    digitalWrite(9, LOW);
    if(first_run_clearance == 0) {
        base_clearance = 0;
        pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
        pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
        base_clearance = requestClrearence(10);
        Serial.println(base_clearance);

        first_run_clearance = 1;
    }

    clearance = requestClrearence(10);
    Serial.print("Clearance: ");
    Serial.println(clearance);
}
