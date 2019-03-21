void setup() //初期設定
{
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  }

void loop() //ループ
{
  //モーター右回転
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  delay(1000);

  //ストップ
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  delay(1000);

  //モーター左回転
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  delay(1000);

  //ブレーキ
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  delay(5000);

}

