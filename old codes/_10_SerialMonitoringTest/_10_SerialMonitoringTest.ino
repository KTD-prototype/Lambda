
void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("Hello.");
}


void loop()
{
  if (Serial.available() > 0)
  {
    int i, val;
    val = Serial.read();
    if (val == 's')
    {
      PP();
      PP();
      PP();
      Serial.println("OK,Signal===>S");
    }

    if (val == 'o')
    {
      QQ();
      QQ();
      QQ();
      Serial.println("OK,Signal===>0");
    }
  }
}


void PP()
{
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(400);
}


void QQ()
{
  digitalWrite(13, HIGH);
  delay(400);
  digitalWrite(13, LOW);
  delay(100);
}

