#include<MBED_RPi_Pico_TimerInterrupt.h>

const int LED_PIN=2;
const int PIR_PIN=4;

volatile int tot_count=0;
volatile int LedState=LOW;
int pirStatus=LOW;

void setup() {
Serial.begin(9600);
while(!Serial);
Serial.println("Lab 1.3 Starting");
pinMode(LED_PIN,OUTPUT);
pinMode(PIR_PIN,INPUT);
attachInterrupt(digitalPinToInterrupt(PIR_PIN), checkPresence, CHANGE);
}

void checkPresence(){
  LedState=!LedState;
  digitalWrite(LED_PIN, LedState);
  if(digitalRead(pirStatus) == HIGH){
    tot_count++;
  }
}

void loop() {
Serial.println("Total people count: "+ String(tot_count));
delay(30000);
}

