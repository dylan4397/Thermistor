//Dylan Dickson December 2020

//Defining variables and importing libraries
#include "SevSeg.h"
SevSeg sevseg;
int ThermistorPin = A0;
int Vo;
float R1 = 10000; //Value of R1 on board
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; //steinhart-hart coeficients for thermistor

void setup() {
  //Setting up the display
  byte numDigits = 3;
  byte digitPins[] = {A3, A4, A5};
  byte segmentPins[] = {3/*A*/, 5/*B*/, 8/*C*/, 7/*D*/, 6/*E*/, 2/*F*/, 4/*G*/, 9/*DEC*/}; // A,B,C,D,E,F,G,dec.
  bool resistorsOnSegments = true;
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(100);
}

void loop() {
  //Reading values from the thermistor, converting them and writing to the display
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); //Calculate resistance on thermistor
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); //Temperature in Kelvin
  T = T - 273; //Convert Kelvin to Celcius
 // T = (T * 9.0)/ 5.0 + 32.0; //convert Celcius to Farenheit (uncomment if you want to display Farenhiet instead)

  //Write the values to the display, and refresh it
  sevseg.setNumber(T);
  sevseg.refreshDisplay();
}
