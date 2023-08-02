#include<ThingSpeak.h>
#include<ESP8266WiFi.h>

WiFiClient client;
unsigned long counterChannelNumber = 1735208;
const char *myCounterReadAPIKey = "56DO3RBY30LDC8R9"; //Read API Key
const int FieldNumber1 = 1;
const int FieldNumber2 = 2;

void setup() {
  pinMode(D1,OUTPUT);
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("ROG_Phone3","yoyoyoyo");
  Serial.println("Connecting");
  while(WiFi.status()!= WL_CONNECTED)
  {
    delay(500);
    Serial.print(",");
  }
  Serial.println();
  Serial.print("Connected, IP Address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop() {
  int A = ThingSpeak.readLongField(counterChannelNumber,FieldNumber1,myCounterReadAPIKey);
  Serial.println(A);
  digitalWrite(D1,A);
}
