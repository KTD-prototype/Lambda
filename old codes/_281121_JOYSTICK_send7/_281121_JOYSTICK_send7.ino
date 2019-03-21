#include <SoftwareSerial.h>
SoftwareSerial JOY_send(8, 9);

byte JOY[6] = {0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  JOY_send.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  JOY[0] = analogRead(5) / 4;//RX
  JOY[1] = analogRead(4) / 4;//RY
  JOY[2] = analogRead(1) / 4;//RS
  JOY[3] = analogRead(3) / 4;//LX
  JOY[4] = analogRead(2) / 4;//LY
  JOY[5] = analogRead(0) / 4;//LS
  sendIntData(JOY[0], JOY[1], JOY[2], JOY[3], JOY[4], JOY[5]);
}

void sendIntData(int value1, int value2, int value3, int value4, int value5, int value6) {
  JOY_send.write('H');
  JOY_send.write(value1);
  JOY_send.write(value2);
  JOY_send.write(value3);
  JOY_send.write(value4);
  JOY_send.write(value5);
  JOY_send.write(value6);
}

