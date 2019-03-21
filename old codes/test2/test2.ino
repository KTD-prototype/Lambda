void setup() //初期設定
{
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  }

void loop() //ループ
{
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  delay(1000);

  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  delay(1000);
}

