/*     front
     M1     M2

     M3     M4
   /


  //refered http://www.lucidarme.me/?p=5057
  //http://garchiving.com/gyro-drift-correction/ and peripherals
  /* refered http://www.isopro91.com/entry/2014/10/21/arduino/servo/robot
  //        _281116_MPU9250_PCA9685_Angle_Revice
*/

#include<SoftwareSerial.h>
SoftwareSerial JOY_receive(14, 15);
#include<TimerOne.h>
#include<Wire.h>
#include<Adafruit_PWMServoDriver.h>

#define PWM_MIN 810
#define PWM_MAX 1610

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
void pwm_write(int n, int ang) {
  ang = map(ang, 0, 255, PWM_MIN, PWM_MAX);
  pwm.setPWM(n, 0, ang);
}

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

#define ACC_SCALE 8
#define GYR_SCALE 1000
#define SAMPLINGRATE 50 //Hz

int A = 0;
int B = 0;
int wait = 0;
unsigned long EXETIME = 0; //実行時間監視用
int ControlMode = 0; //ドローンの動作モードを表す。0と2：休止、1：遠隔操縦、3：自律走行
int FlightMode = 0; //ドローンの飛行中のモード
int TO = 0; //1なら離陸、0ならスタンバイ
byte Elevator = 0, Aileron = 0, Throttle = 0, Rudder = 0, RS = 1, LS = 1;
int M1 = 810, M2 = 810, M3 = 810, M4 = 810;
float height = 0; //飛行高度（超音波）
byte discard;
unsigned long t;

volatile float data[6] = {0, 0, 0, 0, 0, 0}; //加速度3軸＋角速度3軸
volatile float Calib[6] = {0, 0, 0, 0, 0, 0}; //同上。キャリブレーション用。
volatile float ACCroll = 0, ACCpitch = 0, ACCyaw = 0; //加速度から計算した姿勢。
volatile float roll = 0, pitch = 0, yaw = 0; //姿勢角
volatile float k = 0.05; //姿勢角計算時の、加速度から姿勢角を計算する成分の重み係数。重力以外の加速度が大きくかかっているときは加速度から算出される姿勢角の信用度を落とす。最大0.05（5%）
volatile int flag = 0;


void setup() {
  //シリアル通信開始。
  JOY_receive.begin(9600);
  Serial.begin(115200);
  //I2C通信開始
  Wire.begin();

  //PCA9685関連（PWM関連）
  pwm.begin();
  pwm.setPWMFreq(200); // PWM周波数：200Hz
  //ESCキャリブレーション
  //pwm_write(15, 255);
  //delay(5000);
  //pwm_write(15, 0);
  //delay(3000);

  //IMUの初期化、キャリブレーション
  //Configure sensor range
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_1000_DPS);
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_8_G);
  //Set by pass mode for the magnetometers
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);
  //Request first magnetometer single measurement
  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x01);

  //キャリブレーション
  MPU9250_Calibration();

  //タイマー割込み設定
  Timer1.initialize(20000);
  Timer1.attachInterrupt(FLAG);

  //ピンモードの設定
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {


  if (A == 0) {//起動時に一度だけ送信
    delay(1);
    JOY_receive.write(ControlMode);
    JOY_receive.write('S');
    A++;
  }


  if (JOY_receive.available() > 6) {  //受信バッファにデータが6バイトより多くある時（ヘッダバイト＋ジョイスティック信号６バイト
    if (JOY_receive.read() == 'H') {
      Elevator = JOY_receive.read();
      Aileron = JOY_receive.read();
      Throttle = JOY_receive.read();
      Rudder = JOY_receive.read();
      RS = JOY_receive.read();
      LS = JOY_receive.read();

      ChangeMode(); //モード変更指令が入った場合に動作モードを変更する関数

      if (ControlMode == 0 || ControlMode == 2) {//ControlMode : stop
        //Prop(810, 810, 810, 810);
      }

      else if (ControlMode == 1) {//ControlMode : remote
        if (FlightMode == 0) {
          takeoff();
        }
        else if (FlightMode == 1) {
          fly();
        }
        else if (FlightMode == 2) {
          landing();
        }
        //Prop(M1, M2, M3, M4); //モータ指令値に基づきモータ駆動する関数
      }

      else if (ControlMode == 3) {//ControlMode : remote
        FlightMode = 0;
        //Prop(810, 810, 810, 810);
      }
    }
    else {  //受信バッファにデータは6バイトより多くあるものの、先頭がヘッダバイトではないとき（通信に欠落があったとき
      while (JOY_receive.available() > 0) {
        ControlMode = 0;
        discard = JOY_receive.read(); //受信バッファが空になるまでデータを読み出して、リセット。
      }
    }
    //一通り処理を終えたので、現在モードのフィードバックと次回指令地のリクエストを行う。
    JOY_receive.write(ControlMode);//現在の動作モードをコントローラにフィードバックする
    JOY_receive.write('S');//一通り処理が終わったので、次の指令値をリモコン側にリクエスト
    wait = 0;
  }

  else {
    wait++;
    if (wait == 2000) {//2000ループ（1ループ2～3msとすると5,6秒くらい）経っても6バイト貯まらなかったら、通信断と判定しControlModeをSTOPとする。
      ControlMode = 0;
      while (JOY_receive.available() > 0) {
        discard = JOY_receive.read(); //受信バッファが空になるまでデータを読み出して、リセット。
      }
      //完全に通信断と判定し、新たにコントローラに現在モードと次の指令値をリクエスト
      JOY_receive.write(ControlMode);//現在の動作モードをコントローラにフィードバックする
      JOY_receive.write('S');//一通り処理が終わったので、次の指令値をリモコン側にリクエスト
      wait = 0;
    }
  }




  //get sensor data and contain into "data[6]"

  if (flag == 1) {
    MPU9250_Sensordata(Calib[0], Calib[1], Calib[2], Calib[3], Calib[4], Calib[5]);
    MPU9250_PostureAngle();
    flag = 0;
    //EXETIME = micros();
    //Serial.println(EXETIME);
    //ここで見てみると、大体141853096～141875036の22000usec=22msecくらいで割込みが入っている。
    //めちゃくちゃ精度が良いわけでもないが、まあこんなものか。
  }


  //delayMicroseconds(400);
  //EXETIME = micros();
  //Serial.println(EXETIME);
  //なぜか多少プログラム周期を遅らせないと動かない。
  //こっちを使って遅らせると600us周期くらいでプログラムが回る。

  /*
    Serial.print(M1);
    Serial.print(",   ");
    Serial.print(M2);
    Serial.print(",   ");
    Serial.print(M3);
    Serial.print(",   ");
    Serial.println(M4);
  */
  //EXETIME = micros();
  //Serial.println(EXETIME);
  //こちらを使っても同じか気持ち早いくらい。


  
    Serial.print(pitch);
    Serial.print(",");
    Serial.print(roll);
    Serial.print(",");
    Serial.println(yaw);
  
}


