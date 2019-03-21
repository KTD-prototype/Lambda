#include<Servo.h>
Servo servo0;

void setup() {
  // put your setup code here, to run once:
  servo0.attach(6);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo0.write(90);
  delay(1200);

  servo0.write(100);
  delay(50);

    servo0.write(110);
  delay(50);

      servo0.write(120);
  delay(50);
    servo0.write(130);
  delay(50);

    servo0.write(140);
  delay(50);

      servo0.write(150);
  delay(50);
    servo0.write(160);
  delay(50);

    servo0.write(170);
  delay(50);

      servo0.write(180);
  delay(50);

  
}
