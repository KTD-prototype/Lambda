void takeoff() {
  FlightMode = 1;
}

void fly() {
  M1 = 810, M2 = 810, M3 = 810, M4 = 810;

  M1 = pitch * 10 + roll * 10 + yaw * 10;
  M2 = pitch * 10 - roll * 10 - yaw * 10;
  M3 = roll * 10 - pitch * 10 - yaw * 10;
  M4 = roll * 10 - pitch * 10 + yaw * 10;

  M1 = M1 - (Elevator - 130) + (Aileron - 125) + (Throttle - 128) + (Rudder - 128);
  M2 = M2 - (Elevator - 130) - (Aileron - 125) + (Throttle - 128) - (Rudder - 128);
  M3 = M3 + (Elevator - 130) + (Aileron - 125) + (Throttle - 128) - (Rudder - 128);
  M4 = M4 + (Elevator - 130) - (Aileron - 125) + (Throttle - 128) + (Rudder - 128);
}

void landing() {

}

void FlightMode_R(byte val1, byte val2, byte val3, byte val4) { //1:Elevator, 2:Aileron, 3:Throttle, 4:Rudder



}


void Prop(byte val0, byte val1, byte val2, byte val3) { //1:M1, M2, 3:M3, M4
  pwm.setPWM(0, 0, val0);
  pwm.setPWM(1, 0, val1);
  pwm.setPWM(2, 0, val2);
  pwm.setPWM(3, 0, val3);
}
