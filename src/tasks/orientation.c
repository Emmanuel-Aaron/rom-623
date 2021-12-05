#include "/root/Development/rom-623/src/sensors/gyro/gyro_src.hpp"

int first_run_orient = 0;

void orient() {
    digitalWrite(11, HIGH);
    delay(100);
    digitalWrite(11, LOW);
    if(first_run_orient == 0) {
        Wire.begin();
        setupMPU();
        ort_error = averageOrientation(1000, 0);

        first_run_orient = 1;
    }
    struct Orientation ort = averageOrientation(10, 1); 
    updateOrientation(ort); 
    printCurrentOrt(); 
}
