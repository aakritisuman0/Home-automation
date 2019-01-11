#include <WiFi.h>
#include<Wire.h>
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "JQJVXMU8V1W7TLND";
const int updateThingspeakInterval = 15*1000;
char buffer[225];
char ssid[] = "Abhigya";
char password[] = "abhigya123";
boolean lastConnected = false;
WiFiClient clients;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
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

}

void loop() {
  // put your main code here, to run repeatedly: 

  
  int a;
  for(a=0;a<100;a++)
  {String obj = dtostrf(a,1,0,buffer);
   Serial.println(obj);
   updateThingSpeak("field1=" +obj); 
  }

   while(clients.available())
{
  char c = clients.read();
  Serial.println(c);
}

if(!clients.connected() && lastConnected)
{
  Serial.print("disconnecting");
  clients.stop();
}
  
}

void updateThingSpeak(String tsData)
{
  if (clients.connect(thingSpeakAddress, 80))
  {         
    clients.print("POST /update HTTP/1.1\n");
    clients.print("Host: api.thingspeak.com\n");
    clients.print("Connection: close\n");
    clients.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    clients.print("Content-Type: application/x-www-form-urlencoded\n");
    clients.print("Content-Length: ");
    clients.print(tsData.length());
    Serial.println(">>TSDATALength=" + tsData.length());
    clients.print("\n\n");

    clients.print(tsData);
    Serial.println(">>TSDATA=" + tsData);

    if (clients.connected())
    {
      Serial.println("Connected and uploaded data to ThingSpeak...");
      Serial.println();
    }
    else
    {
           Serial.println("Connection to ThingSpeak failed");   
      Serial.println();
    }

  }
  else
  {
    
    Serial.println("Connection to ThingSpeak Failed");   
    Serial.println();
  }
  delay(1000);
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
