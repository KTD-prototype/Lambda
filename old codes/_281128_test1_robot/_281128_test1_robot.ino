#include<SoftwareSerial.h>
SoftwareSerial JOY_receive(8, 9);

int A = 0;
int count = 0;
int mode = 0;
int modechange = 0;
int ModeChangeFlag = 0;
byte JOY[6] = {0, 0, 0, 0, 0, 0};

void setup() {
  JOY_receive.begin(9600);
  Serial.begin(9600);
  //pinMode(
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
      JOY_receive.write('S');
    }
  }



  if (mode == 0) {
    Serial.println("mode : inactive");
  }
  else if (mode == 1) {
    Serial.println("mode : remote");
    //analogWrite();
    //analogWrite();
  }
  else if (mode == 2) {
    Serial.println("mode : auto");
  }





}
