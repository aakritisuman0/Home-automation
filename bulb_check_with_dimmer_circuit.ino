#include <Blynk.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space


#include <SPI.h>
#include <WiFi.h>
//#include <BlynkSimpleTI_CC3200_LaunchXL.h>
#include <BlynkSimpleEnergiaWiFi.h>" 
#include <Wire.h>
#include "RTClib.h"
char auth[] = "52e2738c640845599b70a6b304f8aa69";
#define analogpin 29

// Your WiFi credentials
char ssid[] = "Aakriti";
char pass[] = "aakriti143";        //
int i=150;
int j=0;
int k=0;
RTC_Millis RTC;
 DateTime now ;
int val,val2;

void setup () {
Serial.begin(9600);
pinMode(29,OUTPUT);
pinMode(31,OUTPUT);
Blynk.begin(auth,ssid,pass);
RTC.begin(DateTime(__DATE__, __TIME__));
}
// following line sets the RTC to the date & time this sketch was compiled
// uncomment it & upload to set the time, date and start run the RTC!
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
void light()
{
if(j==1)
  {
    analogWrite(analogpin,i);
    Serial.print(i);
    Serial.println();
  }
  else
  analogWrite(analogpin,115);
}
void loop () {
 
timedisplay();
if (now.hour()==14 && now.minute()>=00 && now.minute()<=59)
{
Serial.println("aakriti");
Blynk.run();
light();
}
}
