
//pitchに応じたモータコントロールを実施する。
//pitch方向角速度はdata[4]に格納されているのでこれを使う。angleは引数で、関数呼び出し時はピッチ角が入る。
void motor_control(float angle) {

  //制御目標（モータ指令値　0～255）
  vel = P * (target_pitch - angle) + D * data[4] + I * integral_pitch_error;

  //ずっと同じ方向に行かないようにする成分
  //これはただPゲインを増したのと同じ効果では？
  if (prevel > 0 && vel > 0 ) {
    vel += 1;
    Serial.println(vel);
  }
  else if (prevel < 0 && vel < 0 ) {
    vel -= 1;
    Serial.println(vel);
  }


  //ギアの抵抗等でモータが回らない領域を底上げ
  if (vel > 0) {
    vel += 5;
  }
  else if (vel < 0) {
    vel -= 5;
  }

  //絶対値がアナログ出力Duty比の最大値255を超えていたら255に合わせる。
  if (vel > 255) {
    vel = 255;
  }
  else if (vel < -255) {
    vel = -255;
  }

  //モータドライバへの指令値を入力
  if (vel >= 0) {
    val1 = vel;
    val2 = 0;
    val3 = val1;
    val4 = 0;
  }
  else {
    val1 = 0;
    val2 = -1 * vel;
    val3 = 0;
    val4 = val2;
  }

  //転倒判定（その時は誤差積算せず、それ以外で実施）
  //姿勢角が目標角に近づいた時も、誤差積算リセット
  if (abs(angle) > 30) {
    val1 = val2 = val3 = val4 = 0;
  }
  else if (abs(target_pitch - angle) < 0.1) {
    integral_pitch_error = 0;
  }
  else {
    //積分用の誤差計算
    integral_pitch_error += (target_pitch - angle) / SAMPLINGRATE;
  }

  //yaw角補正
  if (yaw > 15) {
    val1 += 3;
    val3 -= 3;
  }
  else if (yaw < -15) {
    val2 += 3;
    val4 -= 3;
  }

  //前の速度を保存
  prevel = vel;

  //モータコントローラへPWMで速度指令値送信
  analogWrite(5, val1);
  analogWrite(6, val2);
  analogWrite(11, val3);
  analogWrite(13, val4);
}
