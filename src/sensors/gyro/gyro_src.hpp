#include <Wire.h>
#include <math.h>

double error_pitch;
double error_roll;

struct Vec3 {
    double x;
    double y;
    double z;
};

struct Orientation {
    double pitch;
    double roll;
};


struct Orientation current_ort = (struct Orientation){0};
struct Orientation ort_error = (struct Orientation){0};
int first = 1;

void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4)
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5)
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission();
}

struct Vec3 processAccelData(struct Vec3 accel){
    struct Vec3 g_force;

  g_force.x = (accel.x) / 16384.0;
  g_force.y = (accel.y) / 16384.0;
  g_force.z = (accel.z) / 16384.0;
  return g_force;
}

struct Vec3 recordAccelRegisters() {
    struct Vec3 accel;

  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)

  while(Wire.available() < 6);
  accel.x = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accel.y = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accel.z = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  return processAccelData(accel);
}

struct Orientation requestOrientation() {
    struct Vec3 g_force = recordAccelRegisters();

    struct Orientation ort;
    ort.roll = atan(g_force.y / sqrt(pow(g_force.x, 2) + pow(g_force.z, 2))) * 180/PI;
    ort.pitch = atan(-1 * g_force.x / sqrt(pow(g_force.y, 2) + pow(g_force.z, 2))) * 180/PI;

    return ort;
}

struct Orientation averageOrientation(int cycles, int error) {
    struct Orientation a_ort = (struct Orientation){0};
    struct Orientation c_ort = (struct Orientation){0};

    double e_roll = 0;
    double e_pitch = 0;
    if(error == 1) {
        e_roll = ort_error.roll;
        e_pitch = ort_error.pitch;
    }

    int i = 0;
    while(i < cycles) {
        c_ort = requestOrientation();

        a_ort.roll += (c_ort.roll - e_roll);
        a_ort.pitch += (c_ort.pitch - e_pitch);

        i += 1;
    }
    a_ort.roll = a_ort.roll/i;
    a_ort.pitch = a_ort.pitch/i;

    return a_ort;
}



void updateOrientation(struct Orientation ort) {
    current_ort.roll = ort.roll;
    current_ort.pitch = ort.pitch;
}


void printCurrentOrt() {
     Serial.println("");
     Serial.print("Roll: ");
     Serial.print(current_ort.roll);
     Serial.print(" Pitch: ");
     Serial.print(current_ort.pitch);
     Serial.println("");
}

void printOrientation(struct Orientation ort) {
     Serial.println(""); //Had to print line for output to be registered on serial monitor
     Serial.print("Roll: ");
     Serial.print(ort.roll);
     Serial.print(" Pitch: ");
     Serial.print(ort.pitch);
}

