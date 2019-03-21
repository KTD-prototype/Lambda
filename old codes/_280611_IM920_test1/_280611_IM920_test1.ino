#include <SoftwareSerial.h>
SoftwareSerial IM920Serial(8,9);
int vol=0, vol_new=0, diff, busy;

void setup() {
  // put your setup code here, to run once:
  IM920Serial.begin(19200);
  pinMode(10,INPUT);
  pinMode(7,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  vol_new=analogRead(0)/4;
  diff=abs(vol_new-vol);

  if(diff>1){
    do{
      busy=digitalRead(10);
    }while(busy!=0);
    
    if(digitalRead(7)==1){
    IM920Serial.print("TXDT ");
            delay(30);
    IM920Serial.println('dcba',HEX);

    delay(30);
    }
    
    else if(digitalRead(7)==0){
    IM920Serial.print("TXDT ");
            delay(100);
    IM920Serial.println('abcd',HEX);
        delay(30);
    }
  }
}
