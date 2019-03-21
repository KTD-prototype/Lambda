/*

copied from : https://forum.arduino.cc/index.php?topic=567414.0

Read pot on AIN1 convert value to voltage
then display on Arduino serial monitor.

By Lewis Loflin lewis@bvu.net
http://www.sullivan-county.com/main.htm
Electronics website:
http://www.bristolwatch.com/index.htm 

*/

#include <Wire.h> // specify use of Wire.h library
#define ASD1115 0x48

unsigned int val = 0;
byte writeBuf[3];
byte buffer[3];
float t_micro;

const float VPS = 4.096 / 32768.0; // volts per step

void setup()   {

  Serial.begin(115200); 
  Wire.begin(); // begin I2C

  // ASD1115
  // set config register and start conversion
  // ANC1 and GND, 4.096v, 128s/

  writeBuf[0] = 1;    // config register is 1
  
  // writeBuf[1] = 0b11010000; // 0xC2 single shot off <== NEW -  single conversion/ AIN1 & GND/ 6.144V/ Continuous (0)
  
  writeBuf[1] = 0b11010010; // 0xC2 single shot off <== ORIGINAL - single conversion/ AIN1 & GND/ 4.096V/ Continuous (0)
  
  // bit 15 flag bit for single shot
  // Bits 14-12 input selection:
  // 100 ANC0; 101 ANC1; 110 ANC2; 111 ANC3
  // Bits 11-9 Amp gain. Default to 010 here 001 P19
  // Bit 8 Operational mode of the ADS1115.
  // 0 : Continuous conversion mode
  // 1 : Power-down single-shot mode (default)


  //writeBuf[2] = 0b10000101; // bits 7-0  0x85 //8 SPS
  //writeBuf[2] = 0b10000101; // bits 7-0  0x85 //128 SPS
  writeBuf[2] = 0b11100101; // bits 7-0  0x85 //869 SPS 
  
  // Bits 7-5 data rate default to 100 for 128SPS
  // Bits 4-0  comparator functions see spec sheet.

  // setup ADS1115
  Wire.beginTransmission(ASD1115);  // ADC 
  Wire.write(writeBuf[0]); 
  Wire.write(writeBuf[1]);
  Wire.write(writeBuf[2]);  
  Wire.endTransmission();  

  delay(500);

}  // end setup

void loop() {

  buffer[0] = 0; // pointer
  Wire.beginTransmission(ASD1115);  // DAC
  Wire.write(buffer[0]);  // pointer
  Wire.endTransmission();

  Wire.requestFrom(ASD1115, 2);
  buffer[1] = Wire.read();  // 
  buffer[2] = Wire.read();  // 
  Wire.endTransmission();  

  // convert display results
  val = buffer[1] << 8 | buffer[2]; 

t_micro = micros();

  if (val > 32768) val = 0;
  Serial.print(t_micro/1000000.0,6);
  Serial.print("\t");
  Serial.print(val * VPS);
  Serial.print("\t");
  Serial.println(val);
  
} // end loop





