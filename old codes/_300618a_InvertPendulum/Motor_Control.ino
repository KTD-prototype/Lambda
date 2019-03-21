//pitchに応じたモータコントロールを実施する。


void motor_control(float angle) {

  //転倒判定（その時は直ちに関数を離脱）
  if (abs(angle) > 30) {
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(11, 0);
    analogWrite(13, 0);
    //Serial.println(angle);
    return;
  }

  else {//転倒判定がないとき、モータ制御を実施

    //pitch変数初期値がゼロだが、実態電源入れた時のピッチ角がゼロでないため、ここで積分項が増えてしまう。
    //また、この過程でpitch角度がちょうどいい値になってしまい、リセット時にモータが回ってしまう。
    //最初の10000ループ目までモータ制御しない、かつ最初の10000ループ目で積分項をリセットする。
    count++;
    if (count < 1000) {
      analogWrite(5, 0);
      analogWrite(6, 0);
      analogWrite(11, 0);
      analogWrite(13, 0);
      return;
    }
    else if (count == 1000) {
      integral_pitch_error = 0;
    }
    else {
      count = 10001;
    }


    //積分項の計算
    if (abs(target_pitch - angle) < 0.1) {//目標姿勢角との誤差が小さければ、積算誤差をリセット
      integral_pitch_error = 0;
    }
    else {//そうでなければ、積分用の誤差計算
      integral_pitch_error += (target_pitch - angle) / SAMPLINGRATE;
    }

    //微分項の計算
    //differential_pitch = (angle - preangle) * SAMPLINGRATE;
    //ここでやると、IMU値による更新以上のペースでpreangleを更新してしまい、角速度ゼロになってしまう。postureAngleの関数で計算する。
    //生データ（data[4]）よりも、相補フィルタしたあとのピッチ角から再計算した方がいいのでは、と思ったけど、そんなことなかった


    //制御目標（モータ指令値　0～255）
    vel = P * (target_pitch - angle) + D * data[4] + I * integral_pitch_error;

    //ずっと同じ方向に行かないようにする成分
    //これはただPゲインを増したのと同じ効果では？
    if (prevel > 0 && vel > 0 ) {
      vel += 1;
      //Serial.println(vel);
    }
    else if (prevel < 0 && vel < 0 ) {
      vel -= 1;
      //Serial.println(vel);
    }


    //ギアの抵抗等でモータが回らない領域を底上げ
    //ゼロ以外の出力なら、絶対値の最低値を10にする。
    if (vel > 0 && vel < FRICTION_COMPLEMENT) {
      vel = FRICTION_COMPLEMENT;
    }
    else if (vel < 0 && vel > -1 * FRICTION_COMPLEMENT) {
      vel = FRICTION_COMPLEMENT;
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

    //Serial.print(data[4]);
    //Serial.print(",");
    //Serial.println(differential_pitch);
  }
}
