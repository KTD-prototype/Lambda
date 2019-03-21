//refered http://www.lucidarme.me/?p=5057
//http://garchiving.com/gyro-drift-correction/ and peripherals

#include<SoftwareSerial.h>
SoftwareSerial JOY_receive(14, 15);
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

#define ACC_SCALE 16
#define GYR_SCALE 1000
#define SAMPLINGRATE 100 //Hz

int A = 0;
int B = 0;
int wait = 0;
unsigned long EXETIME = 0; //実行時間監視用
int mode = 0; //ロボットの動作モードを表す。0：休止、1：遠隔操縦、2：自律走行
byte RMotor1 = 0, RMotor2 = 0, LMotor1 = 0, LMotor2 = 0, RS = 1, LS = 1;
byte discard;
unsigned long t;

volatile float data[6] = {0, 0, 0, 0, 0, 0}; //加速度3軸＋角速度3軸
volatile float Calib[6] = {0, 0, 0, 0, 0, 0}; //同上。キャリブレーション用。
volatile float ACCroll = 0, ACCpitch = 0, ACCyaw = 0; //加速度から計算した姿勢。
volatile float roll = 0, pitch = 0, yaw = 0, roll2 = 0, yaw2 = 0;//姿勢角
volatile float k = 0.05; //姿勢角計算時の、加速度から姿勢角を計算する成分の重み係数。重力以外の加速度が大きくかかっているときは加速度から算出される姿勢角の信用度を落とす。最大0.05（5%）
volatile int flag = 0;


void setup() {
  //シリアル通信開始。
  JOY_receive.begin(9600);
  Serial.begin(115200);
  Wire.begin();

  //IMUの初期化、キャリブレーション
  //Configure sensor range
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_1000_DPS);
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_16_G);
  //Set by pass mode for the magnetometers
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);
  //Request first magnetometer single measurement
  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x01);

  //キャリブレーション
  MPU9250_Calibration();

  //タイマー割込み設定
  Timer1.initialize(10000); //10000us = 10msごとに割り込み（100Hz)
  Timer1.attachInterrupt(FLAG);

  //ピンモードの設定
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {



  //get sensor data and contain into "data[6]"

  if (flag == 1) {
    MPU9250_Sensordata(Calib[0], Calib[1], Calib[2], Calib[3], Calib[4], Calib[5]);
    MPU9250_PostureAngle();
    flag = 0;
    //EXETIME = micros();
    //Serial.println();
  }
  roll2 = yaw;
  yaw2 = roll;
  Serial.print(pitch);
  Serial.print(",");
  Serial.print(roll2);
  Serial.print(",");
  Serial.println(yaw2);
  //EXETIME = micros();  //実行時間（us）をEXETIMEに代入
  //Serial.println(EXETIME); //1ループあたりを表示。300us = 0.3ms（タイマ割り込みないとき）で回っている。

  /*
    Serial.print(pitch);
    Serial.print(",");
    Serial.print(roll);
    Serial.print(",");
    Serial.println(yaw);
  */

}


