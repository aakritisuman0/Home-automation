#include <Blynk.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space


#include <SPI.h>
#include <WiFi.h>
//#include <BlynkSimpleTI_CC3200_LaunchXL.h>
#include <BlynkSimpleEnergiaWiFi.h>" 
#include <Wire.h>
#include "RTClib.h"
#include <WiFi.h>
#include <RTClib.h>
char auth[] = "bf6a6613668a4c589542cbc686e440d7";
RTC_Millis RTC;
WiFiClient clients;  
WiFiClient client; 
WiFiClient client2;
boolean alreadyConnected = false;
boolean alreadyConnected2 = false;
char ssid[] = "Aakriti";
char password[] = "aakriti143";
char buffer1[255];
char buffer[255];
int j=0;
int k=0;
WiFiServer port(23);
WiFiServer port2(25);
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Blynk.begin(auth,ssid,password);
  RTC.begin(DateTime(__DATE__, __TIME__));
  Serial.print("Attempting to connect to Network named: ");
  Serial.println(ssid); 
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");  
  while (WiFi.localIP() == INADDR_NONE) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nIP Address obtained");
  printWifiStatus();
   port.begin();
  port2.begin();
}

BLYNK_WRITE(V1)
{
  j=param.asInt();
  Serial.print("Value of j is");
    Serial.print(j);
    Serial.println();
}

 BLYNK_WRITE(V2)
{
  
k=param.asInt();
Serial.print(k);
    Serial.println();
 }
void loop() {
  Blynk.run();
  DateTime now = RTC.now();
    
    client = port.available();
    if (client) {
      if(!alreadyConnected) {
      // clear out the input buffer:
      client.flush();
      Serial.println("We have a new client from port1");
      client.println("Hello, client1!");
      alreadyConnected = true;
    }
    if (client.available() > 0) {
      // read the bytes incoming from the client:
      char buffer1[255] = {0};
      client.read((uint8_t*)buffer1, client.available());
    }

    }
    
 client2 = port2.available(); 
    if (client2) {
      if (!alreadyConnected2) {
      // clear out the input buffer:
      client2.flush();
      Serial.println("We have a new client from port2");
      client2.println("Hello, client!");
      alreadyConnected2 = true;
      }  
      if (client2.available() > 0) {
      // read the bytes incoming from the client:
      //char thisChar = client2.read();
      char buffer[255] = {0};
      client2.read((uint8_t*)buffer, client2.available());
      }
    }
    
}
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm"); 
}

