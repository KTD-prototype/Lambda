void mode_R(byte val1, byte val2, byte val3, byte val4) {
  JOY_receive.write(mode);
  val1 = val1 * 0.5;
  val2 = val2 * 0.5;
  val3 = val3 * 0.5;
  val4 = val4 * 0.5;
  analogWrite(5, val1);
  analogWrite(6, val2);
  analogWrite(11, val3);
  analogWrite(13, val4);
  /*
    Serial.print(val1);
    Serial.print("  ||  ");
    Serial.println(val2);
  */
}

