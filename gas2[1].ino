#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
int sensorpin=A0;
int sensorvalue;
int buzzer=6;
int LED=8;

void setup() {
  mySerial.begin(19200);
  Serial.begin(9600);
  pinMode(sensorpin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode (LED, OUTPUT);

}

void loop() {
sensorvalue=analogRead(sensorpin);
Serial.println(sensorvalue);
delay(1000);
if(sensorvalue>280){
  digitalWrite(buzzer,HIGH);
  digitalWrite(LED, HIGH);
  mySerial.print("AT+CMGF=1\r"); 
  delay(100);
   mySerial.println("AT + CMGS = \"+254713378076\"\r"); 
  delay(100);
  mySerial.println(sensorvalue); 
  delay(100);
  mySerial.println((char)26); 
  delay(100);
  Serial.println("pollution alert!!!!"); 
  delay(4000);
  }
 else{
  Serial.println("No pollution");
  digitalWrite(buzzer,LOW);
  digitalWrite(LED, LOW) ;
  }

}
