#include <WiFi.h>
#include<Wire.h>
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "JQJVXMU8V1W7TLND";
const int updateThingspeakInterval = 15*1000;
char buffer[225];
char ssid[] = "Aakriti";
char password[] = "aakriti143";
WiFiClient clients;
unsigned long lastConnectionTime = 0;
boolean lastConnected = false;
const unsigned long postingInterval = 10*1000;
int failedCounter =0; 
int val =1;
boolean state = LOW;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);      // initalize LED as an output
  pinMode(31, INPUT);  
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

if(!clients.connected() && (millis() - lastConnectionTime > 10000))
{
val = digitalRead(31);   // read sensor value
  Serial.println();
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(RED_LED, HIGH);   // turn LED ON
    Serial.println(val);
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!");
      state = HIGH;       // update variable state to HIGH
    }
   String obj = dtostrf(val,1,0,buffer);
   Serial.println(obj);
   updateThingSpeak("field1=" +obj); 
 } 
  else {
      digitalWrite(RED_LED, LOW); // turn LED OFF
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        Serial.println(val);
        state = LOW;       // update variable state to LOW
}
  String obj = dtostrf(val,1,0,buffer);
   updateThingSpeak("field1=" +obj); 


  }  
}
  lastConnected = clients.connected();

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
 
    clients.println(tsData);
    Serial.print(">>TSDATA=" + tsData);

    if (clients.connected())
    {
      Serial.println("Connected and uploaded data to ThingSpeak...");
      Serial.println();
      failedCounter = 0;
    }
    else
    {
      failedCounter++;
      Serial.println("Connection to ThingSpeak failed ("+String(failedCounter, DEC)+")");   
      Serial.println();
    }

  }
  else
  {
    failedCounter++;
    Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");   
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

