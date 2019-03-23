void print_time() {
  present_time = micros();
  passed_time = present_time - previous_time;
  Serial.println(passed_time);
  previous_time = present_time;
}
