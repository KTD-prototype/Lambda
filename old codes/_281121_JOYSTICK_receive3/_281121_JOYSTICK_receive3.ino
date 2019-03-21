#include<SoftwareSerial.h>
SoftwareSerial JOY_receive(8, 9);

int ansR = 0;
int RX, RY, RS, LX, LY, LS;
byte data;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  JOY_receive.begin(9600);
  Serial.begin(9600);
}

void loop() {

  JOY_receive.write('F');

  if (JOY_receive.available() >= sizeof('A') + sizeof(int)) {

    if (JOY_receive.read() == 'A') {
      int low = JOY_receive.read();
      int high = JOY_receive.read();
      RX = makeWord(high, low);
      JOY_receive.write('A');
    }


    if (JOY_receive.read() == 'B') {
      int low = JOY_receive.read();
      int high = JOY_receive.read();
      RY = makeWord(high, low);
      JOY_receive.write('B');
    }

    if (JOY_receive.read() == 'C') {
      int low = JOY_receive.read();
      int high = JOY_receive.read();
      RS = makeWord(high, low);
      JOY_receive.write('C');
    }

    if (JOY_receive.read() == 'D') {
      int low = JOY_receive.read();
      int high = JOY_receive.read();
      LX = makeWord(high, low);
      JOY_receive.write('D');
    }

    if (JOY_receive.read() == 'E') {
      int low = JOY_receive.read();
      int high = JOY_receive.read();
      LY = makeWord(high, low);
      JOY_receive.write('E');
    }

    if (JOY_receive.read() == 'F') {
      int low = JOY_receive.read();
      int high = JOY_receive.read();
      LS = makeWord(high, low);
      JOY_receive.write('F');
    }
  }



  /*
    RY = JOY_receive.read();
    RS = JOY_receive.read();
    LX = JOY_receive.read();
    LY = JOY_receive.read();
    LS = JOY_receive.read();
  */
  //}

  /*
    else{
    RX = 128;
    RY = 0;
    RS = 0;
    LX = 0;
    LY = 0;
    LS = 0;
    }
  */

  //analogWrite(5, RX/4);

  Serial.print(RX);
  Serial.print(" || ");
  Serial.print(RY);
  Serial.print(" || ");
  Serial.print(RS);
  Serial.print(" || ");
  Serial.print(LX);
  Serial.print(" || ");
  Serial.print(LY);
  Serial.print(" || ");
  Serial.print(LS);

  Serial.println("");

}
