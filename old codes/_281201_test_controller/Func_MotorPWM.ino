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


/*
   ジョイスティック読み取り値からモーター指令値を読み取る関数
*/
#define RemoteYawGainR 1.4 //遠隔操縦時、右旋回ゲイン
#define RemoteYawGainL 0.75 //遠隔操縦時、左旋回ゲイン（0 ～ 1）

void MotorPWM(int value1, int value2) {
  if (value2 > 131 || value2 < 124) { //左の縦方向（直進方向）に入力がある場合（この場合、並進をフルで入れても緩やかに曲がる
    if (value2 > 131) {//左スティックで前進が入っているとき
      //直進成分を入力
      RMotor1 = (value2 - 128) * 2; //正転
      RMotor2 = 0;
      LMotor1 = (value2 - 128) * 2; //正転
      LMotor2 = 0;
      if (value1 > 131) {//右スティックで右進が入っているとき
        RMotor1 = RMotor1 - (value1 - 128) * RemoteYawGainR; //右モータ減速（正転）（最後の乗算が左右方向ゲイン
        LMotor1 = LMotor1 + (value1 - 128) * RemoteYawGainR; //左モータ加速（正転）（最後の乗算が左右方向ゲイン
        if (LMotor1 > 255) {//サチってたら無視して255とする
          LMotor1 = 255;
        }
        if (RMotor1 < 0) {//値が負になっていたらゼロにしておく
          RMotor1 = 0;
        }
      }
      else if (value1 < 124) {//右スティックで左進が入っているとき
        RMotor1 = RMotor1 + (255 - value1 * 2) * RemoteYawGainL; //右モータ加速（正転）（最後の乗算が左右方向ゲイン
        LMotor1 = LMotor1 - (255 - value1 * 2) * RemoteYawGainL; //左モータ減速（正転）（最後の乗算が左右方向ゲイン
        if (RMotor1 > 255) {//サチってたら無視して255とする
          RMotor1 = 255;
        }
        if (LMotor1 < 0) {//値が負になっていたらゼロにしておく
          LMotor1 = 0;
        }
      }
    }
    else if (value2 < 124) { //左スティックで後進が入っているとき
      //直進成分を入力
      RMotor1 = 0;
      RMotor2 = 255 - value2 * 2; //逆転
      LMotor1 = 0;
      LMotor2 = 255 - value2 * 2; //逆転
      if (value1 > 131) {//右スティックで右進が入っているとき
        RMotor2 = RMotor2 - (value1 - 128) * RemoteYawGainR; //右モータ減速（逆転）（最後の乗算が左右方向ゲイン
        LMotor2 = LMotor2 + (value1 - 128) * RemoteYawGainR; //左モータ加速（逆転）（最後の乗算が左右方向ゲイン
        if (LMotor2 > 255) {//サチってたら無視して255とする
          LMotor2 = 255;
        }
        if (RMotor2 < 0) {//値が負になっていたらゼロにしておく
          RMotor2 = 0;
        }
      }
      else if (value1 < 124) {//右スティックで左進が入っているとき
        RMotor2 = RMotor2 + (255 - value1 * 2) * RemoteYawGainL; //右モータ加速（逆転）（最後の乗算が左右方向ゲイン
        LMotor2 = LMotor2 - (255 - value1 * 2) * RemoteYawGainL; //左モータ減速（逆転）（最後の乗算が左右方向ゲイン
        if (RMotor2 > 255) {//サチってたら無視して255とする
          RMotor2 = 255;
        }
        if (LMotor2 < 0) {//値が負になっていたらゼロにしておく
          LMotor2 = 0;
        }
      }
    }
  }
  else if (value1 > 131) { //左スティックで前後方向に入力が無く、右スティックで右進が入っているとき
    RMotor2 = (value1 - 128) * 2; //右モータ逆転
    LMotor1 = (value1 - 128) * 2; //左モータ正転
  }
  else if (value1 < 124) { //左スティックで前後方向に入力が無く、右スティックで左進が入っているとき
    RMotor1 = 255 - value1 * 2; //右モータ正転
    LMotor2 = 255 - value1 * 2; //左モータ逆転
  }
  else{ //それ以外、すなわち、左スティック前後、右スティック左右に信号が無い場合
    RMotor1 = 0;
    RMotor2 = 0;
    LMotor1 = 0;
    LMotor2 = 0;
  }

  /*
  //なにはともあれ、信号レベルが低かったらゼロにしておく。
  if (RMotor1 < 30) {
    RMotor1 = 0;
  }
  if (RMotor2 < 30) {
    RMotor2 = 0;
  }
  if (LMotor1 < 30) {
    LMotor1 = 0;
  }
  if (LMotor2 < 30) {
    LMotor2 = 0;
  }
  */
}

