#include<SoftwareSerial.h>
SoftwareSerial JOY_receive(8, 9);

int A = 0;
byte JOY[6] = {0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  JOY_receive.begin(9600);
  Serial.begin(9600);
}

void loop() {

  while (JOY_receive.available() <= 6) {
    delayMicroseconds(1);
    //Serial.println('A');
  }

  if (JOY_receive.available() > 6) {
    //Serial.println('C');
    if (JOY_receive.read() == 'H') {
      JOY[0] = JOY_receive.read();
      JOY[1] = JOY_receive.read();
      JOY[2] = JOY_receive.read();
      JOY[3] = JOY_receive.read();
      JOY[4] = JOY_receive.read();
      JOY[5] = JOY_receive.read();

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
      //JOY_receive.write('S');
    }
  }
}
