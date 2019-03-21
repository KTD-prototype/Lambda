#define analogPin 1
int val;
int threshold = 80;
int value = 0;
int range = 0;
int AD = 0;



void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}



void loop()
{
  if (Serial.available() > 0) //シリアルポートがデータを受信したら次へ
  {
    val = Serial.read();  //受信データを読み込んでその値をvalに代入
    if (val == 'A') //valがAならば次へ
    {
      digitalWrite(5, HIGH);  //ピン5にHIGHを出力
      digitalWrite(4, LOW); //ピン4にLOW出力　
      digitalWrite(3, HIGH);  //ピン３にHIGHを出力
      digitalWrite(2, LOW); //ピン２にLOW出力　クローラ前進
      
      delay(100); //タイマ0,1s
      
      digitalWrite(5, LOW); //
      digitalWrite(3, LOW); //停止


      
    }


    else if (val == 'B')
    {
      digitalWrite(5, LOW); //
      digitalWrite(4, HIGH);  //　
      digitalWrite(3, LOW); //
      digitalWrite(2, HIGH);  //クローラ後退

      delay(100); //タイマ0,1s

      digitalWrite(4, LOW); //
      digitalWrite(2, LOW); //停止
    }


    else if (val == 'C')
    {
      digitalWrite(5, HIGH);  //
      digitalWrite(4, LOW); //　
      digitalWrite(3, LOW); //
      digitalWrite(2, HIGH);  //クローラ右旋回

      delay(100); //タイマ0,1s

      digitalWrite(5, LOW); //
      digitalWrite(2, LOW); //停止
    }


    else if (val == 'D')
    {
      digitalWrite(5, LOW); //
      digitalWrite(4, HIGH);  //　
      digitalWrite(3, HIGH);  //
      digitalWrite(2, LOW); //クローラ左旋回

      delay(100); //タイマ0,1s

      digitalWrite(4, LOW); //
      digitalWrite(3, LOW); //停止
    }


    else if (val == 'E')
    {
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW); //可動クローラ持ち上げ
      delay(100);
      digitalWrite(7, LOW); //停止
    }


    else if (val == 'F')
    {
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);  //可動クローラおろし
      delay(100);
      digitalWrite(6, LOW); //停止
    }

    else if (val == 'G')
    {
      value = analogRead(analogPin);  //AD変換しデジタル値をvalueへ代入
      Serial.print("Distance= ");   //シリアル端末にDistance=と表示
      if (value > threshold)      //valueが閾値より大きければ
      {
        range = (6787 / (value - 3)) - 4; //デジタル値valueを距離に変換しrangeに代入
        Serial.print(range);
        Serial.println(" cm");
      }
      else
      {
        Serial.println("OFF");
        delay(300);
      }
        
        
    }
  }
 }


