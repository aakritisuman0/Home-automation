#include <RTClib.h>

#include <WiFi.h>
#include <Wire.h>


// your network name also called SSID
char ssid[] = "Aakriti";
// your network password
char password[] = "aakriti143";
// your network key Index number (needed only for WEP)
int keyIndex = 0;

uint16_t port = 25;     // port number of the server//TCP, UDP with telnet protocol: encrypted text communication
IPAddress server(192,168,43,80);   // IP Address of the server
WiFiClient client;
RTC_Millis RTC;
#define analogPin 31           // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  RTC.begin(DateTime(__DATE__, __TIME__));


  pinMode(analogPin, OUTPUT);    // initialize sensor as an input

   // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED)
  {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nYou're connected to the network");
 Serial.println("Waiting for an ip address");
  
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");
  
  // you're connected now, so print out the status  
  printWifiStatus();
  
  // attempt to connect to the server
  Serial.println("Attempting to connect to server");

uint8_t tries = 0;
  while (client.connect(server, port) == false)
  {
    Serial.print(".");
    if (tries++ > 100) {
      Serial.println("\nThe server isn't responding");
      while(1);
    }
    delay(100);
  }
  
  //we've connected to the server by this point
  Serial.println("\nConnected to the server!");
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("Network Name: ");
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
void loop()
{
  // put your main code here, to run repeatedly:

    digitalWrite(analogPin, HIGH);   // turn FAN ON
    
}
