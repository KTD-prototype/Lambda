void setup() {
  // put your setup code here, to run once:
  DDRD=B11111100;
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTD=B10000000;
  delay(1000);

  PORTD=B01000000;
  delay(1000);

  PORTD=B00100000;
  delay(1000);

  PORTD=B00010000;
  delay(1000);

  PORTD=B00001000;
  delay(1000);

  PORTD=B00000100;
  delay(1000);
}
