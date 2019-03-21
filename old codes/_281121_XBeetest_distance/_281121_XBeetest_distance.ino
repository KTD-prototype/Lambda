#include <SoftwareSerial.h>
SoftwareSerial XBee_PC(8,9);

void setup() {
  XBee_PC.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  XBee_PC.write('H');
  delay(1000);
  XBee_PC.write('L');
  delay(1000);

}
