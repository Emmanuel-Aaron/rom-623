// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //

#define LOW 0
#define HIGH 1
#define echoPin 7 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 8 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
double clearance;
double base_clearance;

double requestAverageTimeDelay(int cycles) {
    double time_delay = 0;

    int i = 0;
    while(i < cycles) {
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);

        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        time_delay += pulseIn(echoPin, HIGH);
        i += 1;
    }

  return time_delay/i;
}


double requestClrearence(int cycles) {
    return (requestAverageTimeDelay(cycles)*(0.034/2) - base_clearance)/100;
}
