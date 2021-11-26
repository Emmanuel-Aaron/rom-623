#include <Wire.h> //library allows communication with I2C / TWI devices
#include <math.h> //library includes mathematical functions

const int MPU=0x68; //I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; //16-bit integers
int AcXcal,AcYcal,AcZcal,GyXcal,GyYcal,GyZcal,tcal; //calibration variables
double t,tx,tf,pitch,roll;


struct Vec3 {
    int x, y, z;
};

struct Orientation {
    double pitch, roll;
};

void activateBMP6500() {
    Wire.beginTransmission(MPU); //begin transmission to I2C slave device

    //Format of output
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)

    //Stop sending data for setup
    Wire.endTransmission(false); //restarts transmission to I2C slave device

    //Tell BMP to send data and stop after one cycle
    Wire.requestFrom(MPU,14,true); //request 14 registers in total  
}

int readTemp() {
    Tmp = Wire.read()<<8|Wire.read(); // 0x41 (TEMP_OUT_H) 0x42 (TEMP_OUT_L) 
    tx = Tmp - 1600;
    t = tx/340 + 36.53; //equation for temperature in degrees C from datasheet

    return t;
}

struct Vec3 readAccel() {
    struct Vec3 accel;

    //read accelerometer data
    accel.x = Wire.read()<<8|Wire.read() - 950; // 0x3B (ACCEL_XOUT_H) 0x3C (ACCEL_XOUT_L)  
    accel.y =Wire.read()<<8|Wire.read() - 300; // 0x3D (ACCEL_YOUT_H) 0x3E (ACCEL_YOUT_L) 
    accel.z =Wire.read()<<8|Wire.read() - 0; // 0x3F (ACCEL_ZOUT_H) 0x40 (ACCEL_ZOUT_L)

    return accel;
}

struct Vec3 readGyro() {
    struct Vec3 gyro;

    //read gyroscope data
    gyro.x = Wire.read()<<8|Wire.read() + 480; // 0x43 (GYRO_XOUT_H) 0x44 (GYRO_XOUT_L)
    gyro.y = Wire.read()<<8|Wire.read() + 170; // 0x45 (GYRO_YOUT_H) 0x46 (GYRO_YOUT_L)
    gyro.z = Wire.read()<<8|Wire.read() + 210; // 0x47 (GYRO_ZOUT_H) 0x48 (GYRO_ZOUT_L) 

    return gyro;
}


void setup()
{
    Wire.begin(); //initiate wire library and I2C
    Wire.beginTransmission(MPU); //begin transmission to I2C slave device
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // set to zero (wakes up the MPU-6050)  
    Wire.endTransmission(true); //ends transmission to I2C slave device
    Serial.begin(9600); //serial communication at 9600 bauds
}

void loop()
{

    activateBMP6500();

    struct Vec3 accel = readAccel();
    AcX = accel.x;
    AcY = accel.y;
    AcZ = accel.z;
  
    //Celcius
    Tmp = readTemp(); // 0x41 (TEMP_OUT_H) 0x42 (TEMP_OUT_L) 
  
    struct Vec3 gyro = readGyro();
    GyX = gyro.x; // 0x43 (GYRO_XOUT_H) 0x44 (GYRO_XOUT_L)
    GyY = gyro.y; // 0x45 (GYRO_YOUT_H) 0x46 (GYRO_YOUT_L)
    GyZ = gyro.z; // 0x47 (GYRO_ZOUT_H) 0x48 (GYRO_ZOUT_L) 


    //get pitch/roll
    struct Orientation orient = getAngle(AcX,AcY,AcZ);
  
    //printing values to serial port
    Serial.print("Angle: ");
    Serial.print("Pitch = "); Serial.print(orient.pitch);
    Serial.print(" Roll = "); Serial.println(orient.roll);
  
    Serial.print("Accelerometer: ");
    Serial.print("X = "); Serial.print(AcX);
    Serial.print(" Y = "); Serial.print(AcY);
    Serial.print(" Z = "); Serial.println(AcZ); 

    Serial.print("Temperature in celsius = "); Serial.print(t);  
  
    Serial.print("Gyroscope: ");
    Serial.print("X = "); Serial.print(GyX);
    Serial.print(" Y = "); Serial.print(GyY);
    Serial.print(" Z = "); Serial.println(GyZ);
  
    delay(1000);
}

//function to convert accelerometer values into pitch and roll
struct Orientation getAngle(int Ax,int Ay,int Az) 
{
    double x = Ax;
    double y = Ay;
    double z = Az;

    pitch = atan(x/sqrt((y*y) + (z*z))); //pitch calculation
    roll = atan(y/sqrt((x*x) + (z*z))); //roll calculation

    struct Orientation orient;
    //converting radians into degrees
    orient.pitch = pitch * (180.0/3.14);
    orient.roll = roll * (180.0/3.14) ;

    return orient;
}
