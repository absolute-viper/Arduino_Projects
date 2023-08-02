#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


#define WLAN_SSID       "ROG_Phone3"
#define WLAN_PASS       "yoyoyoyo"

#define IO_SERVER      "io.adafruit.com"
#define IO_SERVERPORT  1883                   // use 8883 for SSL
#define IO_USERNAME  "absolute_viper"
#define IO_KEY       "aio_TWoC22HmniGwAyiYnoXT8gtQeDW8"

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;


// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, IO_SERVER, IO_SERVERPORT, IO_USERNAME, IO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe direction_control = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME "/feeds/welcome-feed");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)


void MQTT_connect();

void setup() {
  

  Serial.begin(115200);
  delay(10);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);  
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  analogWrite(ENB, 255);
  analogWrite(ENA, 255);
  
  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); 
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
  mqtt.subscribe(&direction_control);
}

uint32_t x=0;

void loop() {

  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &direction_control) {
      Serial.println((char *)direction_control.lastread);
      if(strcmp((char *)direction_control.lastread, "1") == 0){
        Forward();
        Serial.println("Forward");
      }
      else if(strcmp((char *)direction_control.lastread, "3") == 0){
        Serial.println("Left");
        Left();
        
      }
      else if(strcmp((char *)direction_control.lastread, "2") == 0){
        Serial.println("Right");
        Right();
        
      }
      else if(strcmp((char *)direction_control.lastread, "4") == 0){
        Serial.println("Backwards");
        Backwards();
        
      }
      else if(strcmp((char *)direction_control.lastread, "5") == 0){
        Serial.println("Cycle");
        Cycle();
        
      }
      else if(strcmp((char *)direction_control.lastread, "0") == 0){
        Serial.println("Stop");
        Stopping();
        
      }
    }
}
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");

  
}




void Cycle(){
  Forward();
  Left();
  ForwardShort();
  Right();
  ForwardShort();
  Left();
  ForwardShort();
  Left();
  ForwardShort();
  Right();
  ForwardShort();
  Left();
  ForwardShort();
  Right();
  ForwardShort();
  Left();
  ForwardShort();
  Right();
  ForwardShort();
  Left();
  ForwardShort();
  Right();
  Stopping(); 
}

void Forward(){
  
  digitalWrite(IN_2,LOW);
  digitalWrite(IN_4,LOW);
  analogWrite(ENA, 240);
  analogWrite(ENB, 225);
  digitalWrite(IN_1,HIGH);
  digitalWrite(IN_3,HIGH);
  delay(2000);
}

void ForwardShort(){
  digitalWrite(IN_1,HIGH);
  digitalWrite(IN_3,HIGH);
  digitalWrite(IN_2,LOW);
  digitalWrite(IN_4,LOW);
  delay(1550);
}

void Backwards(){
  digitalWrite(IN_1,LOW);
  digitalWrite(IN_3,LOW);
  digitalWrite(IN_2,HIGH);
  digitalWrite(IN_4,HIGH);
  delay(2000);  
}

void Right(){
  digitalWrite(IN_1,HIGH);
  digitalWrite(IN_2,LOW);
  digitalWrite(IN_3,LOW);
  digitalWrite(IN_4,LOW);
  delay(3500); 
}

void Left(){
  digitalWrite(IN_1,LOW);
  digitalWrite(IN_2,LOW);
  digitalWrite(IN_3,HIGH);
  digitalWrite(IN_4,LOW);
  delay(3800); 
}

void Stopping(){
  digitalWrite(IN_1,LOW);
  digitalWrite(IN_2,LOW);
  digitalWrite(IN_3,LOW);
  digitalWrite(IN_4,LOW);
}
