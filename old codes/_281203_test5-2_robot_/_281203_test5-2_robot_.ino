#include<SoftwareSerial.h>
SoftwareSerial JOY_receive(14, 15);


int A = 0;
int B = 0;
int timer = 0;
int mode = 0; //ロボットの動作モードを表す。0：休止、1：遠隔操縦、2：自律走行
byte RMotor1 = 0, RMotor2 = 0, LMotor1 = 0, LMotor2 = 0, RS = 1, LS = 1;
volatile float roll = 0, pitch = 0, yaw = 0; //姿勢角

void setup() {
  //シリアル通信開始。
  JOY_receive.begin(9600);
  Serial.begin(115200);

  //ピンモードの設定
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {

  if (A == 0) {
    JOY_receive.write('S');
    A++;
  }

  //コントローラの指令値が受信バッファに貯まるまで待機。1000ms経っても貯まらなかったら（通信断の時など）、モータ指令値を全て0にして、STOPモードへ移行。
  while (JOY_receive.available() <= 6) {
    timer++;
    if (timer == 10000) {
      mode_R(0, 0, 0, 0);
      mode = 0;
      break;
    }
  }
  timer = 0;//タイマリセット
  


  if (JOY_receive.available() > 6) {
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
        mode_R(RMotor1, RMotor2, LMotor1, LMotor2); //指令値に基づきモータ駆動する関数
      }
      else if (mode == 2) {
        Serial.println("mode : auto");
      }

      JOY_receive.write(mode);//現在の動作モードをコントローラにフィードバックする
      JOY_receive.write('S');//一通り処理が終わったので、次の指令値をリモコン側にリクエスト

    }
    else {
      Serial.println("wait");
    }
  }
}


