#include <SoftwareSerial.h>
SoftwareSerial JOY_send(8, 9);

int A = 0;
int JOY[6] = {0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  JOY_send.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  JOY[0] = analogRead(5);//RX
  JOY[1] = analogRead(4);//RY
  JOY[2] = analogRead(3);//LX
  JOY[3] = analogRead(2);//LY
  JOY[4] = analogRead(1);//RS
  JOY[5] = analogRead(0);//LS

  for (int i = 0; i < 6; i++) {
    while (i != A) {
      A = JOY_send.read();
    }
    sendIntData(JOY[i]);
  }
}

void sendIntData(int value) {
  JOY_send.write('H');
  JOY_send.write(lowByte(value));
  JOY_send.write(highByte(value));
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
