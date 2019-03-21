#include <SoftwareSerial.h>
SoftwareSerial JOY_send(8, 9);

int A = 0;
int RX, RY, LX, LY, RS, LS;

void setup() {
  // put your setup code here, to run once:
  JOY_send.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  RX = analogRead(5);
  RY = analogRead(4);
  LX = analogRead(3);
  LY = analogRead(2);
  RS = analogRead(1);
  LS = analogRead(0);

  
  while (A != 'F') {
    A = JOY_send.read();
    Serial.println('H');
  }
  sendIntDataRX(RX);
  A = JOY_send.read();
  Serial.println('L');


  while (A != 'A') {
    A = JOY_send.read();
    Serial.println('M');
  }
  sendIntDataRY(RY);
  A = JOY_send.read();
  Serial.println('O');

  while (A != 'B') {
    A = JOY_send.read();
  }
  sendIntDataRS(RS);
  A = JOY_send.read();

  while (A != 'C') {
    A = JOY_send.read();
  }
  sendIntDataLX(LX);
  A = JOY_send.read();

  while (A != 'D') {
    A = JOY_send.read();
  }
  sendIntDataLY(LY);
  A = JOY_send.read();

  while (A != 'E') {
    A = JOY_send.read();
  }
  sendIntDataLS(LS);
  A = JOY_send.read();



/*
  A++;
  Serial.print(RX);

  Serial.print(" || ");
  Serial.print(RY);
  Serial.print(" || ");
  Serial.print(LX);
  Serial.print(" || ");
  Serial.print(LY);
  Serial.print(" || ");
  Serial.print(RS);
  Serial.print(" || ");
  Serial.print(LS);

  Serial.println("");
  */

  //delay(50);

}


void sendIntDataRX(int value) {
  JOY_send.write('A');
  JOY_send.write(lowByte(value));
  JOY_send.write(highByte(value));
}


void sendIntDataRY(int value) {
  JOY_send.write('B');
  JOY_send.write(lowByte(value));
  JOY_send.write(highByte(value));
}


void sendIntDataRS(int value) {
  JOY_send.write('C');
  JOY_send.write(lowByte(value));
  JOY_send.write(highByte(value));
}


void sendIntDataLX(int value) {
  JOY_send.write('D');
  JOY_send.write(lowByte(value));
  JOY_send.write(highByte(value));
}


void sendIntDataLY(int value) {
  JOY_send.write('E');
  JOY_send.write(lowByte(value));
  JOY_send.write(highByte(value));
}


void sendIntDataLS(int value) {
  JOY_send.write('F');
  JOY_send.write(lowByte(value));
  JOY_send.write(highByte(value));
}
