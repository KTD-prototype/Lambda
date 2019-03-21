void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  
}


void loop()
{
  move_GO(5000);
  move_BACK(5000);
  turn_RIGHT(3000);
  turn_LEFT(3000);
}


void move_GO(int ms)
{
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(2,LOW);
  delay(ms); 
}

void move_BACK(int ms)
{
  digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  delay(ms);  
}

void turn_RIGHT(int ms)
{
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  delay(ms);  
}

void turn_LEFT(int ms)
{
  digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(2,LOW);
  delay(ms);  
}

/*
void loop() {
  // put your main code here, to run repeatedly:
  while(1)
  {
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(2,LOW);
  delay(5000);

  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  delay(3000);

  digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  delay(5000);

  digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(2,LOW);
  delay(3000);
  }
}*/
