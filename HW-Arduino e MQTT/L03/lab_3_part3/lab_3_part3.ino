#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

String broker_address = "test.mosquitto.org";
int broker_port=1883;

const String base_topic= "/tiot/group7";

const int capacity = JSON_OBJECT_SIZE(2) + JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(4)+100;
DynamicJsonDocument doc_snd(capacity);
DynamicJsonDocument doc_rec(capacity);

void callback(char* ,byte*,unsigned int);
void reconnect();

WiFiClient wifi;
PubSubClient client(broker_address.c_str(),broker_port,callback,wifi);

const int TEMP_PIN = A1;
const int LED_PIN = 2;

float T;
const int B=4275;
const long int r0=100000;
const long int r1=100000;
float T0= 25 + 273.15;

char ssid[]="Home&Life SuperWiFi-0C65";
char pass[]="T48QR3BUDUFUTEY3";

int status=WL_IDLE_STATUS;


float compute_temp();

void setup() {
  
  pinMode(TEMP_PIN,INPUT);
  pinMode(LED_PIN,OUTPUT);

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

  if(client.state() != MQTT_CONNECTED)
  {
    reconnect();
  }
  String body=senMlEncode("Temperature",T,"Celsius");
  //Serial.println(body);

  
  client.publish((base_topic + String("/temperature")).c_str()  ,  body.c_str()  );
  client.loop();
}




void callback(char* topic ,byte* payload,unsigned int length)
{
  
  Serial.println((char*)payload);
  DeserializationError err = deserializeJson(doc_rec,(char*)payload);
  if(err)
  {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(err.c_str());
      return;
  }
  if(doc_rec["e"][0]["n"]=="led")
  {
    Serial.println("change led status");
    if(doc_rec["e"][0]["v"]==1)
    {
      digitalWrite(LED_PIN, HIGH);
    }
    if(doc_rec["e"][0]["v"]==0)
    {
      digitalWrite(LED_PIN, LOW);
    }
    
  }
}



void reconnect()
{
  while(client.state() != MQTT_CONNECTED )
  {
    if(client.connect("TiotGroup7"))
    {
        client.subscribe( (base_topic + String("/led")).c_str() );
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 1 seconds");
      delay(1000);
    }


  }
}

float compute_temp(){
  int Vsig=analogRead(TEMP_PIN);
  float R= (1023.0/Vsig -1)*r1;
  float T = 1/(log(R/r0)/B + 1/T0);
  T =T-273.15;
  return T;
}


String senMlEncode(String n, float val,String unit)
{
  doc_snd.clear();
  doc_snd["bn"]="ArduinoGroup7";
  doc_snd["e"][0]["t"]=int(millis()/1000);
  doc_snd["e"][0]["v"]=val;
  doc_snd["e"][0]["u"]=unit;
  String output;
  serializeJson(doc_snd,output);
 return output;
}

