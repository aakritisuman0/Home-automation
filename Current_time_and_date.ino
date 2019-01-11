// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
RTC_Millis RTC;
void setup () {
Serial.begin(9600);
// following line sets the RTC to the date & time this sketch was compiled
// uncomment it & upload to set the time, date and start run the RTC!
RTC.begin(DateTime(__DATE__, __TIME__));
pinMode(RED_LED,OUTPUT);
}
void loop () {
DateTime now = RTC.now();
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
if (now.hour()==11 && now.minute()>=41&& now.minute()<43)
{
Serial.println("aakriti");
Serial.println();
digitalWrite(RED_LED,HIGH);
}
else
{
Serial.println("abhigya");
Serial.println();
digitalWrite(RED_LED,LOW);
}
}
