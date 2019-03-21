#include <SoftwareSerial.h>
SoftwareSerial XBeeSerialCOM9(8,9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  XBeeSerialCOM9.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  //XBeeSerialCOM9.write("test B");

  if(XBeeSerialCOM9.available() > 0){
     int a = XBeeSerialCOM9.read();
     Serial.println(a, HEX);
  }
  delay(1000);
}
