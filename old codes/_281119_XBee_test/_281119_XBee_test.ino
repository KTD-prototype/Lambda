#include <SoftwareSerial.h>
SoftwareSerial XBeeSerial(8,9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  XBeeSerial.begin(115200);
}

int a = 0xFF;
int c = 100;

void loop() {
  // put your main code here, to run repeatedly:
  XBeeSerial.write(c);
  //c = XBeeSerial.read();
  if(XBeeSerial.available()){
     Serial.println(c,HEX);
  }
  delay(1000);
}
