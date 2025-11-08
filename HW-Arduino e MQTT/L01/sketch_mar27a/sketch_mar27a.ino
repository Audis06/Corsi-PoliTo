#include<MBED_RPi_Pico_TimerInterrut.h>

const int RLED_PIN=2;
const int GLED_PIN=3;

const long R_HALF_PERIOD= 1500L;
const long R_HALF_PERIOD= 3500L;

MBED_RPI_PICO_Timer ITimer1(1);

void blinkGreen(uint alarm_num){
  TIMER_ISR_START(alarm_num);
  digitalWrite(GLED_PIN, greenLedState);
  greenLedState=!greenLedState;
  TIMER_ISR_END(alarm_num);
}

void setup() {
pinMode(RLED_PIN,OUTPUT);
pinMode(GLED_PIN,OUTPUT);
ITimer1.setInterval(G_HALF_PERIOD * 1000, blinkGreen);

}

void loop() {
digitalWrite(RLED_PIN, redLedState);
redLedState=!redLedState;
delay(R_HALF_PERIOD);
}
