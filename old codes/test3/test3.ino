void setup() //初期設定
{
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  }

void loop() //ループ
{
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  delay(2);

  digitalWrite(2,HIGH);
  delay(1);
}

