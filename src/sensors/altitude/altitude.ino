#include "altitude.h"

void setup()
{
  Serial.begin(9600);

  pressure.begin();
  setBasePressure(200);
  Serial.println(baseline);
}

void loop()
{
    current_altitude = requestAltitude(15);
  
    Serial.println(current_altitude);
}


