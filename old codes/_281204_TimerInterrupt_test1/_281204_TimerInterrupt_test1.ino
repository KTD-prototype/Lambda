#include<TimerOne.h>
#include<Wire.h>

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

#define ACC_SCALE 4 //g
#define GYR_SCALE 500 //degree per second
#define SAMPLINGRATE 20 //Hz  or sample/50ms


volatile int A = 0; //全体プログラムの最初のループであることを示すフラグ。
volatile float data[6] = {0, 0, 0, 0, 0, 0}; //加速度3軸＋角速度3軸
volatile float Calib[6] = {0, 0, 0, 0, 0, 0}; //同上。キャリブレーション用。
volatile float ACCroll = 0, ACCpitch = 0, ACCyaw = 0; //加速度から計算した姿勢。
volatile float k = 0.05; //姿勢角計算時の、加速度から姿勢角を計算する成分の重み係数。重力以外の加速度が大きくかかっているときは加速度から算出される姿勢角の信用度を落とす。最大0.05（5%）
volatile float roll = 0, pitch = 0, yaw = 0; //姿勢角

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

  MPU9250_Initialization();

  Timer1.initialize(50000);
  Timer1.attachInterrupt(PostureAngle);
  interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (A == 0) {//最初のループなら、センサをキャリブレーション。
    MPU9250_Calibration();
    A++;
  }
  PostureAngle();

  Serial.print("roll : ");
  Serial.print(roll, DEC);
  Serial.print("\t");
  Serial.print("pitch : ");
  Serial.print(pitch, DEC);
  Serial.print("\t");
  Serial.print("yaw : ");
  Serial.println(yaw, DEC);
  interrupts();
}


void MPU9250_Initialization() {
  //MPU9250測定レンジを決定
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_500_DPS);
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_4_G);

  //地磁気センサのバイパスモードを設定
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);
  //地磁気センサの最初の測定を一回だけリクエスト
  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x01);
  interrupts();
}

//アドレス「Address」にあるI2CデバイスからNバイトの値を読み取る関数。
//読み取りバイトをデータ配列内のレジスタ「register」に書き込む。
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
  //set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  //read Nbytes
  Wire.requestFrom(Address, Nbytes);
  uint8_t index = 0;
  while (Wire.available())
    Data[index++] = Wire.read();
    interrupts();
}


//バイト型データ「Data」を「Address」にあるレジスタ「Register」にかきこむ　
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data) {
  //Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
  interrupts();
}


//MPU9250のキャリブレーション。1000サンプルの平均値をオフセット
void MPU9250_Calibration() {
  int i = 0;
  float SUMax = 0, SUMay = 0, SUMaz = 0, SUMgx = 0, SUMgy = 0, SUMgz = 0;
  while (i < 1000) {
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
  interrupts();
}


//加速度、角速度の生データ読み出し
void Sensordata(float Cax, float Cay, float Caz, float Cgx, float Cgy, float Cgz) {
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);
  data[0] = -(Buf[0] << 8 | Buf[1]);
  data[1] = -(Buf[2] << 8 | Buf[3]);
  data[2] = (Buf[4] << 8 | Buf[5]);

  //Gyroscope
  data[3] = -(Buf[8] << 8 | Buf[9]);
  data[4] = -(Buf[10] << 8 | Buf[11]);
  data[5] = (Buf[12] << 8 | Buf[13]);

  data[0] = 4 * data[0] / 32768 - Cax;
  data[1] = 4 * data[1] / 32768 - Cay;
  data[2] = 4 * data[2] / 32768 - Caz;
  data[3] = 500 * data[3] / 32768 - Cgx;
  data[4] = 500 * data[4] / 32768 - Cgy;
  data[5] = 500 * data[5] / 32768 - Cgz;
  interrupts();
}


void PostureAngle() {
  //get sensor data and contain into "data[6]"
  Sensordata(Calib[0], Calib[1], Calib[2], Calib[3], Calib[4], Calib[5]);

  //when accleraration more or less than 1G is loaded to sensor(resultant vector of ax,ay,az),  ACCroll and ACCpitch will offset from true value.
  //so if then, smallen the coefficient for complementary filter
  float ACCvectorSUM = sqrt(pow(data[0], 2) + pow(data[1], 2) + pow(data[2], 2));
  k = 0.05 * (1 / pow((pow(ACCvectorSUM - 1, 2) + 1), 4));

  //calculate pitch and roll by accelerometer with LPF
  ACCroll = 0.95 * ACCroll + 0.05 * atan2(data[1],  data[2]) * 180 / M_PI;
  ACCpitch = 0.95 * ACCpitch + 0.05 * atan2(data[0], sqrt(pow(data[1], 2) + pow(data[2], 2))) * 180 / M_PI;

  //calculate pitch/roll/yaw by gyrosensor (About pitch & roll, using Complementary Filter)
  roll = (1 - k) * (roll + data[3] * (1 / SAMPLINGRATE)) + k * ACCroll;
  pitch = (1 - k) * (pitch + (-1 * data[4]) * (1 / SAMPLINGRATE)) + k * ACCpitch; //ピッチだけジャイロの角速度データが正負逆っぽい
  if (fabs(data[5]) < 0.1) { //ヨーレートが0.1°/sec未満なら、ゼロとする。
    yaw = yaw;
  }
  else yaw = yaw + data[5] * (1 / SAMPLINGRATE);
  interrupts();
}
