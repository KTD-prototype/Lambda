void ChangeMode() {
  if (RS == 0 && LS == 0 && ControlMode == 0) {
    ControlMode = 1;
    delay(1000);
  }
  else if (RS == 0 && LS == 0 && ControlMode == 1) {
    ControlMode = 2;
    delay(1000);
  }
  else if (RS == 0 && LS == 0 && ControlMode == 2) {
    ControlMode = 3;
    delay(1000);
  }
  else if (RS == 0 && LS == 0 && ControlMode == 3) {
    ControlMode = 0;
    delay(1000);
  }
}

