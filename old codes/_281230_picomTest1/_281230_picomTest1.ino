#include <I2CLiquidCrystal.h>
#include <Wire.h>

I2CLiquidCrystal lcd(0x3c, (uint8_t)255);

byte faceX = ';', faceY = '@';
int X = 0, Y = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 1) {
    faceX = Serial.read();
    //faceX = int(faceX - 0x30);
    //faceX = int(faceX) * 3;
    faceY = Serial.read();
    //faceY = int(faceY - 0x30);
    //faceY = int(faceY) * 3;
    //X = int(faceX);
    //Y = int(faceY);
  }
  //Serial.println(faceX);
  lcd.setCursor(0, 0);
  lcd.println(faceX, DEC);
  lcd.setCursor(0, 1);
  lcd.println(faceY, DEC);
  //delay(1000);
}
