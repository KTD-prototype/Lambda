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
	if (Serial.available() > 0)	//�V���A���|�[�g���f�[�^����M�����玟��
	{
		val = Serial.read();	//��M�f�[�^��ǂݍ���ł��̒l��val�ɑ��
		if (val == 'A')	//val��A�Ȃ�Ύ���
		{
			digitalWrite(5, HIGH);	//�s��5��HIGH���o��
			digitalWrite(4, LOW);	//�s��4��LOW�o�́@
			digitalWrite(3, HIGH);	//�s���R��HIGH���o��
			digitalWrite(2, LOW);	//�s���Q��LOW�o�́@�N���[���O�i
			
			delay(100);	//�^�C�}0,1s
			
			digitalWrite(5, LOW);	//
			digitalWrite(3, LOW);	//��~

			AD = analogRead(analogPin);	//A-D�ϊ����f�W�^���l��AD�ɑ��
			if (AD >= 409)	//AD>=409�Ȃ玟��
			{
				Serial.print('H');	//�V���A���|�[�g��H�𑗐M
				delay(1000);	//�^�C�}�P��
			}
		}


		else if (val == 'B')
		{
			digitalWrite(5, LOW);	//
			digitalWrite(4, HIGH);	//�@
			digitalWrite(3, LOW);	//
			digitalWrite(2, HIGH);	//�N���[�����

			delay(100);	//�^�C�}0,1s

			digitalWrite(4, LOW);	//
			digitalWrite(2, LOW);	//��~
		}


		else if (val == 'C')
		{
			digitalWrite(5, HIGH);	//
			digitalWrite(4, LOW);	//�@
			digitalWrite(3, LOW);	//
			digitalWrite(2, HIGH);	//�N���[���E����

			delay(100);	//�^�C�}0,1s

			digitalWrite(5, LOW);	//
			digitalWrite(2, LOW);	//��~
		}


		else if (val == 'D')
		{
			digitalWrite(5, LOW);	//
			digitalWrite(4, HIGH);	//�@
			digitalWrite(3, HIGH);	//
			digitalWrite(2, LOW);	//�N���[��������

			delay(100);	//�^�C�}0,1s

			digitalWrite(4, LOW);	//
			digitalWrite(3, LOW);	//��~
		}


		else if (val == 'E')
		{
			digitalWrite(7, HIGH);
			digitalWrite(6, LOW);	//���N���[�������グ
			delay(100);
			digitalWrite(7, LOW);	//��~
		}


		else if (val == 'F')
		{
			digitalWrite(7, LOW);
			digitalWrite(6, HIGH);	//���N���[�����낵
			delay(100);
			digitalWrite(6, LOW);	//��~
		}

		else if (val == 'G')
		{
			value = analogRead(analogPin);	//AD�ϊ����f�W�^���l��value�֑��
			Serial.print("Distance= ");		//�V���A���[����Distance=�ƕ\��
			if (value > threshold)			//value��臒l���傫�����
			{
				range = (6787 / (value - 3)) - 4;	//�f�W�^���lvalue�������ɕϊ���range�ɑ��
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
