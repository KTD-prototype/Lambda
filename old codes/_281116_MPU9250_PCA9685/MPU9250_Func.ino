#include <math.h>

void Sensordata(float Cax, float Cay, float Caz, float Cgx, float Cgy, float Cgz){
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);
  data[0] = -(Buf[0]<<8 | Buf[1]);
  data[1] = -(Buf[2]<<8 | Buf[3]);
  data[2] = (Buf[4]<<8 | Buf[5]);

  //Gyroscope
  data[3] = -(Buf[8]<<8 | Buf[9]);
  data[4] = -(Buf[10]<<8 | Buf[11]);
  data[5] = (Buf[12]<<8 | Buf[13]);

  data[0] = 4 * data[0] / 32768 - Cax;
  data[1] = 4 * data[1] / 32768 - Cay;
  data[2] = 4 * data[2] / 32768 - Caz;
  data[3] = 500 * data[3] / 32768 - Cgx;
  data[4] = 500 * data[4] / 32768 - Cgy;
  data[5] = 500 * data[5] / 32768 - Cgz;
  
}


void Calibration(){
  int i = 0;
  float SUMax = 0, SUMay = 0, SUMaz = 0, SUMgx = 0, SUMgy = 0, SUMgz = 0;
  while(i < 1000){
    Sensordata(Calib[0], Calib[1], Calib[2], Calib[3], Calib[4], Calib[5]);
    SUMax += data[0];
    SUMay += data[1];
    SUMaz += data[2] - 1;
    SUMgx += data[3];
    SUMgy += data[4];
    SUMgz += data[5];
    i++;
  }
  Calib[0] = SUMax / 1000;
  Calib[1] = SUMay / 1000;
  Calib[2] = SUMaz / 1000;
  Calib[3] = SUMgx / 1000;
  Calib[4] = SUMgy / 1000;
  Calib[5] = SUMgz / 1000;
}


void PostureAngle(){
  //get sensor data and contain into "data[6]"
  Sensordata(Calib[0], Calib[1], Calib[2], Calib[3], Calib[4], Calib[5]);

  //when accleraration more or less than 1G is loaded to sensor(resultant vector of ax,ay,az),  ACCroll and ACCpitch will offset from true value.
  //so if then, smallen the coefficient for complementary filter 
  float ACCvectorSUM = sqrt(pow(data[0], 2) + pow(data[1], 2) + pow(data[2], 2)); 
  k =0.05 * (1 / pow((pow(ACCvectorSUM - 1, 2) + 1), 4));
  
  //calculate pitch and roll by accelerometer with LPF
  ACCroll = 0.75 * ACCroll + 0.25 * atan(data[1] / data[2]) * 180 / M_PI;
  ACCpitch = 0.75 * ACCpitch + 0.25 * atan(data[0] / sqrt(pow(data[1],2) + pow(data[2],2))) * 180 / M_PI;

  //calculate pitch/roll/yaw by gyrosensor (About pitch & roll, using Complementary Filter)
  roll = (1 - k) * (roll + data[3]  / SamplingRate) + k * ACCroll;
  pitch = (1 - k) * (pitch + data[4] / SamplingRate) + k * ACCpitch;
  if(fabs(data[5]) < 0.1){
    yaw = yaw;
  }
  else yaw = yaw + data[5] / SamplingRate;
}

