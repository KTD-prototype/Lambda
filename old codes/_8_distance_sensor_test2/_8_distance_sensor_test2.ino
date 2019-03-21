void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello!");
}

void loop() {
  // put your main code here, to run repeatedly:
  int d;
  d=analogRead(0);

  Serial.print("check=");
  Serial.println(d);
  delay(1000);
}
