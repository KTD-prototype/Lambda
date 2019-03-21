#include<Servo.h>
Servo servo0;

void setup() {
  // put your setup code here, to run once:
  servo0.attach(6);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo0.write(90);
  delay(2000);


  
  
}
