/*
   ロボットからの返答に基づき、ロボットの動作モードを判定
*/
void OperationMode(byte value) {
  switch (value) {
    case 0:
      Serial.println("mode : stop");
      break;
    case 1:
      Serial.println("mode : remote");
      break;

    case 2:
      Serial.println("mode : auto");
      break;

    case 'S':
      Serial.println('S');
      break;

    default:
      Serial.println("wait");
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
 * ジョイスティックの読み取りデータ（を4で割ったもの）を出力
 */
 void PrintJOYsignal(int val1, int val2, int val3, int val4, int val5, int val6){
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

