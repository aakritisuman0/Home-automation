#define analog_pin 24 

int sensitivity = 66;
int adcValue= 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;
 
void setup() 
{
  Serial.begin(9600);
  pinMode(24,OUTPUT);
}
 
void loop()
{
  adcValue = analogRead(analog_pin);
  adcVoltage = (adcValue / 1024.0) * 5000;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
  
  Serial.print("Raw Sensor Value = " );
  Serial.print(adcValue);

  Serial.print("\t Voltage(mV) = ");
  Serial.print(adcVoltage,3);
  
  Serial.print("\t Current = ");
  Serial.println(currentValue,3);
 
  delay(5000);
}
