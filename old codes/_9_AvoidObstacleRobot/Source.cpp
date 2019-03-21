#include <Servo.h>//���C�u�����̓ǂݍ���
#define PBS1 0//�u������
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
	DDRB = B1111;//�|�[�gB�̓��o�͂�ݒ�
	servo0.attach(6);
}

void loop()
{
	s1 = digitalRead(PBS1);//���������Q����������铮��
							//PBS1�̒l��ǂݎ����S1�ɑ��

	if (s1 == 0)//S1��0�A���Ȃ킿PBS1���I���Ȃ玟��
	{
		while (1)//���[�v
		{
			PORTB = 0x05;//PORTB�ɏo�́B���{�b�g�O�i�B
			servo0.write(170);//�T�[�{�o��170�x�B�������W���[�������������B
			delay(500);
			
			value = analogRead(analogPin);//AD�ϊ��B�f�W�^���l��value�ɑ��
			
			if (value >= 266)//value��266�ȏ�Ȃ玟��
			{
				PORTB = 0x09;	//���{�b�g�E����
				delay(500);
			}


///////////////////////////////////////////////////////////////////////////////////

			PORTB = 0x05;	//���{�b�g�O�i
			servo0.write(90);//��������
			delay(500);

			value = analogRead(analogPin);//AD�ϊ��B�f�W�^���l��value�ɑ��
			if (value >= 409)//value��409�ȏ�Ȃ玟��
			{
				PORTB = 0x0a;	//���{�b�g��i
				delay(1000);
				PORTB = 0x06;	//���{�b�g������
				delay(500);
			}

///////////////////////////////////////////////////////////////////////////////////

			PORTB = 0x05;//PORTB�ɏo�́B���{�b�g�O�i�B
			servo0.write(10);//�����E�B
			delay(500);

			value = analogRead(analogPin);//AD�ϊ��B�f�W�^���l��value�ɑ��

			if (value >= 266)//value��266�ȏ�Ȃ玟��
			{
				PORTB = 0x06;	//���{�b�g������
				delay(500);
			}


///////////////////////////////////////////////////////////////////////////////////

			PORTB = 0x05;	//���{�b�g�O�i
			servo0.write(90);//��������
			delay(500);

			value = analogRead(analogPin);//AD�ϊ��B�f�W�^���l��value�ɑ��
			if (value >= 409)//value��409�ȏ�Ȃ玟��
			{
				PORTB = 0x0a;	//���{�b�g��i
				delay(1000);
				PORTB = 0x09;	//���{�b�g�E����
				delay(500);
			}





		}
	}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

	s2 = digitalRead(PBS2); //��������͏�Q���փA�^�b�N�@PBS2�̒l��ǂݎ����S2�ɑ��

	if (s2 == 0)	//s2=0���Ȃ킿PBS2��ON�Ȃ玟��
	{
		while (2)//���[�v
		{
			PORTB = 0x05;//PORTB�ɏo�́B���{�b�g�O�i�B
			servo0.write(170);//�T�[�{�o��170�x�B�������W���[�������������B
			delay(500);

			value = analogRead(analogPin);//AD�ϊ��B�f�W�^���l��value�ɑ��

			if (value >= 266)//value��266�ȏ�Ȃ玟��
			{
				PORTB = 0x0f;	//���{�b�g�u���[�L
				delay(500);
				PORTB = 0x0a;	//���{�b�g���
				delay(500);
				PORTB = 0x06;	//���{�b�g������
				delay(300);	
			}



///////////////////////////////////////////////////////////////////////////////////

			PORTB = 0x05;	//���{�b�g�O�i
			servo0.write(90);//��������
			delay(500);

			s3 = digitalRead(Limit);	//Limit�̒l��ǂݎ����s3�֑��
			if (s3 == 0)//s3��0���Ȃ킿�}�C�N���X�C�b�`��ON�Ȃ�Ύ���
			{
				PORTB = 0x0f;	//���{�b�g�u���[�L
				delay(500);
				PORTB = 0x0a;	//���{�b�g���
				delay(500);
				PORTB = 0x09;	//���{�b�g�E����
				delay(300);
			}



///////////////////////////////////////////////////////////////////////////////////

			PORTB = 0x05;	//���{�b�g�O�i
			servo0.write(10);//�����E
			delay(500);

			s3 = digitalRead(Limit);	//Limit�̒l��ǂݎ����s3�֑��
			if (value >= 266)//value��266�ȏ�Ȃ玟��
			{
				PORTB = 0x0f;	//���{�b�g�u���[�L
				delay(500);
				PORTB = 0x0a;	//���{�b�g���
				delay(500);
				PORTB = 0x09;	//���{�b�g�E����
				delay(300);
			}


///////////////////////////////////////////////////////////////////////////////////

			PORTB = 0x05;	//���{�b�g�O�i
			servo0.write(90);//��������
			delay(500);

			s3 = digitalRead(Limit);	//Limit�̒l��ǂݎ����s3�֑��
			if (s3 == 0)//s3��0���Ȃ킿�}�C�N���X�C�b�`��ON�Ȃ�Ύ���
			{
				PORTB = 0x0f;	//���{�b�g�u���[�L
				delay(500);
				PORTB = 0x0a;	//���{�b�g���
				delay(500);
				PORTB = 0x06;	//���{�b�g������
				delay(300);
			}




		}
	}
}