void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int d;
  d=analogRead(0);

  if(d>=500)
  {
     digitalWrite(13,HIGH);
     delay(1000);
     digitalWrite(13,LOW);
  }
}
