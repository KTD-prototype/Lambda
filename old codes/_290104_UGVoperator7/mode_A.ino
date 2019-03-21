//http://kzmssk.blogspot.jp/2013/11/pyserialarduino-uno.html
//http://d.hatena.ne.jp/kougaku-navi/20140501/p1

void mode_A() { //自律走行モードの時、ラズパイから走行に必要な情報を取得し、それに基づきモータ駆動する関数
  JOY_receive.write(mode);
  if (Serial.available()) {
    int i = 0;
    while (1) {
      if (Serial.available()) {
        str[i] = Serial.read();
        if (str[i] == '=') {
          str[i + 1] = '\0';
          break;
        }
        else {
          i++;
        }
      }
    }
    sscanf(str, "%d, %d", &faceX, &faceY);
  }
  /*
    JOY_receive.write(mode);
    if (faceX > 255) {
    JOY_receive.write('H');
    JOY_receive.write(lowByte(faceX));
    JOY_receive.write(highByte(faceX));
    }
    else {
    JOY_receive.write('L');
    JOY_receive.write(faceX);
    }

    if (faceY > 255) {
    JOY_receive.write('H');
    JOY_receive.write(lowByte(faceY));
    JOY_receive.write(highByte(faceY));
    }
    else {
    JOY_receive.write('L');
    JOY_receive.write(faceY);
    }
  */
}

