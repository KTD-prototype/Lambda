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
	if (Serial.available() > 0)	//�V���A���|�[�g���f�[�^����M�����玟��
	{
		val = Serial.read();	//��M�f�[�^��ǂݍ����val�֊i�[
		if (val == 'H')	//val��High�Ȃ玟��
		{
			digitalWrite(Buzzer, HIGH);	//Buzzer��High�o�́A�u�U�[����
			delay(2000);
			digitalWrite(Buzzer, LOW);	//Buzzer������
			delay(20);
		}
	}

	int s1 = digitalRead(PBS1);	//PBS1�̒l��ǂݎ���Ă��P�ɑ��
	int s2 = digitalRead(PBS2);
	int s3 = digitalRead(PBS3);
	int s4 = digitalRead(PBS4);

	if (s1 == 0 && s2 == 0)	//1��ON����2��ON
	{
		Serial.print('A');	//�V���A���|�[�g��A�𑗐M
		delay(100);	//�^�C�}0.1s
	}

	else if (s3 == 0 && s4 == 0)
	{
		Serial.print('B');	//�V���A���|�[�g��B�𑗐M
		delay(100);	//�^�C�}�O�D�P��
	}

	else if (s2 == 0 && s3 == 0)
	{
		Serial.print('C');	//�V���A���|�[�g��C�𑗐M
		delay(100);	//�^�C�}�O�D�P��
	}

	else if (s1 == 0 && s4 == 0)
	{
		Serial.print('D');	//�V���A���|�[�g��D�𑗐M
		delay(100);	//�^�C�}�O�D�P��
	}

	else if (s1 == 0 && s3 == 0)
	{
		Serial.print('E');	//�V���A���|�[�g��E�𑗐M
		delay(100);	//�^�C�}�O�D�P��
	}

	else if (s2 == 0 && s4 == 0)
	{
		Serial.print('F');	//�V���A���|�[�g��F�𑗐M
		delay(100);	//�^�C�}�O�D�P��
	}
}