#include <math.h>
#include <LiquidCrystal_PCF8574.h>
#include <PDM.h>


LiquidCrystal_PCF8574 lcd(0x20); 

const int LED_PIN = A0;
const int TEMP_PIN = A1;
const int FAN_PIN = A2;
const int PIR_PIN = 17;   //vecchio A3 , dobbiamo usare un digital pin
const int GREEN_LED = 2;

const int B=4275;
const long int r0=100000;
const long int r1=100000;
float T0= 25 + 273.15;

float currentspeed=0;
float currentlight=0;
bool presence_pir=false;
bool presence_sound=false;
int last_presence_pir=0; //save millis of last presence
const int timeout_pir=5000;

//valori per HT alti per fare i test
float mHTp=19.0,mHTa=20.0, MHTp=27.0, MHTa=28.0, mACp=23.0, mACa=24.0, MACp=29.0, MACa=30.0;

volatile short sampleBuffer[256];
int samlesRead=0;

const int n_sound_events=10; //numero eventi suoni soglia
const int sound_threshold=300; //soglia livello suono
const int sound_interval = 15000; //ultimi 150 secondi salvati
const int event_delay=300;
const int timeout_sound = 20000 ;
int last_presence_sound=0; //save millis of last presence
int last_event_sound=0;

int Time_switch_screen=10000; //tempo per cambiare schermata display
//menu


bool green_led=0;
const int clap_inteval=1000;

void air_conditioning_control(int);
void heater_control(int);
float compute_temp();
void set_present_pir();
void check_timeout_pir();
void check_timeout_sound();
bool is_someone();
void onPDMdata();
void screen_update(float);
void new_sound_event();
int count_events();
void is_sound();
void menu();
void clap_turn_on();   //bonus

int events[sound_interval/event_delay];
int events_lenght=sound_interval/event_delay;
bool first=true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Lab 2 starting");
 
  menu();
  attachInterrupt( digitalPinToInterrupt(PIR_PIN),set_present_pir,CHANGE);
  pinMode(FAN_PIN,OUTPUT);
  pinMode(TEMP_PIN,INPUT);
  pinMode(LED_PIN,OUTPUT);
  pinMode(PIR_PIN,INPUT);
  pinMode(GREEN_LED,OUTPUT);

  PDM.onReceive(onPDMdata);
  while(!PDM.begin(1, 16000));
  lcd.begin(16,2);
  lcd.setBacklight(200);
  lcd.home();
  lcd.clear();
  lcd.noBlink(); //nascondo cursore
  
  for(int i=0;i<events_lenght;i++)
  {
    events[i]=-1;//evento non presente
  }
  
}

int first_clap=0;
int screen_update_delay=millis();

void loop() {

 
  menu();
  float T=compute_temp();
  air_conditioning_control(T);
  heater_control(T);

  if(millis()-screen_update_delay>500) // non aggiorno sempre lo schermo
  {
    screen_update(T);
    screen_update_delay=millis();
  }
  check_timeout_pir();
  check_timeout_sound();

  //Serial.println(String(T)+" C"); // debug per sound 
  /*Serial.println("N:"+String(count_events()));

  for(int i=0;i<events_lenght;i++)
  {
    Serial.print(events[i]);
    Serial.print("\t");
  }
   Serial.print("\n");*/
  //Serial.println(String(currentspeed));
  //Serial.println(String(currentlight));

  
  if(samlesRead)
  {
    for(int i=0;i<samlesRead;i++)
    {
      if(millis()-last_event_sound<event_delay)
        break;
      //Serial.print(sampleBuffer[i]);
      //Serial.print("\t");
      
      if( abs(sampleBuffer[i]) >sound_threshold)
      {
        new_sound_event();  //genero un solo evento anche se ci sono più saple > sound_ thrashold, perchè sono molto vicini i sample e non ha senso considerarli come un nuovo evento
        samlesRead=0;

        if( millis()-first_clap <clap_inteval)
          clap_turn_on();
        else         
          first_clap=millis();

        break;
      }
    }
    //Serial.print("\n");
    
  }
  is_sound();

 //delay(1000);
 
}


void air_conditioning_control(int T){
  //controlli per gestione 'condizionatore' (ventola)
  if(T>=MACa){
    analogWrite(FAN_PIN, 255);
    currentspeed=255; 
  }
  else if(T<=mACa){
    analogWrite(FAN_PIN, 0);
    currentspeed=0;
  }
  else{
    currentspeed=map(T,mACa,MACa, 0, 255);
    analogWrite(FAN_PIN, (int)currentspeed);
  }
}

void heater_control(int T){
  //controlli per gestione 'riscaldamento' (led)
  if(T>=MHTa){
    analogWrite(LED_PIN,0);
    currentlight=0;
  }
  else if(T<mHTa){
    analogWrite(LED_PIN,255);
    currentlight=255;
  }
  else{
    float temp=map(T,mHTa,MHTa, 0, 255);
    currentlight = 255.0-temp;
    analogWrite(LED_PIN,(int)currentlight);
  }
}

float compute_temp(){
  int Vsig=analogRead(TEMP_PIN);
  float R= (1023.0/Vsig -1)*r1;
  float T = 1/(log(R/r0)/B + 1/T0);
  T =T-273.15;
  return T;
}


bool is_someone(){
  if(presence_sound || presence_pir )
    return true;
  else
    return false;
}


void set_present_pir(){
  presence_pir=true;
  last_presence_pir=millis();
}

void onPDMdata() // è una ISR 
{
  int bytesAvailable = PDM.available();
  PDM.read( (void*)sampleBuffer,  bytesAvailable);
  samlesRead = bytesAvailable/2;
}

