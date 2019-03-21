void mode_R(byte val1, byte val2, byte val3, byte val4) {
  Serial.print("mode : remote  ");
  analogWrite(5, val1);
  analogWrite(6, val2);
  analogWrite(10, val3);
  analogWrite(11, val4);
  Serial.print(val1);
  Serial.print("  ||  ");
  Serial.println(val2);
}

