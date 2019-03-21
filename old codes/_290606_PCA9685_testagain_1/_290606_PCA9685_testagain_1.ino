/* refered http://www.isopro91.com/entry/2014/10/21/arduino/servo/robot
//        _281116_MPU9250_PCA9685_Angle_Revice
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN 150
#define SERVOMAX 390

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void servo_write(int n, int ang) {
  ang = map(ang, 0, 360, SERVOMIN, SERVOMAX);
  pwm.setPWM(n, 0, ang);
}

void setup() {
  // put your setup code here, to run once:
  pwm.begin();
  pwm.setPWMFreq(60);// アナログサーボが60Hzで動く
  servo_write(15, 90);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  servo_write(15, 0);
  delay(5000);
  servo_write(15, 90);
  delay(2500);
  servo_write(15, 180);
  delay(2500);
  servo_write(15, 270);
  delay(2500);
  servo_write(15, 350);
  delay(2500);
  servo_write(15, 360);
  delay(2500);
 
}
