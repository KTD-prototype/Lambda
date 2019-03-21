  #define PBS1 9 //置き換えPBS1→8
  #define PBS2 8
  #define analogPin0 0
  #define analogPin1 1
  int value0=0;
  int value1=0;
  int s1,s2;


void setup() {
  // put your setup code here, to run once:
  pinMode(PBS1,INPUT);
  pinMode(PBS2,INPUT);
  DDRD=B11111100;
    
}

void loop() {
  // put your main code here, to run repeatedly:
  s1=digitalRead(PBS1); 
  if(s1==0) //PBS1がＯＮならば、次へ
  {
    while(1)
    {
      PORTD=0x28;//ロボット前進
      s2=digitalRead(PBS2);
      if(s2==0)//PBS2がＯＮならば、次へ行く
      {
        PORTD=0x3c;
        break;//ブレーキして、ループを脱出
      }
      value0=analogRead(analogPin0);//AD変換して右センサの値をvalue0へ
      value1=analogRead(analogPin1);//AD変換して左センサの値をvalue0へ
      
      if(value0<=409)//右センサの出力値が１２ｃｍ以上（右側が壁から飛び出しそう）の時
      {
        PORTD=0x3c;//ブレーキ
        delay(1000);
        PORTD=0x14; //後進
        delay(1000);
        PORTD=0x24;//左旋回
        s2=digitalRead(PBS2);
        if(s2==0) //PBS2がＯＮならば次へ行く
        {
          PORTD=0x3c;
          break;//ブレーキをかけて、ループ脱出
        }
        delay(1000);
        
      }
      else if(value1<=409)//左センサの出力値が１２ｃｍ以上（右側が壁から飛び出しそう）の時
      {
        PORTD=0x3c;//ブレーキ
        delay(1000);
        PORTD=0x14;//後進
        delay(1000);
        PORTD=0x18;//右旋回
        s2=digitalRead(PBS2);
        if(s2==0)
        {
          PORTD=0x3c;//ブレーキ
          break;
        }
        delay(1000);
      }
    }
  }
}
