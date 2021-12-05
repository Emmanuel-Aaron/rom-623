#include <math.h>
#include "/root/Development/rom-623/src/sensors/gyro/gyro_src.hpp"

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU();
  ort_error = averageOrientation(1000, 0);
}

void loop() {
  struct Orientation ort = averageOrientation(10, 1);
  updateOrientation(ort);
  printCurrentOrt();
  delay(100);
}
