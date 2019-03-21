void ChangeMode() {
  if (RS == 0 && LS == 0 && mode == 0) {
    mode = 1;
    delay(1000);
  }
  else if (RS == 0 && LS == 0 && mode == 1) {
    mode = 2;
    delay(1000);
  }
  else if (RS == 0 && LS == 0 && mode == 2) {
    mode = 0;
    delay(1000);
  }
}

