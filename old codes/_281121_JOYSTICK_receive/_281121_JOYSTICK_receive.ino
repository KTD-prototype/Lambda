#include<SoftwareSerial.h>
SoftwareSerial JOY_receive(8, 9);

int ansR = 0;
int RX, RY, RS, LX, LY, LS;

void setup() {
  // put your setup code here, to run once:
  JOY_receive.begin(9600);
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(JOY_receive.available() > 0){
    while(ansR != 'A'){
      Serial.println("test1");
      delay(1);
      ansR = JOY_receive.read();
    }
    JOY_receive.write('A');
    delay(1);
    RX = JOY_receive.read();


    while(ansR != 'B'){
      delay(1);
      ansR = JOY_receive.read();
    }
    JOY_receive.write('B');
    delay(1);
    RY = JOY_receive.read();


    while(ansR != 'C'){
      delay(1);
      ansR = JOY_receive.read();
    }
    JOY_receive.write('C');
    delay(1);
    RS = JOY_receive.read();

    while(ansR != 'D'){
      delay(1);
      ansR = JOY_receive.read();
    }
    JOY_receive.write('D');
    delay(1);
    LX = JOY_receive.read();

    while(ansR != 'E'){
      delay(1);
      ansR = JOY_receive.read();
    }
    JOY_receive.write('E');
    delay(1);
    LY = JOY_receive.read();

    while(ansR != 'F'){
      delay(1);
      ansR = JOY_receive.read();
    }
    JOY_receive.write('F');
    delay(1);
    LS = JOY_receive.read();
  }
  
  else{
    RX = 0;
    RY = 0;
    RS = 0;
    LX = 0;
    LY = 0;
    LS = 0;
  }
  

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
  
}
