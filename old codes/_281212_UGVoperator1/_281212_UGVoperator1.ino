#include<SoftwareSerial.h>
#include<TimerOne.h>
SoftwareSerial JOY_receive(14, 15);

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
#define SamplingRate 50 //Hz

int A = 0;
int timer = 0;
int mode = 0;
byte RMotor1 = 0, RMotor2 = 0, LMotor1 = 0, LMotor2 = 0, RS = 1, LS = 1;
volatile float data[6], Calib[6] = {0, 0, 0, 0, 0, 0};
volatile float ACCroll = 0, ACCpitch = 0, ACCyaw = 0;
volatile float roll = 0, pitch = 0, yaw = 0;
volatile float k = 0;

void setup() {
  JOY_receive.begin(9600);
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);

  //Calibration();

  Timer1.initialize(20000);
  Timer1.attachInterrupt(PostureAngle);
}

void loop() {

  Sensordata(Calib[0], Calib[1], Calib[2], Calib[3], Calib[4], Calib[5]);
  
  if (A == 0) {
    JOY_receive.write('S');
    A++;
  }

  while (JOY_receive.available() <= 6) {
    timer++;
    if (timer == 5000) {
      Mode_R(0, 0, 0, 0);
      mode = 0;
    }
  }
  timer = 0;


  if (JOY_receive.available() > 6) {
    //Serial.println('C');
    if (JOY_receive.read() == 'H') {
      RMotor1 = JOY_receive.read();
      RMotor2 = JOY_receive.read();
      LMotor1 = JOY_receive.read();
      LMotor2 = JOY_receive.read();
      RS = JOY_receive.read();
      LS = JOY_receive.read();

      ChangeMode(); //モード変更指令が入った場合に動作モードを変更する関数

      if (mode == 0) {
        Serial.println("mode : stop");
      }
      else if (mode == 1) {
        Serial.print("mode : remote  ");
        Mode_R(RMotor1, RMotor2, LMotor1, LMotor2); //指令値に基づきモータ駆動する関数
      }
      else if (mode == 2) {
        Serial.println("mode : auto");
      }

      JOY_receive.write(mode);//現在の動作モードをコントローラにフィードバックする
      JOY_receive.write('S');//一通り処理が終わったので、次の指令値をリモコン側にリクエスト
    }
  }
  else {
    Serial.println("wait");
  }
  /*
  Serial.print(RMotor1);
  Serial.print(",");
  Serial.print(RMotor2);
  Serial.print(",");
  Serial.print(roll);
  Serial.print(",");
  Serial.print(pitch);
  Serial.print(",");
  Serial.println(yaw);
  */
}
