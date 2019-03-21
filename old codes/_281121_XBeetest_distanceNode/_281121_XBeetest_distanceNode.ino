#include <SoftwareSerial.h>
SoftwareSerial XBee_Node(8,9);

int val;

void setup() {
  XBee_Node.begin(9600);
  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(XBee_Node.available() > 0){
    val = XBee_Node.read();
    if(val  == 'H'){
      digitalWrite(2,HIGH);
    }
    else{
      digitalWrite(2,LOW);
    }
  }
  
  //digitalWrite(2,HIGH);
}
