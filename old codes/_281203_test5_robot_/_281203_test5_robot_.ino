#include<SoftwareSerial.h>
#include<MsTimer2.h>
SoftwareSerial JOY_receive(14, 15);

int A = 0;
int timer = 0;
int mode = 0;
byte RMotor1 = 0, RMotor2 = 0, LMotor1 = 0, LMotor2 = 0, RS = 1, LS = 1;

void setup() {
  JOY_receive.begin(9600);
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  MsTimer2::set(20, PostureAngle); //[数値]msごとにPostureAngle関数を実行するようにセット
  MsTimer2::start();
}

void loop() {

  if (A == 0) {
    JOY_receive.write('S');
    A++;
  }

  while (JOY_receive.available() <= 6) {
    delay(1);
    timer++;
    if (timer == 5000) {
      mode_R(0, 0, 0, 0);
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
        mode_R(RMotor1, RMotor2, LMotor1, LMotor2); //指令値に基づきモータ駆動する関数
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
}
