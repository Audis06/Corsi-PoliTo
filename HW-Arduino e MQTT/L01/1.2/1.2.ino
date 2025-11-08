#include<MBED_RPi_Pico_TimerInterrupt.h>

const int RLED_PIN=2;
const int GLED_PIN=3;

const long R_HALF_PERIOD= 6000L;
const long G_HALF_PERIOD= 14000L;

int redLedState=LOW;
volatile int greenLedState=LOW;

MBED_RPI_PICO_Timer ITimer1(1);

void blinkGreen(uint alarm_num){
  TIMER_ISR_START(alarm_num);
  digitalWrite(GLED_PIN, greenLedState);
  serialPrintStatus();
  greenLedState=!greenLedState;
  TIMER_ISR_END(alarm_num);
}

void serialPrintStatus(){
  if(Serial.available()>0){
    int inByte=Serial.read();
    if(inByte==82){
      Serial.println("Led R status: " +String(redLedState));
    }
    if(inByte==86){
      Serial.println("Led V status: " +String(greenLedState));
    }
    if(inByte!= 82 && inByte!=86){
      Serial.println("Invalid command");
    }
  }
}

void setup() {
Serial.begin(9600);
while(!Serial);
Serial.println("Lab 1.2 Starting");
pinMode(RLED_PIN,OUTPUT);
pinMode(GLED_PIN,OUTPUT);
ITimer1.setInterval(G_HALF_PERIOD * 1000, blinkGreen);

}

void loop() {
digitalWrite(RLED_PIN, redLedState);
serialPrintStatus();
redLedState=!redLedState;
delay(R_HALF_PERIOD);
}
