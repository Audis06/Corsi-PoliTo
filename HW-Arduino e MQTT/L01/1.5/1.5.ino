const int PIN=A1;
const int B=4275;
const long int r0=100000;
const long int r1=100000;
float T0= 25 + 273.15;

#include <math.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("lab 1.5 starting");
  pinMode(PIN,INPUT);
  
}



void loop() {
  // put your main code here, to run repeatedly:
  int Vsig=analogRead(PIN);
  Serial.println(Vsig);
  float R= (1023.0/Vsig -1)*r1;
  float T = 1/(log(R/r0)/B + 1/T0);
   T =T-273.15;
  Serial.println("temperatura: "+String(T));
  delay(1000);
}


