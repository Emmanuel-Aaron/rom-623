#include "/root/Development/rom-623/src/sensors/ultrasonic/ultra.c"

void setup() {
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  base_clearance = 0;
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  base_clearance = requestClrearence(1000);
  Serial.print("Base Clearance: ");
  Serial.print(base_clearance);
  Serial.println(" cm");
}
void loop() {
  // Clears the trigPin condition
  // Displays the distance on the Serial Monitor
  //
  Serial.print("Distance: ");
  Serial.print(requestClrearence(100));
  Serial.println(" cm");
}
