void setup()
{
	Serial.begin(9600);	//シリアル通信のデータレートをbps(baud)で指定
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
}

void loop()
{
	if (Serial.available() > 0)	//シリアルポートがデータを受信したら次へ
	{
		int val = Serial.read();	//受信データを読み込んでvalへ代入

		if (val == 'A')	//valがAならば次へ
		{
			digitalWrite(3, HIGH);	//ピン３にHIGHを出力
			digitalWrite(2, LOW);	//ピン２にLOW出力　右モータ正転
			delay(100);	//タイマ0,1s
			digitalWrite(3, LOW);	//ピン3にLOWを出力。右DCモーター停止
		}

		else if (val == 'B')	//valがBならば次へ
		{
			digitalWrite(3, LOW);
			digitalWrite(2, HIGH);	//右モータ逆転
			delay(100);
			digitalWrite(2, LOW);	//右モータ停止
		}

		else if (val == 'C')	//valがCならば次へ
		{
			digitalWrite(5, HIGH);
			digitalWrite(4, LOW);		//左モータ正転
			delay(100);
			digitalWrite(5, LOW);	//左モータ停止
		}

		else if (val == 'D')	//valがDならば次へ
		{
			digitalWrite(5, LOW);
			digitalWrite(4, HIGH);	//左モータ逆転
			delay(100);
			digitalWrite(4, LOW);	//左モータ停止
		}

		else if (val == 'E')	//valがEならば次へ
		{
			digitalWrite(7, HIGH);
			digitalWrite(6, LOW);	//上モータ正転
			delay(100);
			digitalWrite(7, LOW);
		}

		else if (val == 'F')	//valがFならば次へ
		{
			digitalWrite(7, LOW);
			digitalWrite(6, HIGH);	//上モータ逆転
			delay(100);
			digitalWrite(7, LOW);
		}

	}
}