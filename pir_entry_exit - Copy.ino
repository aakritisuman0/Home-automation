
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(31,INPUT);
pinMode(9,INPUT);
pinMode(RED_LED,OUTPUT);
pinMode(10,OUTPUT);
}
int pir1=0;
int pir2=0;
int entry=0;
int counter=0;
int out=0;
void loop() {
 
  pir1=digitalRead(9);
   Serial.print("pir1= ");
  Serial.print(pir1);
  Serial.println();

  pir2=digitalRead(31);
  Serial.print("pir2= ");
  Serial.print(pir2);
  Serial.println();
  
  if(pir1==1 && pir2==0)
  {
    entry=1;
    Serial.print("entry: ");
    Serial.print(entry);
    Serial.println();
  }
  if(entry==1 && pir2==1)
  {
    counter=counter+1;
    Serial.print("counter: ");
    Serial.print(counter);
    Serial.println();
  }
  if(pir2==1 && pir1==0)
  {
    out=1;
    Serial.print("entry");
    Serial.print(entry);
    Serial.println();
    Serial.print("exit: ");
    Serial.print(out);
    Serial.println();
  }
  if(out==1 && pir1==1)
  {
  counter=counter-1;
   if (counter<0)
   {counter=0;
   }
  
  Serial.print("exit counter: ");
    Serial.print(counter);
    Serial.println();
  }
  
  if(counter==0)
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(10,LOW);
    Serial.print("light is off");
    Serial.println();
  }
  else
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(10,HIGH);
    Serial.print("light is on");
    entry=0;
    Serial.println();
  }
  delay(2500);
  Serial.println();
}
