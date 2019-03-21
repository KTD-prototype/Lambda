/*最初に右がついたか左がついたかによって、右手の法則or左手の法則で
 *台の縁をぐるぐる回り続けるロボット
 */
  
  #define PBS1 9 //置き換えPBS1→8
  #define PBS2 8
  #define analogPin0 0
  #define analogPin1 1
  int valueL=0;
  int valueR=0;
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

      
      valueR=analogRead(analogPin0);//AD変換して右センサの値をvalueLeftへ
      valueL=analogRead(analogPin1);//AD変換して左センサの値をvalueRightへ

//左手の法則モード
      if(valueL<=409)//左が反応
      {
        while(valueR<=409)//右も反応
        {
         PORTD=0x18;//右旋回しつづける 
         break;
        }

       //左が無反応になるまで、ちょっとずつ右前に進む
       while(valueL<=409)
       {
        PORTD=0x28;//直進
        delay(200);
        PORTD=0x18;//右旋回
        delay(200);
        break;
       }

       //左が反応するまでちょっとずつ左前に進む
       while(valueL>409)
       {
       PORTD=0x28;//直進
       delay(200);
       PORTD=0x24;//左旋回
       delay(200);
       break;
       }
      break;
      }


//右手の法則モード
      if(valueR<=409)//右が反応
      {
        while(valueL<=409)//左も反応
        {
         PORTD=0x24;//左旋回しつづける 
         break;
        }

       //右が無反応になるまで、ちょっとずつ左前に進む
       while(valueR<=409)
       {
        PORTD=0x28;//直進
        delay(200);
        PORTD=0x24;//左旋回
        delay(200);
        break;
       }

       //右が反応するまでちょっとずつ右前に進む
       while(valueR>409)
       {
       PORTD=0x28;//直進
       delay(200);
       PORTD=0x18;//右旋回
       delay(200);
       break;
       }
      break;
      }


    }
  }
}





/*
void loop() {
  // put your main code here, to run repeatedly:
  s1=digitalRead(PBS1); 
  if(s1==0) //PBS1がＯＮならば、次へ
  {
    while(1)
    {
       PORTD=0x24;//左旋回
       delay(200);
       PORTD=0x28;//ロボット前進
       delay(200);
       
      s2=digitalRead(PBS2);
      if(s2==0)//PBS2がＯＮならば、次へ行く
      {
        PORTD=0x3c;
        break;//ブレーキして、ループを脱出
      }
      
      valueL=analogRead(analogPin0);//AD変換して右センサの値をvalueleftへ
      valueR=analogRead(analogPin1);//AD変換して左センサの値をvaluerightへ
      
      if(valueL<=409&&valueR>409)//左飛び出しそう、右大丈夫のとき
      {
       PORTD=0x18;//右旋回
       delay(200);
       PORTD=0x28;//ロボット前進
       delay(200);
      }

      else
      {
       break;
      }
    }

      
      
        
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
}*/
