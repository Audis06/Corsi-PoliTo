#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

const int TEMP_PIN = A1;

char server_address[]="192.168.1.12";
int server_port=8080;


char ssid[]="Home&Life SuperWiFi-0C65";
char pass[]="T48QR3BUDUFUTEY3";

WiFiClient wifi;
HttpClient client= HttpClient(wifi,server_address,server_port);
int status=WL_IDLE_STATUS;

float T;
const int B=4275;
const long int r0=100000;
const long int r1=100000;
float T0= 25 + 273.15;


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
  
  
}

void loop() {
  T=compute_temp();
  String body=senMlEncode("Temperature",T,"Celsius");
  Serial.println(body);

  client.beginRequest();
  client.post("/log");
  client.sendHeader("Content-Type", "application/json");
  client.sendHeader("Content-Length", body.length());
  client.beginBody();
  client.print(body);
  client.endRequest();

  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  Serial.println("Wait 1 seconds");
  delay(1000);
}



float compute_temp(){
  int Vsig=analogRead(TEMP_PIN);
  float R= (1023.0/Vsig -1)*r1;
  float T = 1/(log(R/r0)/B + 1/T0);
  T =T-273.15;
  return T;
}

String senMlEncode(String n, int val,String unit)
{
 return String("{\"bn\":\"ArduinoGroupX\",\"e\":[{\"n\":\""+n+"\",\"t\":"+millis()+",\"v\":"+val+",\"u\":\""+unit+"\"}]}")  ;
}
