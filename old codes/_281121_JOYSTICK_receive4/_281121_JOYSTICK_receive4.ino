#include<SoftwareSerial.h>
SoftwareSerial JOY_receive(8, 9);

int ansR = 0;
int RX, RY, RS, LX, LY, LS;
byte data;
int JOY[6] = {0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  JOY_receive.begin(9600);
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 6; i++) {
    JOY_receive.write(i);
    delay(100);
    if (JOY_receive.available() >= 3) {
      if (JOY_receive.read() == 'H') {
        int low = JOY_receive.read();
        int high = JOY_receive.read();
        JOY[i] = makeWord(high, low);
      }
    }
  }



  Serial.print(JOY[0]);
  Serial.print(" || ");
  Serial.print(JOY[1]);
  Serial.print(" || ");
  Serial.print(JOY[4]);
  Serial.print(" || ");
  Serial.print(JOY[2]);
  Serial.print(" || ");
  Serial.print(JOY[3]);
  Serial.print(" || ");
  Serial.print(JOY[5]);
  Serial.println("");

}
