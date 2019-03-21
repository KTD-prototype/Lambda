void setup() //初期設定
{
  pinMode(9,OUTPUT);
  }

void loop() //ループ
{
  int i=0;
  for(i=0;i<=254,i=i+1;)
    {
      analogWrite(9,i);
      delay(10);
    }

  for(i=0;i<=254,i=i+1;)
    {
      analogWrite(9,255-i);
      delay(10);
    }

}

