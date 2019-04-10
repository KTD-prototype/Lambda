#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <TimerOne.h>

// define the number of sample to get data to calibrate and sampling rate
#define NUM_OF_SAMPLES_FOR_INIT 500
#define SAMPLING_RATE 100

volatile int interrupt_flag = 1;
float a, b, c;
int previous_time = 0;
int present_time = 0;
int passed_time = 0;
float count = 0.00;

void setup() {
  Serial.begin(115200);
  Timer1.initialize(1000000 / SAMPLING_RATE); //interrupt per 10000 micro seconds(10 msec)
  Timer1.attachInterrupt(interrupt_function);

  a = 10.00;
  b = 11.00;
  c = 12.00;
}

void loop() {
  if (interrupt_flag == 1) {
    //    print_time();

    count++;
    a = count;
    b = count + 1.01;
    c = count + 2.02;
    //    Serial.println();
    interrupt_flag = 0;
  }

  if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      Serial.read();
      //      Serial.println("read");
    }
    Serial.println(a);
    Serial.println(b);
    Serial.println(c);
  }
}


void interrupt_function() {
  interrupt_flag = 1;
}

void print_time() {
  present_time = micros();
  passed_time = present_time - previous_time;
  Serial.println(passed_time);
  previous_time = present_time;
}
