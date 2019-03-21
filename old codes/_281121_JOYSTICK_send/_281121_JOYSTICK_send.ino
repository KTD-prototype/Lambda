#include <SoftwareSerial.h>
SoftwareSerial JOY_send(8, 9);

int ansS = 0;
int RX, RY, LX, LY, RS, LS;

void setup() {
  // put your setup code here, to run once:
  JOY_send.begin(9600);
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  RX = analogRead(5);
  RY = analogRead(4);
  LX = analogRead(3);
  LY = analogRead(2);
  RS = analogRead(1);
  LS = analogRead(0);

  //delay(1000);
  Serial.println("test");

  
  while(ansS != 'A'){
    JOY_send.write('A');
    Serial.println("test1");
    delay(1);
    ansS = JOY_send.read();
  }
  JOY_send.write(RX);
  delay(1);
  Serial.println("test2");

  
  while(ansS != 'B'){
    Serial.println("test4");
    JOY_send.write('B');
    delay(1);
    ansS = JOY_send.read();
  }
  JOY_send.write(RY);
  delay(1);

  
  while(ansS != 'C'){
    JOY_send.write('C');
    delay(1);
    ansS = JOY_send.read();
  }
  JOY_send.write(RS);
  delay(1);

  
  while(ansS != 'D'){
    JOY_send.write('D');
    delay(1);
    ansS = JOY_send.read();
  }
  JOY_send.write(LX);
  delay(1);

  
  while(ansS != 'E'){
    JOY_send.write('E');
    delay(1);
    ansS = JOY_send.read();
  }
  JOY_send.write(LY);
  delay(1);

  
  while(ansS != 'F'){
    JOY_send.write('F');
    delay(1);
    ansS = JOY_send.read();
  }
  JOY_send.write(LS);
  delay(1);
  
  
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
  Serial.println(LS);
  
  delay(50);
}
