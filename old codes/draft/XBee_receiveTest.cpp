void setup()
{
	Serial.begin(9600);	//�V���A���ʐM�̃f�[�^���[�g��bps(baud)�Ŏw��
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
		int val = Serial.read();	//��M�f�[�^��ǂݍ����val�֑��

		if (val == 'A')	//val��A�Ȃ�Ύ���
		{
			digitalWrite(3, HIGH);	//�s���R��HIGH���o��
			digitalWrite(2, LOW);	//�s���Q��LOW�o�́@�E���[�^���]
			delay(100);	//�^�C�}0,1s
			digitalWrite(3, LOW);	//�s��3��LOW���o�́B�EDC���[�^�[��~
		}

		else if (val == 'B')	//val��B�Ȃ�Ύ���
		{
			digitalWrite(3, LOW);
			digitalWrite(2, HIGH);	//�E���[�^�t�]
			delay(100);
			digitalWrite(2, LOW);	//�E���[�^��~
		}

		else if (val == 'C')	//val��C�Ȃ�Ύ���
		{
			digitalWrite(5, HIGH);
			digitalWrite(4, LOW);		//�����[�^���]
			delay(100);
			digitalWrite(5, LOW);	//�����[�^��~
		}

		else if (val == 'D')	//val��D�Ȃ�Ύ���
		{
			digitalWrite(5, LOW);
			digitalWrite(4, HIGH);	//�����[�^�t�]
			delay(100);
			digitalWrite(4, LOW);	//�����[�^��~
		}

		else if (val == 'E')	//val��E�Ȃ�Ύ���
		{
			digitalWrite(7, HIGH);
			digitalWrite(6, LOW);	//�ヂ�[�^���]
			delay(100);
			digitalWrite(7, LOW);
		}

		else if (val == 'F')	//val��F�Ȃ�Ύ���
		{
			digitalWrite(7, LOW);
			digitalWrite(6, HIGH);	//�ヂ�[�^�t�]
			delay(100);
			digitalWrite(7, LOW);
		}

	}
}