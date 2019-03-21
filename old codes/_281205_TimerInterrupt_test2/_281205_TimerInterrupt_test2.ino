#include<MsTimer2.h>

void flash(){
  interrupts();
  static boolean output = HIGH;

  digitalWrite(13,output);
  output = !output;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);

  MsTimer2::set(500,flash);
  MsTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:

}
