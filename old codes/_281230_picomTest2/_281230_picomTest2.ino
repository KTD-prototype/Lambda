#include <I2CLiquidCrystal.h>
#include <Wire.h>

I2CLiquidCrystal lcd(0x3c, (uint8_t)255);

byte faceX = ';', faceY = '@';
int X = 0, Y = 0;
byte str[20];
int Face[20];

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    int i = 0;
    while (1) {
      if (Serial.available()) {
        str[i] = Serial.read();
        //sscanf(str[i], "%d", &Face[i]);
        if (str[i] == '=') {
          str[i + 1] = '\0';
          break;
        }
        else {
          i++;
        }
      }
    }
    sscanf(str, "%d, %d", &X, &Y);
    //X = int(X);
    //Y = int(Y);
    lcd.setCursor(0, 0);
    lcd.println(X, DEC);
    lcd.setCursor(0, 1);
    lcd.println(Y, DEC);
  }
}
