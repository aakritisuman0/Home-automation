#include <Blynk.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space


#include <SPI.h>
#include <WiFi.h>
//#include <BlynkSimpleTI_CC3200_LaunchXL.h>
#include <BlynkSimpleEnergiaWiFi.h>" 
#include <Wire.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "bf6a6613668a4c589542cbc686e440d7";


// Your WiFi credentials
char ssid[] = "Aakriti";
char pass[] = "aakriti143";        //
int i=0;
int j=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(9,OUTPUT);
Blynk.begin(auth,ssid,pass);
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
    analogWrite(9,i);
    Serial.print(i);
    Serial.println();
  }
  else
  analogWrite(9,115);
}

void loop() {
  // put your main code here, to run repeatedly:
Blynk.run();
light();

  
}

