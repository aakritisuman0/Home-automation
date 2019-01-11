
#include <SPI.h>
//#include <BlynkSimpleTI_CC3200_LaunchXL.h>
#include <BlynkSimpleEnergiaWiFi.h>
#include <WiFi.h>
#include <Wire.h>
#include <RTClib.h>
#include <Blynk.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#define analog_pin 24

// your network name also called SSID
char ssid[] = "Aakriti";
// your network password
char password[] = "aakriti143";
// your network key Index number (needed only for WEP)


uint16_t port = 23;     // port number of the server//TCP, UDP with telnet protocol: encrypted text communication
IPAddress server(192,168,43,80);   // IP Address of the server
WiFiClient client;
unsigned long oldTime;


RTC_Millis RTC;
DateTime now;
int i=30;
int j=0;
int k=0;
int val,val2;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500; 
double Voltage = 0;
double Amps = 0;
double voltage2 = 0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "bf6a6613668a4c589542cbc686e440d7";


void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
  RTC.begin(DateTime(__DATE__, __TIME__));
  pinMode(31,OUTPUT);
  pinMode(analog_pin,INPUT);

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

 Blynk.begin(auth,ssid,password);
 oldTime = 0;

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


BLYNK_WRITE(V1)
{
  j=param.asInt();
  Serial.print("Value of j is");
    Serial.print(j);
    Serial.println();
}


BLYNK_WRITE(V0)
{
  
i=param.asInt();
Serial.print(i);
    Serial.println();
 }

 
void light()
{
 if(j==1)
  {
    digitalWrite(31,HIGH);
    Serial.print(j);
    Serial.println();
    //read the serial command into a buffer
  }
  else
  {
  digitalWrite(31,LOW);
      
      //read the serial command into a buffer
}
}

void current_sensor()
{ 
  RawValue = analogRead(analog_pin);
 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 Amps = ((Voltage - ACSoffset) / mVperAmp);
 voltage2 =Voltage/1000;
 
 
 Serial.print("Raw Value = " ); // shows pre-scaled value 
 Serial.print(RawValue); 
 Serial.print("\t V = "); // shows the voltage measured 
 Serial.print(voltage2,3); // the '3' after voltage allows you to display 3 digits after decimal point
 Serial.print("\t Amps = "); // shows the voltage measured 
 Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point
 delay(1000);

   if((millis() - oldTime) > 5000)
 {
   oldTime = millis();
  
  float buffer1=Amps;
   
    //send the serial command to the server
    client.println(buffer1);
    client.println(buffer1);
    Serial.print("Sent: ");
    Serial.println(buffer1);
    
}

 }


void timedisplay()
{
 now=RTC.now();
Serial.print(now.year(), DEC);
Serial.print('/');
Serial.print(now.month(), DEC);
Serial.print('/');
Serial.print(now.day(), DEC);
Serial.print(' ');
Serial.print(now.hour(), DEC);
Serial.print(':');
Serial.print(now.minute(), DEC);
Serial.print(':');
Serial.print(now.second(), DEC);
Serial.println();
delay(1000);
}




void loop() {
  // put your main code here, to run repeatedly:
  if (client.available()) {
    char buffer[255] = {0};
    client.read((uint8_t*)buffer, client.available());
    Serial.print("Received: ");
    Serial.println(buffer);
}

  
timedisplay();
Blynk.run();
light();
current_sensor();
}

  
 

