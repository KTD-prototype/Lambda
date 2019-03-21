/*
   ロボットからの返答に基づき、ロボットの動作モードを判定
*/
void OperationMode(byte value) {
  switch (value) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.println("mode : stop");
      lcd.setCursor(0, 1);
      lcd.println("                 ");
      break;

    case 1:
      lcd.setCursor(0, 0);
      lcd.print("mode : remote");
      lcd.setCursor(0, 1);
      lcd.println(Throttle);
      lcd.setCursor(4, 1);
      lcd.println(Rudder);
      lcd.setCursor(8, 1);
      lcd.println(Elevator);
      lcd.setCursor(12, 1);
      lcd.println(Aileron);
      break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.println("mode : stop");
      lcd.setCursor(0, 1);
      lcd.println("                 ");
      break;

    case 3:
      lcd.setCursor(0, 0);
      lcd.println("mode : auto");
      lcd.setCursor(0, 1);
      lcd.println("                  ");
      break;

    case 'S':
      lcd.println("S");
      break;

    default:
      lcd.println("wait");
  }
}


/*
   モータードライバへの指令値をプリントアウト
   もっと直感的にわかりやすい数字にしたいなあ。。。
*/
void PrintMotor(int value1, int value2, int value3, int value4) {
  Serial.print(value1);
  Serial.print("  ||  ");
  Serial.print(value2);
  Serial.print("  ||  ");
  Serial.print(value3);
  Serial.print("  ||  ");
  Serial.print(value4);
  Serial.print("  ||  ");
}


/*
   ジョイスティックの読み取りデータ（を4で割ったもの）を出力
*/
void PrintJOYsignal(int val1, int val2, int val3, int val4, int val5, int val6) {
  Serial.print(val1);
  Serial.print("  ||  ");
  Serial.print(val2);
  Serial.print("  ||  ");
  Serial.print(val3);
  Serial.print("  ||  ");
  Serial.print(val4);
  Serial.print("  ||  ");
  Serial.print(val5);
  Serial.print("  ||  ");
  Serial.print(val6);
  Serial.println("");
}

