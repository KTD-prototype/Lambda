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
  C:
  s1=digitalRead(PBS1); 
  if(s1==0) //PBS1がＯＮならば、次へ
  {
    while(1)
    {
      PORTD=0x28;//ロボット前進
      delay(1000);
      PORTD=0x3c;//ブレーキ
      delay(1000);

      s2=digitalRead(PBS2);
      if(s2==0)//PBS2がＯＮならば、次へ行く
      {
        PORTD=0x3c;
        break;//ブレーキして、ループを脱出
      }

      
      valueR=analogRead(analogPin0);//AD変換して右センサの値をvalueLeftへ
      valueL=analogRead(analogPin1);//AD変換して左センサの値をvalueRightへ


      if(valueL<=409&&valueR>409)goto A;//左センサ12cm以上、右は以下  
      else if(valueL>409&&valueR<=409)goto B;//左は以下、右は以上
      else if(valueL<=409&&valueR<=409)
      {
        PORTD=0x14; //2s後進
        delay(2000);
        PORTD=0x18;//1s間右旋回
        delay(2000);
      }
    }
  }
  goto C;


      
A://左手の法則モード
B:
   
while(1)
{
      valueR=analogRead(analogPin0);//AD変換して右センサの値をvalueLeftへ
      valueL=analogRead(analogPin1);//AD変換して左センサの値をvalueRightへ
      
        if(valueR<=409)//もし右センサも12以上のとき
        {
         PORTD=0x14; //500ms後進
         delay(1000);       
         PORTD=0x18;//500ms間右旋回
         delay(1000);
         PORTD=0x3c;//ブレーキ
         delay(1000);
        }
                
             
        else if(valueR>409&&valueL<=409)//右センサは12以下だけど左は12以上の時
        {//ちょっと右前へ進む
         PORTD=0x14; //1s後進
         delay(1000);       
         PORTD=0x18;//右旋回
         delay(1000);
         PORTD=0x28;//直進
         delay(1000);
         PORTD=0x3c;//ブレーキ
         delay(1000);
        }

       
        else if(valueL>409)//左がそもそも12以下のとき
        {//ちょっと左前へ進む
         PORTD=0x28;//直進
         delay(1000);
         PORTD=0x24;//左旋回
         delay(700);
         PORTD=0x3c;//ブレーキ
         delay(1000);
        }
      

      s2=digitalRead(PBS2);
      if(s2==0)//PBS2がＯＮならば、次へ行く
      {
        PORTD=0x3c;
        break; //ブレーキして、ループを脱出
      }
       }
  }


  
  

    


/*右手の法則モード
B:
      while(valueR<=409)//右が反応
      {
        while(valueL<=409)//左も反応
        {
         PORTD=0x24;//左旋回しつづける 
        }

       //右が無反応になるまで、ちょっとずつ左前に進む
       while(valueR<=409)//右が反応している間
       {
        PORTD=0x24;//左旋回
        delay(200);
        PORTD=0x28;//直進
        delay(200);
       }

       //右が反応するまでちょっとずつ右前に進む
       while(valueR>409)
       {
       PORTD=0x28;//直進
       delay(200);
       PORTD=0x18;//右旋回
       delay(200);
       }
      }*/







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
