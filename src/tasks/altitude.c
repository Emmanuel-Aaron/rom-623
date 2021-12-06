#include "/root/Development/rom-623/src/sensors/altitude/altitude.h"
int first_run_alti = 0;

void altitude() {
    digitalWrite(10, HIGH);
    delay(100);
    digitalWrite(10, LOW);
    if(first_run_alti == 0) {
        pressure.begin();
        setBasePressure(200);
        first_run_alti = 1;
    }
    current_altitude = requestAltitude(15);
    Serial.print("Altitude: ");
    Serial.print(current_altitude);
}

