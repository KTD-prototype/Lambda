#include <SoftwareSerial.h>
#include <I2CLiquidCrystal.h>
#include <Wire.h>
SoftwareSerial JOY_send(8, 9);
I2CLiquidCrystal lcd(0x3c, (uint8_t)255);

int A = 0;
float wait = 0;
int JOY[6] = {0, 0, 0, 0, 0, 0};//JOYSTICKモジュールからの入力
int Throttle = 0, Elevator = 0, Aileron = 0, Rudder = 0, RS = 0, LS = 0;
byte mode = 0;//ロボットの動作モードを表す。0：休止、1：遠隔操縦、2：自律走行
byte discard;


void setup() {
  // put your setup code here, to run once:
  JOY_send.begin(9600);
  Serial.begin(115200);
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:

  Elevator = analogRead(5) / 4;//RX　ピンが出ている面がXの負方向なので注意
  Aileron = analogRead(4) / 4;//RY
  RS = analogRead(1) / 4;//RS
  Throttle = analogRead(3) / 4;//LX
  Rudder = analogRead(2) / 4;//LY
  LS = analogRead(0) / 4;//LS

  if (A == 0) {   //起動時に一度だけ送信
    sendIntData(Elevator, Aileron, Throttle, Rudder, RS, LS);
    A++;
    delay(1);
  }

  else if (JOY_send.read() == 'S') {  //ロボット側が、起動時または前回指令値読み込み終了時に送ってくる信号をキャッチしたら、送信
    sendIntData(Elevator, Aileron, Throttle, Rudder, RS, LS);
    //Serial.write();
  }

  while (JOY_send.available() < 2) { //ロボットから動作モードフィードバックと次の指令値リクエストの2バイトが届くまで待つ。
    //1バイト目が動作モードフィードバック（0～2）。2バイト目は次指令リクエスト(S)で、次のループで読みだす。
    wait++;
    if (wait > 100000) {
      lcd.setCursor(0, 0);
      lcd.println("COM LOST     ");
      lcd.setCursor(0, 1);
      lcd.println("                 ");
    }
  }

  wait = 0;

  mode = JOY_send.read();   //動作モード信号を読み取り・格納
  OperationMode(mode);      //動作モード信号から動作モードを判定し、表示する関数。
  //PrintJOYsignal(JOY[0],JOY[1],JOY[2],JOY[3],JOY[4],JOY[5]);


  //起動時を除き、ロボット側からリクエストが来ない限りはジョイスティックの読みを更新し続けるのみ。
}

