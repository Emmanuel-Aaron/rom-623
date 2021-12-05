#include "SFE_BMP180.h"
#include <Wire.h>

SFE_BMP180 pressure;
double current_altitude;
double baseline; // baseline pressure

double getPressure()
{
  char status;
  double T,P,p0,a;

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure mesurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}

double requestAveragePressure(int cycles) {
    double a_pressure = 0;

    int i = 0;
    while(i < cycles) {
        a_pressure += getPressure();
//        Serial.print("pressure: ");Serial.println(a_pressure/i);
        i += 1;
        delay(10);
    }

    return (a_pressure/i);
}

double requestRelativePressure(int cycles) {
    return requestAveragePressure(cycles);
}

void setBasePressure(int cycles) {
    baseline = requestAveragePressure(cycles);
}

double requestAltitude(int cycles) {
    double p = requestRelativePressure(cycles);
    return pressure.altitude(p, baseline);
}
