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

/*
float data[6];


void Sensordata(){
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);
  data[0] = -(Buf[0]<<8 | Buf[1]);
  data[1] = -(Buf[2]<<8 | Buf[3]);
  data[2] = (Buf[4]<<8 | Buf[5]);

  //Gyroscope
  data[3] = -(Buf[8]<<8 | Buf[9]);
  data[4] = -(Buf[10]<<8 | Buf[11]);
  data[5] = (Buf[12]<<8 | Buf[13]);

  data[0] = 4 * data[0] / 32768;
  data[1] = 4 * data[1] / 32768;
  data[2] = 4 * data[2] / 32768;
  data[3] = 500 * data[3] / 32768;
  data[4] = 500 * data[4] / 32768;
  data[5] = 500 * data[5] / 32768;
  
}
*/


long int cpt = 0;

//Main loop, read and display data
void loop() {

  //---------------//
  // :::Counter::: //

  //Display data counter
  Serial.print(cpt++, DEC);
  Serial.print("\t");

  

  //-------------------------------------//
  // ::: accelerometer and gyroscope ::: //
  //read accelerometer and gyroscope
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

  //Create 16bits values from 8 bits data


  //Accelerometer
  float ax = -(Buf[0]<<8 | Buf[1]);
  float ay = -(Buf[2]<<8 | Buf[3]);
  float az = (Buf[4]<<8 | Buf[5]);

  //Gyroscope
  float gx = -(Buf[8]<<8 | Buf[9]);
  float gy = -(Buf[10]<<8 | Buf[11]);
  float gz = (Buf[12]<<8 | Buf[13]);
  
  ax = 4 * ax / 32768;
  ay = 4 * ay / 32768;
  az = 4 * az / 32768;
  gx = 500 * gx / 32768;
  gy = 500 * gy / 32768;
  gz = 500 * gz / 32768;


  //-------------------------------------//
  // ::: display values ::: /
  Serial.print(ax, DEC);
  Serial.print("\t");
  Serial.print(ay, DEC);
  Serial.print("\t");
  Serial.print(az, DEC);
  Serial.print("\t");
  Serial.print(gx, DEC);
  Serial.print("\t");
  Serial.print(gy, DEC);
  Serial.print("\t");
  Serial.print(gz, DEC);
  Serial.print("\t");

  //End of line
  Serial.println("");
  delay(100);
}


/*
 * 
float SensorData(){
  uint8_t Buf[14];
  float sensordata[6];
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

  
  sensordata[0] = -(Buf[0]<<8 | Buf[1]);
  sensordata[1] = -(Buf[2]<<8 | Buf[3]);
  sensordata[2] = (Buf[4]<<8 | Buf[5]);

  sensordata[3] = -(Buf[8]<<8 | Buf[9]);
  sensordata[4] = -(Buf[10]<<8 | Buf[11]);
  sensordata[5] = (Buf[12]<<8 | Buf[13]);
  
  sensordata[0] = ACC_SCALE * sensordata[0] / 32768;
  sensordata[1] = ACC_SCALE * sensordata[1] / 32768;
  sensordata[2] = ACC_SCALE * sensordata[2] / 32768;

  sensordata[3] = GYR_SCALE * sensordata[3] / 32768;
  sensordata[4] = GYR_SCALE * sensordata[4] / 32768;
  sensordata[5] = GYR_SCALE * sensordata[5] / 32768;

  return sensordata;
}
 * 
 */
