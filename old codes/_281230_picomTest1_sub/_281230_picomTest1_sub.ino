#include <I2CLiquidCrystal.h>
#include <Wire.h>

I2CLiquidCrystal lcd(0x3c, (uint8_t)255);

byte X = 200;
int Y;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  Y = int(X);
  Serial.println(Y);
  lcd.setCursor(0, 0);
  lcd.println(Y);
}
