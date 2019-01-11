#include <WiFi.h>
#include <Wire.h>

#include <RTClib.h>

// your network name also called SSID
char ssid[] = "Aakriti";
// your network password
char password[] = "aakriti143";
// your network key Index number (needed only for WEP)
byte SensorInterrupt = PUSH1;
byte SensorPin = PUSH1;
volatile int state = HIGH;
volatile byte pulsecount;


uint16_t port = 23;     // port number of the server//TCP, UDP with telnet protocol: encrypted text communication
IPAddress server(192,168,137,224);   // IP Address of the server
WiFiClient client;


RTC_Millis RTC;
              // the pin that the sensor is atteched to
     // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)
int motion1;
unsigned long oldTime;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  RTC.begin(DateTime(__DATE__, __TIME__));

   pinMode(RED_LED, OUTPUT);      // initalize LED as an output
  pinMode(18, INPUT);    // initialize sensor as an input

  motion1 =0;
  oldTime = 0;
  pulsecount=0;
  attachInterrupt(SensorInterrupt, pulsecounter, FALLING);
  
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
  val = digitalRead(18);   // read sensor value
  Serial.print(val);
  Serial.println();
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(RED_LED, HIGH);   // turn LED ON
    if((millis() - oldTime)>1000)
    detachInterrupt(SensorInterrupt);
    
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(RED_LED, LOW); // turn LED OFF
      if((millis() - oldTime)>1000)
    detachInterrupt(SensorInterrupt);
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
}
  }
  pulsecount=0;
  attachInterrupt(SensorInterrupt, pulsecounter, FALLING);
}
void pulsecounter()
{
  state!=state;
  pulsecount++;
}


