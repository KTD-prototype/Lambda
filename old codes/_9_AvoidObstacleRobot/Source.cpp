#include <Servo.h>//ライブラリの読み込み
#define PBS1 0//置き換え
#define PBS2 1
#define Limit 2
#define analogPin 0
int value = 0;
int s1, s2, s3;
Servo servo0;

void setup()
{
	pinMode(PBS1, INPUT);
	pinMode(PBS2, INPUT);
	pinMode(Limit, INPUT);
	pinMode(6, OUTPUT);
	DDRB = B1111;//ポートBの入出力を設定
	servo0.attach(6);
}

void loop()
{
	s1 = digitalRead(PBS1);//ここから障害物を回避する動作
							//PBS1の値を読み取ってS1に代入

	if (s1 == 0)//S1が0、すなわちPBS1がオンなら次へ
	{
		while (1)//ループ
		{
			PORTB = 0x05;//PORTBに出力。ロボット前進。
			servo0.write(170);//サーボ出力170度。測距モジュールが左を向く。
			delay(500);
			
			value = analogRead(analogPin);//AD変換。デジタル値をvalueに代入
			
			if (value >= 266)//valueが266以上なら次へ
			{
				PORTB = 0x09;	//ロボット右旋回
				delay(500);
			}


///////////////////////////////////////////////////////////////////////////////////

			PORTB = 0x05;	//ロボット前進
			servo0.write(90);//測距正面
			delay(500);

			value = analogRead(analogPin);//AD変換。デジタル値をvalueに代入
			if (value >= 409)//valueが409以上なら次へ
			{
				PORTB = 0x0a;	//ロボット後進
				delay(1000);
				PORTB = 0x06;	//ロボット左旋回
				delay(500);
			}

///////////////////////////////////////////////////////////////////////////////////

			PORTB = 0x05;//PORTBに出力。ロボット前進。
			servo0.write(10);//測距右。
			delay(500);

			value = analogRead(analogPin);//AD変換。デジタル値をvalueに代入

			if (value >= 266)//valueが266以上なら次へ
			{
				PORTB = 0x06;	//ロボット左旋回
				delay(500);
			}


///////////////////////////////////////////////////////////////////////////////////

			PORTB = 0x05;	//ロボット前進
			servo0.write(90);//測距正面
			delay(500);

			value = analogRead(analogPin);//AD変換。デジタル値をvalueに代入
			if (value >= 409)//valueが409以上なら次へ
			{
				PORTB = 0x0a;	//ロボット後進
				delay(1000);
				PORTB = 0x09;	//ロボット右旋回
				delay(500);
			}





		}
	}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

	s2 = digitalRead(PBS2); //ここからは障害物へアタック　PBS2の値を読み取ってS2に代入

	if (s2 == 0)	//s2=0すなわちPBS2がONなら次へ
	{
		while (2)//ループ
		{
			PORTB = 0x05;//PORTBに出力。ロボット前進。
			servo0.write(170);//サーボ出力170度。測距モジュールが左を向く。
			delay(500);

			value = analogRead(analogPin);//AD変換。デジタル値をvalueに代入

			if (value >= 266)//valueが266以上なら次へ
			{
				PORTB = 0x0f;	//ロボットブレーキ
				delay(500);
				PORTB = 0x0a;	//ロボット後退
				delay(500);
				PORTB = 0x06;	//ロボット左旋回
				delay(300);	
			}



///////////////////////////////////////////////////////////////////////////////////

			PORTB = 0x05;	//ロボット前進
			servo0.write(90);//測距正面
			delay(500);

			s3 = digitalRead(Limit);	//Limitの値を読み取ってs3へ代入
			if (s3 == 0)//s3が0すなわちマイクロスイッチがONならば次へ
			{
				PORTB = 0x0f;	//ロボットブレーキ
				delay(500);
				PORTB = 0x0a;	//ロボット後退
				delay(500);
				PORTB = 0x09;	//ロボット右旋回
				delay(300);
			}



///////////////////////////////////////////////////////////////////////////////////

			PORTB = 0x05;	//ロボット前進
			servo0.write(10);//測距右
			delay(500);

			s3 = digitalRead(Limit);	//Limitの値を読み取ってs3へ代入
			if (value >= 266)//valueが266以上なら次へ
			{
				PORTB = 0x0f;	//ロボットブレーキ
				delay(500);
				PORTB = 0x0a;	//ロボット後退
				delay(500);
				PORTB = 0x09;	//ロボット右旋回
				delay(300);
			}


///////////////////////////////////////////////////////////////////////////////////

			PORTB = 0x05;	//ロボット前進
			servo0.write(90);//測距正面
			delay(500);

			s3 = digitalRead(Limit);	//Limitの値を読み取ってs3へ代入
			if (s3 == 0)//s3が0すなわちマイクロスイッチがONならば次へ
			{
				PORTB = 0x0f;	//ロボットブレーキ
				delay(500);
				PORTB = 0x0a;	//ロボット後退
				delay(500);
				PORTB = 0x06;	//ロボット左旋回
				delay(300);
			}




		}
	}
}