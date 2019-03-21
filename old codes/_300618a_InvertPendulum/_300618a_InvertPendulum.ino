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
#define FRICTION_COMPLEMENT 10 //ギヤ抵抗等でPWM出力が弱いと回らなくなる。それを防ぐため、ゼロを除いた最低値（の絶対値）を決めておく。

unsigned long EXETIME = 0; //実行時間監視用
int mode = 0; //ロボットの動作モードを表す。0：休止、1：遠隔操縦、2：自律走行

volatile float data[6] = {0, 0, 0, 0, 0, 0}; //加速度3軸＋角速度3軸
volatile float Calib[6] = {0, 0, 0, 0, 0, 0}; //同上。キャリブレーション用。
volatile float ACCroll = 0, ACCpitch = 0, ACCyaw = 0; //加速度から計算した姿勢。
volatile float roll = 0, pitch = 0, yaw = 0;//姿勢角 ピッチ角は初期値-90度としておく（+90度をデフォルト=0度とするため）
volatile float preroll = 0, prepitch = 0, preyaw = 0;//前回姿勢角。加速度で相補フィルタした後の値で角速度を再算出するための変数
volatile float k = 0.05; //姿勢角計算時の、加速度から姿勢角を計算する成分の重み係数。重力以外の加速度が大きくかかっているときは加速度から算出される姿勢角の信用度を落とす。最大0.05（5%）
volatile int flag = 0;


float P = 35, D = 0.9, I = 10.375; //PIDの係数
float vel = 0, prevel = 0;//モータ目標速度、前回目標速度
float target_pitch = 1; //ピッチ角ターゲット=安定になる角度。とりあえず0度にしておく
float integral_pitch_error = 0, differential_pitch = 0; //ピッチ角誤差積算、ピッチ角速度
int val1 = 0, val2 = 0, val3 = 0, val4 = 0; //モータドライバへの指令値(0～255)
int count = 0;

int firstloop = 1;

void setup() {
  //シリアル通信開始。
  JOY_receive.begin(9600);
  Serial.begin(115200);
  Wire.begin();

  //タイマー割込み設定
  Timer1.initialize(10000); //10000us = 10msごとに割り込み（100Hz)
  Timer1.attachInterrupt(FLAG);

  //IMUの初期化
  //Configure sensor range
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_1000_DPS);
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_16_G);
  //Set by pass mode for the magnetometers
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);
  //Request first magnetometer single measurement
  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x01);

  //キャリブレーション（とりあえず無しにしておく
  //MPU9250_Calibration();

  //ピンモードの設定
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {

  //加速度7G以上かからない限りは制御を続ける
  while (abs(data[0]) < 8 && abs(data[1]) < 8 && abs(data[2]) < 8) {

    //ピッチ角に応じたモータ制御を実施する。
    motor_control(pitch);

    //割り込みが入るとフラグが1になる。
    //その際、姿勢角を更新する。
    if (flag == 1) {
      MPU9250_Sensordata(Calib[0], Calib[1], Calib[2], Calib[3], Calib[4], Calib[5]);
      MPU9250_PostureAngle();
      flag = 0;
      //EXETIME = micros();
      //Serial.println();
    }

    //Serial.println(D * data[4]);
    //Serial.print(",");
    //Serial.print(P * pitch);
    //Serial.print(",");
    //Serial.println(I * integral_pitch_error);
    //Serial.print(",");
    Serial.println(pitch);
    //Serial.print(",");
    //Serial.println(yaw);
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


  //5G以上かかった時の処理。
  //アナログ出力をすべてゼロにして、無限ループに入れる
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(11, 0);
  analogWrite(13, 0);
  while (0) {

  }
}


