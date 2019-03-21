#define PBS1 2
#define PBS2 3
#define PBS3 4
#define PBS4 5
#define Buzzer 8
int val;
void setup()
{
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(Buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0) //シリアルポートがデータを受信したら次へ
  {
    val = Serial.read();  //受信データを読み込んでvalへ格納
    if (val == 'H') //valがHighなら次へ
    {
      digitalWrite(Buzzer, HIGH); //BuzzerにHigh出力、ブザーが鳴る
      delay(2000);
      digitalWrite(Buzzer, LOW);  //Buzzerが鳴りやむ
      delay(20);
    }
  }

  int s1 = digitalRead(PBS1); //PBS1の値を読み取ってｓ１に代入
  int s2 = digitalRead(PBS2);
  int s3 = digitalRead(PBS3);
  int s4 = digitalRead(PBS4);

  if (s1 == 0 && s2 == 0) //1がONかつ2もON
  {
    Serial.print('A');  //シリアルポートへAを送信
    delay(100); //タイマ0.1s
  }

  else if (s3 == 0 && s4 == 0)
  {
    Serial.print('B');  //シリアルポートへBを送信
    delay(100); //タイマ０．１ｓ
  }

  else if (s2 == 0 && s3 == 0)
  {
    Serial.print('C');  //シリアルポートへCを送信
    delay(100); //タイマ０．１ｓ
  }

  else if (s1 == 0 && s4 == 0)
  {
    Serial.print('D');  //シリアルポートへDを送信
    delay(100); //タイマ０．１ｓ
  }

  else if (s1 == 0 && s3 == 0)
  {
    Serial.print('E');  //シリアルポートへEを送信
    delay(100); //タイマ０．１ｓ
  }

  else if (s2 == 0 && s4 == 0)
  {
    Serial.print('F');  //シリアルポートへFを送信
    delay(100); //タイマ０．１ｓ
  }
}
