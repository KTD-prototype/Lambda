#include<SoftwareSerial.h>
SoftwareSerial JOY_receive(8, 9);

int A = 0;
int RX, RY, RS, LX, LY, LS;
byte data;
int JOY[6] = {0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  JOY_receive.begin(4800);
  Serial.begin(9600);
}

void loop() {
  JOY_receive.write('S');
  if (JOY_receive.available() > 12) {
    if (JOY_receive.read() == 'H') {
      int lowRX = JOY_receive.read();
      int highRX = JOY_receive.read();
      int lowRY = JOY_receive.read();
      int highRY = JOY_receive.read();
      int lowRS = JOY_receive.read();
      int highRS = JOY_receive.read();
      int lowLX = JOY_receive.read();
      int highLX = JOY_receive.read();
      int lowLY = JOY_receive.read();
      int highLY = JOY_receive.read();
      int lowLS = JOY_receive.read();
      int highLS = JOY_receive.read();
      JOY[0] = makeWord(highRX, lowRX);
      JOY[1] = makeWord(highRY, lowRY);
      JOY[2] = makeWord(highRS, lowRS);
      JOY[3] = makeWord(highLX, lowLX);
      JOY[4] = makeWord(highLY, lowLY);
      JOY[5] = makeWord(highLS, lowLS);

      Serial.print(JOY[0]);

      Serial.print(" || ");
      Serial.print(JOY[1]);
      Serial.print(" || ");
      Serial.print(JOY[2]);
      Serial.print(" || ");
      Serial.print(JOY[3]);
      Serial.print(" || ");
      Serial.print(JOY[4]);
      Serial.print(" || ");
      Serial.print(JOY[5]);

      Serial.println("");

    }
  }

}
