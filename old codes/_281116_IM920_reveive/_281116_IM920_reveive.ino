/* IM920 DemoProgram */
#include <SoftwareSerial.h>
SoftwareSerial IM92Serial(8, 9); // ソフトウエアシリアル
int vol=0, vol_new=0, diff, busy;

void setup() {
 Serial.begin(19200);
 IM92Serial.begin(19200); // ソフトウエアシリアル 初期化
 pinMode(10, INPUT); // Busy 信号 Pin10 入力
}



int i = 0;
char c = 'a';
void loop() {
 vol_new = analogRead(0)/4; // Analog_0 データ取得 8bit に変換
 diff = abs(vol_new - vol); // 前回データと比較 差分を diff 変数に
 
 busy = digitalRead(10); // Busy 信号 読み取り
 //IM92Serial.println(i);
 if(IM92Serial.available()){
 c = IM92Serial.read();
 Serial.print(c);
 if(i % 30 == 0){
 Serial.println("");
 Serial.println("");
 }
 i++;
}
}
