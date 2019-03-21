//refered http://www.lucidarme.me/?p=5057

#include <Wire.h>

#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS     0x0C

#define GYRO_FULL_SCALE_250_DPS   0x00
#define GYRO_FULL_SCALE_500_DPS   0x08
#define GYRO_FULL_SCALE_1000_DPS  0x10
#define GYRO_FULL_SCALE_2000_DPS  0x18

#define ACC_FULL_SCALE_2_G    0x00
#define ACC_FULL_SCALE_4_G    0x08
#define ACC_FULL_SCALE_8_G    0x10
#define ACC_FULL_SCALE_16_G   0x18

#define ACC_SCALE 4
#define GYR_SCALE 500


//this function read Nbytes bytes from I2C device at address Address.
//put read bytes starting at register Register in the data Array.
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data){
  //set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  //read Nbytes
  Wire.requestFrom(Address, Nbytes);
  uint8_t index = 0;
  while(Wire.available())
    Data[index++] = Wire.read();
}


//Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data){
  //Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}





//Initiallizations
void setup() {
  //Arduino initializations
  Wire.begin();
  Serial.begin(115200);

  //Configure sensor range
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_500_DPS);
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_4_G);

  //Set by pass mode for the magnetometers
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);

  //Request first magnetometer single measurement
  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x01);
}


float data[6], Calib[6] = {0,0,0,0,0,0};


long int cpt = 0;

//Main loop, read and display data
void loop() {

  //---------------//
  // :::Counter::: //

  Calibration();
  
  //Display data counter
  while(1){
    Serial.print(cpt++, DEC);
    Serial.print("\t");

    Sensordata(Calib[0], Calib[1], Calib[2], Calib[3], Calib[4], Calib[5]);

    //-------------------------------------//
    // ::: accelerometer and gyroscope ::: //
    //read accelerometer and gyroscope
  
    //-------------------------------------//
    // ::: display values ::: /
    Serial.print(data[0], DEC);
    Serial.print("\t");
    Serial.print(data[1], DEC);
    Serial.print("\t");
    Serial.print(data[2], DEC);
    Serial.print("\t");
    Serial.print(data[3], DEC);
    Serial.print("\t");
    Serial.print(data[4], DEC);
    Serial.print("\t");
    Serial.print(data[5], DEC);
    Serial.print("\t");

    //End of line
    Serial.println("");
    delay(100);
  }
}

