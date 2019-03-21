#include<SoftwareSerial.h>
SoftwareSerial JOY_receive(8, 9);

int ansR = 0;
int RX, RY, RS, LX, LY, LS;
byte data;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  JOY_receive.begin(9600);
  Serial.begin(9600);
}

void loop() {

  if (JOY_receive.available() > 12) {
    if (JOY_receive.read() == 'H') {
      int RXlow = JOY_receive.read();
      delay(10);
      int RXhigh = JOY_receive.read();
      delay(10);

      int RYlow = JOY_receive.read();
      delay(10);
      int RYhigh = JOY_receive.read();
      delay(10);

      int RSlow = JOY_receive.read();
      delay(10);
      int RShigh = JOY_receive.read();
      delay(10);

      int LXlow = JOY_receive.read();
      delay(10);
      int LXhigh = JOY_receive.read();
      delay(10);

      int LYlow = JOY_receive.read();
      delay(10);
      int LYhigh = JOY_receive.read();
      delay(10);

      int LSlow = JOY_receive.read();
      delay(10);
      int LShigh = JOY_receive.read();
      delay(10);

      RX = makeWord(RXhigh, RXlow);
      RY = makeWord(RYhigh, RYlow);
      RS = makeWord(RShigh, RSlow);
      LX = makeWord(LXhigh, LXlow);
      LY = makeWord(LYhigh, LYlow);
      LS = makeWord(LShigh, LSlow);

      Serial.print(RX);
      Serial.print(" || ");
      Serial.print(RY);
      Serial.print(" || ");
      Serial.print(RS);
      Serial.print(" || ");
      Serial.print(LX);
      Serial.print(" || ");
      Serial.print(LY);
      Serial.print(" || ");
      Serial.print(LS);
      Serial.println("");


    }
  }

  JOY_receive.write('S');
}
