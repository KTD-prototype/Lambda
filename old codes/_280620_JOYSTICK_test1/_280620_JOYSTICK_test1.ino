int val1=0,val2=0,valx1=0,valy1=0,valx2=0,valy2=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  valx1=analogRead(0);
  valy1=analogRead(1);
  valx2=analogRead(2);
  valy2=analogRead(3);
  val1=analogRead(4);
  val2=analogRead(5);

  Serial.print(valx1);
  Serial.print("\t"); 
  Serial.print(valy1);
  Serial.print("\t"); 
  Serial.print(valx2);
  Serial.print("\t"); 
  Serial.print(valy2);
  Serial.print("\t"); 
  Serial.print(val1);
  Serial.print("\t"); 
  Serial.print(val2);
  Serial.println("");
  
  delay(500);
}
