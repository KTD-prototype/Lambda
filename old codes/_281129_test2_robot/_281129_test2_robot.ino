#include<SoftwareSerial.h>
SoftwareSerial JOY_receive(8, 9);

int A = 0;
int MotorR = 0;
int mode = 0;
int modechange = 0;
int ModeChangeFlag = 0;
byte JOY[6] = {0, 0, 0, 0, 0, 0};

void setup() {
  JOY_receive.begin(9600);
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {


  if (A == 0) {
    JOY_receive.write('S');
    A++;
  }

  while (JOY_receive.available() <= 6) {
    delayMicroseconds(1);
  }


  if (JOY_receive.available() > 6) {
    //Serial.println('C');
    if (JOY_receive.read() == 'H') {
      JOY[0] = JOY_receive.read();
      JOY[1] = JOY_receive.read();
      JOY[2] = JOY_receive.read();
      JOY[3] = JOY_receive.read();
      JOY[4] = JOY_receive.read();
      JOY[5] = JOY_receive.read();

      if (JOY[2] == 0 && JOY[5] == 0 && mode == 0) {
        mode = 1;
        delay(1000);
      }
      else if (JOY[2] == 0 && JOY[5] == 0 && mode == 1) {
        mode = 2;
        delay(1000);
      }
      else if (JOY[2] == 0 && JOY[5] == 0 && mode == 2) {
        mode = 0;
        delay(1000);
      }


      if (mode == 0) {
        Serial.println("mode : inactive");
      }
      else if (mode == 1) {
        Serial.print("mode : remote   ");
        if (JOY[0] > 135) {
          MotorR = (JOY[0] - 128) * 2;
          digitalWrite(5, LOW);
          analogWrite(6, MotorR);
          Serial.println(MotorR);
        }
        else if (JOY[0] < 120) {
          MotorR = 255 - JOY[0] * 2;
          digitalWrite(6, LOW);
          analogWrite(5, MotorR);
          Serial.print('-');
          Serial.println(MotorR);
        }
        else {
          digitalWrite(5, LOW);
          digitalWrite(6, LOW);
          Serial.println("");
        }
        
      }
      else if (mode == 2) {
        Serial.println("mode : auto");
      }


      JOY_receive.write('S');
    }
  }
  else {
    Serial.println("wait");
  }
}
