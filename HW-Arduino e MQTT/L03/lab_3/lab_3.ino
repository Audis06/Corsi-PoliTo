#include <WiFiNINA.h>

const int LED_PIN = 2;
const int TEMP_PIN = A1;

char ssid[]="iPhone di Fabio";
char pass[]="12345678";

int status=WL_IDLE_STATUS;
WiFiServer server(80);

float T;
const int B=4275;
const long int r0=100000;
const long int r1=100000;
float T0= 25 + 273.15;


void process(WiFiClient );
float compute_temp();

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Lab 3 starting");
  
  pinMode(TEMP_PIN,INPUT);

  while(status!=WL_CONNECTED)
  {
    Serial.println("tentativo collegamento");
    status=WiFi.begin(ssid,pass);
    delay(1000);
  }
  Serial.println("connected with ip address: ");
  Serial.println(WiFi.localIP());
  server.begin();
 
}

void loop() {
  T=compute_temp();
  WiFiClient client=server.available();
  if(client){
    process(client);
    client.stop();
  }
  delay(50);

   

}



String senMlEncode(String n, int val,String unit)
{
 return String("{\"bn\": \"ArduinoGroupX\",\"e\" : [{\"n\":"+n+",\"t\":"+millis()+",\"v\":"+val+",\"u\":"+unit+"}]}")  ;
}



void process(WiFiClient client)
{
  String req_type = client.readStringUntil(' ');
  req_type.trim();
  String url=client.readStringUntil(' ');
  url.trim();
  if(url.startsWith("/led/"))
  {
    String led_val = url.substring(5);
    Serial.print(led_val);
    if(led_val == "0" || led_val=="1")
    {
      int val=led_val.toInt();
      digitalWrite(LED_PIN,val);
      printResponse(client, 200 , senMlEncode("led",val," ") );
    }
  }
  if(url.startsWith("/temperature"))
  {
      T=compute_temp();
      printResponse(client, 200 , senMlEncode("temperature",T,"Celsius") );
    
  }



}



void printResponse(WiFiClient client, int code, String body)
{
  client.println("HTTP/1.1 "+String(code));
  if(code==200)
  {
    client.println("Content-type: application/json; charset=utf-8");
    client.println();
    client.println(body);
  }else{
    client.println();
  }

}

float compute_temp(){
  int Vsig=analogRead(TEMP_PIN);
  float R= (1023.0/Vsig -1)*r1;
  float T = 1/(log(R/r0)/B + 1/T0);
  T =T-273.15;
  return T;
}







