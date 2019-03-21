#include <SoftwareSerial.h>
SoftwareSerial JOY_send(8, 9);

int A = 0;
int JOY[6] = {0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  JOY_send.begin(4800);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:



  if (JOY_send.read() == 'S') {
    JOY[0] = analogRead(5);//RX
    JOY[1] = analogRead(4);//RY
    JOY[2] = analogRead(1);//RS
    JOY[3] = analogRead(3);//LX
    JOY[4] = analogRead(2);//LY
    JOY[5] = analogRead(0);//LS
    sendIntData(JOY[0], JOY[1], JOY[2], JOY[3], JOY[4], JOY[5]);
    
  }

}

void sendIntData(int value1, int value2, int value3, int value4, int value5, int value6) {
  JOY_send.write('H');
  JOY_send.write(lowByte(value1));
  JOY_send.write(highByte(value1));
  JOY_send.write(lowByte(value2));
  JOY_send.write(highByte(value2));
  JOY_send.write(lowByte(value3));
  JOY_send.write(highByte(value3));
  JOY_send.write(lowByte(value4));
  JOY_send.write(highByte(value4));
  JOY_send.write(lowByte(value5));
  JOY_send.write(highByte(value5));
  JOY_send.write(lowByte(value6));
  JOY_send.write(highByte(value6));
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
