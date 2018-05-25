#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
int sensorpin=A0;
int sensorvalue;
int redLED=5;
int greenLED=6;
int buzzer=8;
int reading;
int timetosend=LOW;
int Sentdata=0;
int commled=7;
unsigned long previousMillis=0;
const long interval=60000;

void setup() {
  mySerial.begin(19200);
  Serial.begin(9600);
  pinMode(sensorpin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode (redLED, OUTPUT);
  pinMode (greenLED, OUTPUT);

}

void loop() {
sensorvalue=analogRead(sensorpin);
Serial.println(sensorvalue);
delay(1000);
if(sensorvalue>300){
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(redLED, HIGH);
  delay(100);
  digitalWrite(greenLED, LOW);
  delay(100);
  mySerial.print("AT+CMGF=1\r"); 
  delay(100);
   mySerial.println("AT + CMGS = \"+2547xxxxxxxx\"\r");     //text sent to the modem
  delay(100);
  mySerial.println(sensorvalue); 
  delay(100);
  mySerial.println((char)26); 
  delay(100);
  
    mySerial.print("AT+CMGF=1\r"); 
  delay(100);
   mySerial.println("AT + CMGS = \"+2547xxxxxxxx\"\r");      //text NEMA officials 
  delay(100);
  mySerial.println("This industry is polluting the environment. Reading="); 
  delay(100);
   mySerial.println(sensorvalue); 
  delay(100);
  mySerial.println((char)26); 
  delay(100);
  
  mySerial.print("AT+CMGF=1\r"); 
  delay(100);
   mySerial.println("AT + CMGS = \"+2547xxxxxxxx\"\r");     //texts the industrial manager
  delay(100);
  mySerial.println("Your industrial process is emitting poisonous gases. Reading="); 
  delay(100);
   mySerial.println(sensorvalue); 
  delay(100);
  mySerial.println(sensorvalue); 
  delay(100);
  mySerial.println((char)26); 
  delay(100);
  
  Serial.println("pollution alert!!!!"); 
  delay(100);
  }
 else{
  Serial.println("No pollution");
  digitalWrite(buzzer,LOW);
   delay(100);
   digitalWrite(greenLED, HIGH) ;
   delay(100);
    digitalWrite(redLED, LOW) ;
   delay(100);
 
  }

}
void server(){
  unsigned long currentMillis=millis();
  if (currentMillis-previousMillis>=interval){
    previousMillis=currentMillis;
    if(timetosend==LOW) {
      timetosend=HIGH;
      if(Sentdata<2){
        mySerial.print("AT+CMGF=1\r"); //set to text mode
        delay (200);
                mySerial.print("AT + CMGS =\"+2547xxxxxxxx\"r"); //phone number to send to.
                delay(100);
                mySerial.print(reading);
                delay(200);
                mySerial.print((char)26);
      }
      Sentdata=+1;
    }
    else{
      timetosend=LOW;
      }
      digitalWrite(commled, timetosend);
    }
  }
  

