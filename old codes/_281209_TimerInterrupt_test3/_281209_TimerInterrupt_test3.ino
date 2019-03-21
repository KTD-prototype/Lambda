#include<TimerOne.h>
#include<Wire.h>

void flash(){
  interrupts();
  static boolean output = HIGH;

  digitalWrite(13,output);
  output = !output;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);

  Wire.begin();

  Timer1.initialize(500000);
  Timer1.attachInterrupt(flash);
  interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:

}
