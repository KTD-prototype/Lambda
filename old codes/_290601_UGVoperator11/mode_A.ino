byte faceX = ';', faceY = '@';
byte str[20];
int Face[20];
int X = 0, Y = 0;

void mode_A() {
  if (Serial.available()) {
    int i = 0;
    while (1) {
      if (Serial.available()) {
        str[i] = Serial.read();
        if (str[i] == '=') {
          str[i + 1] = '\0';
          break;
        }
        else i++; {

        }
      }
    }
    sscanf(str, "%d,%d", &X, &Y);
  }
}

