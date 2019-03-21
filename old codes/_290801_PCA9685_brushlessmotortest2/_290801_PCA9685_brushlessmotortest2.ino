/* refered http://www.isopro91.com/entry/2014/10/21/arduino/servo/robot
//        _281116_MPU9250_PCA9685_Angle_Revice
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN 810
#define SERVOMAX 1610

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void servo_write(int n, int ang) {
  ang = map(ang, 0, 255, SERVOMIN, SERVOMAX);
  pwm.setPWM(n, 0, ang);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(200);// アナログサーボが60Hzで動く
  
  servo_write(15, 255);
  delay(5000);
  servo_write(15,0);
  delay(3000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int m=0; m<255; m++){
    servo_write(15,m);
    delay(100);
    Serial.println(m);
  }
}
