#include <SoftwareSerial.h>
SoftwareSerial XBeeSerialCOM5(8,9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  XBeeSerialCOM5.begin(9600);
}

int a = 1024;

void loop() {
  // put your main code here, to run repeatedly:
  XBeeSerialCOM5.write(a);

  /*
  if(XBeeSerialCOM5.available()){
     Serial.println(XBeeSerialCOM5.read());
  }
  */
  //delay(1000);
}
