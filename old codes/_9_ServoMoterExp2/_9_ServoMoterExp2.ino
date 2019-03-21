#include<Servo.h>
Servo servo0;


void setup() {
  // put your setup code here, to run once:
  servo0.attach(7);
}

void loop() {
  // put your main code here, to run repeatedly:

    servo0.write(0);
    delay(600);

    servo0.write(90);
    delay(600);

    servo0.write(0);
    delay(600);

    servo0.write(90);
    delay(600);

        servo0.write(0);
    delay(600);

    servo0.write(90);
    delay(600);



  
}
