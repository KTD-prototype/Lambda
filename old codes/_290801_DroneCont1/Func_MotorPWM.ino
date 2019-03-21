/*
 * モータ指令値とジョイスティックプッシュボタン状態を送信する関数
 */
void sendIntData(int value1, int value2, int value3, int value4, int value5, int value6) {
  JOY_send.write('H');
  JOY_send.write(value1);
  JOY_send.write(value2);
  JOY_send.write(value3);
  JOY_send.write(value4);
  JOY_send.write(value5);
  JOY_send.write(value6);
}


