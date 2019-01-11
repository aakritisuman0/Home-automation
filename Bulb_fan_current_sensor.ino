// Date and time functions us
//ing a DS1307 RTC connected via I2C and Wire lib
#include <Blynk.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#define analog_pin 24

#include <SPI.h>
#include <WiFi.h>
//#include <BlynkSimpleTI_CC3200_LaunchXL.h>
#include <BlynkSimpleEnergiaWiFi.h>" 
#include <Wire.h>
#include "RTClib.h"
char auth[] = "bf6a6613668a4c589542cbc686e440d7";


// Your WiFi credentials
char ssid[] = "Aakriti";
char pass[] = "aakriti143";        //
int i=170;
int j=0;
int k=0;
RTC_Millis RTC;
DateTime now ;
int val,val2;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500; 
double Voltage = 0;
double Amps = 0;
double voltage2 = 0;


void setup () {
Serial.begin(9600);
pinMode(9,OUTPUT);
pinMode(31,OUTPUT);
pinMode(analog_pin,INPUT);

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

 BLYNK_WRITE(V2)
{
  
k=param.asInt();
Serial.print(i);
    Serial.println();
 }

void light()
{
 if(j==1)
  {
    analogWrite(9,i);
    Serial.print(i);
    Serial.println();
  }
  else
  analogWrite(9,115);
  if(k==1)
  {
  Serial.println("fan is on");
  Serial.println();
  digitalWrite(31,HIGH);
  }
  else
  {
  Serial.println("fan is off");
  Serial.println();
  digitalWrite(31,LOW);
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
 delay(2500); 
}


 void loop () {
 
timedisplay();
if (now.hour()==15 && now.minute()>=00 && now.minute()<=59)
{
Serial.println("aakriti");
Blynk.run();
light();
current_sensor();
}
else
{
analogWrite(9,120);
digitalWrite(31,LOW);
}
 }