unsigned long CurrentMillis = millis();
void screen_update(float T)
{
  float temp_mHT, temp_MHT,  temp_mAC,  temp_MAC;
  if(is_someone())
  {
    temp_mHT=mHTp;
    temp_MHT=MHTp;
    temp_mAC=mACp;
    temp_MAC=MACp;
  }
  else
  {
    temp_mHT=mHTa;
    temp_MHT=MHTa;
    temp_mAC=mACa;
    temp_MAC=MACa;
  }


  if(millis()-CurrentMillis < Time_switch_screen) //schermata 1
  {   
      lcd.home();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("T:"+String(T));
      lcd.setCursor(9,0);
      lcd.print("Pres:"); // mettere funzione presenza da implementare
      lcd.setCursor(14,0);
      if(is_someone())    
        lcd.print("1");     
      else
        lcd.print("0");
      lcd.setCursor(0, 1);
      int val_speed_perc=(currentspeed/255.0)*100.0;
      int val_light_perc=(currentlight/255.0)*100.0;
      lcd.print("AC:" + String(val_speed_perc)+"%");
      lcd.setCursor(9, 1);
      lcd.print("HT:" + String(val_light_perc)+"%" );
  }
  else if(millis()-CurrentMillis < Time_switch_screen*2) //schermata 2
  {
    lcd.home();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AC ");
    lcd.setCursor(3, 0);
    lcd.print("m:"+String(temp_mAC));
    lcd.setCursor(9, 0);
    lcd.print(" ");
    lcd.setCursor(10, 0);
    lcd.print("M:"+String(temp_MAC));


    lcd.setCursor(0, 1);
    lcd.print("HT ");
    lcd.setCursor(3, 1);
    lcd.print("m:"+String(temp_mHT));
    lcd.setCursor(9, 1);
    lcd.print(" ");
    lcd.setCursor(10, 1);
    lcd.print("M:"+String(temp_MHT));

  }
  else
  {
    CurrentMillis=millis();
  }
  
}


void check_timeout_pir()
{
  if(millis()-last_presence_pir > timeout_pir)
    presence_pir=false;
}

void check_timeout_sound()
{
  if(millis()-last_presence_sound > timeout_sound)
    presence_sound=false;
}

void new_sound_event()
{
  
  
  last_event_sound=millis();
  for(int i=0;i<events_lenght;i++)
  {
    if(events[i]==-1)
    {
      events[i]=millis();
      break;
    }
    else if(millis()-events[i]>sound_interval) // elimino eventi piu vecchi di sound interval
    {
      events[i]=millis();
      break;
    }
    

  }
}


int count_events()
{
  int N=0;
  for(int i=0;i<events_lenght;i++)
  {
    if(millis()-events[i]<sound_interval && events[i]!=-1 )
      N++;
  }
  return N;
}



void is_sound()
{
  if(count_events()>n_sound_events)
  {
    last_presence_sound=millis(); 
    presence_sound=true;
  }
  
}


bool other=false;

void menu(){
  if(first){
  Serial.println("Menu per il cambiamento delle temperature:");
  Serial.println("Temperatura in caso di presenza:");
  Serial.println("0: mACp->per la minima temperatura del condizionatore");
  Serial.println("1: MACp->per la massima temperatura del condizionatore");
  Serial.println("2: mHTp->per la minima temperatura del riscaldamento");
  Serial.println("3: MHTp->per la massima temperatura del riscaldamento");
  Serial.println("");
  Serial.println("Temperatura in caso di non presenze nella stanza:");
  Serial.println("4: mACa->per la minima temperatura del condizionatore");
  Serial.println("5: MACa->per la massima temperatura del condizionatore");
  Serial.println("6: mHTa->per la minima temperatura del riscaldamento");
  Serial.println("7: MHTa->per la massima temperatura del riscaldamento");
  Serial.println("Inserire un numero da (0-7) per selezionare la variabile da modificare e succesivamente la temperatura desiderata");
  first=false;
  }
 
  
  if(Serial.available()){
  //char input=Serial.read();
  //Serial.print("Inserire il valore desiderato di ");
  char input=Serial.read();
  switch(input){
    case '0':
   	  Serial.print("mACp: \n");
      mACp=Serial.parseFloat();
      //Serial.println("check");
      Serial.println(String(mACp));
      break;
    case '1':
      Serial.print("MACp: \n");
      MACp=Serial.parseFloat();
      Serial.println(String(MACp));
      break;
    case '2':
      Serial.print("mHTp: \n");
      mHTp=Serial.parseFloat();
      Serial.println(String(mHTp));
      break;
    case '3':
      Serial.print("MHTp: \n");
      MHTp=Serial.parseFloat();
      Serial.println(String(MHTp));
      break;
    case '4':
      Serial.print("mACa: \n");
      mACa=Serial.parseFloat();
      Serial.println(String(mACa));
      break;
    case '5':
      Serial.print("MACa: \n");
      MACa=Serial.parseFloat();
      Serial.println(String(MACa));
      break;
    case '6':
      Serial.print("mHTa: \n");
      mHTa=Serial.parseFloat();
      Serial.println(String(mHTa));
      break;
    case '7':
      Serial.print("MHTa: \n");
      MHTa=Serial.parseFloat();
      Serial.println(String(MHTa));
      break;
  }
    other=true;
    
  }
  
}




void clap_turn_on()
{
   if(green_led)
    {
      digitalWrite(GREEN_LED, LOW);
      green_led=0;
    }
   else
    {
      digitalWrite(GREEN_LED, HIGH);
      green_led=1;
    }
}




