#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <FirebaseESP8266.h>
#include <SoftwareSerial.h>

#define BLYNK_PRINT Serial
BlynkTimer timer;
char auth[] = "yourAuthTokenOfBlynk";
char ssid[] = "yourWifi";
char pass[] = "yourPass";
#define FIREBASE_HOST "yourLinkFirebase"
#define FIREBASE_AUTH "yourAuthOfFirebase" //Project settings -> Service accounts -> Database secrets -> Show
FirebaseData fbdo;
#define Rx 3
#define Tx 1
SoftwareSerial nodeMCU(Rx, Tx);

  
int redLed1 = 14;   //gasSensor
int redLed2 = 4;    //flameSensor
int greenLed = 15; 
int buzzer1 = 13;   //gasSensor
int buzzer2 = 5;    //flameSensor
int gasPin = A0;
int flamePin = 2;
int gasSensor;
int flameSensor;
int gasSensorThres = 600;

  
void setup() {
  pinMode(redLed1, OUTPUT);  
  pinMode(redLed2, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(gasPin, INPUT);
  pinMode(flamePin, INPUT);
  WiFi.begin (ssid, pass);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.begin(9600);
  nodeMCU.begin(9600);
  delay(5000);
  if (WiFi.status() == WL_CONNECTED)
    Blynk.begin(auth, ssid, pass);  
  timer.setInterval(1000L, sendUptime);
}


void sendUptime() {
  Blynk.virtualWrite(V0, flameSensor);
  Blynk.virtualWrite(V1, gasSensor);
}


void loop() {
  Blynk.run();
  timer.run();
  
  gasSensor = analogRead(gasPin);
  flameSensor = digitalRead(flamePin);
  
  if (gasSensor > gasSensorThres  && flameSensor==LOW) {
    nodeMCU.write("warning"); 
    digitalWrite(redLed1, HIGH);
    tone(buzzer1, 5000); 
    digitalWrite(redLed2, HIGH);
    tone(buzzer2, 5000); 
    digitalWrite(greenLed, LOW);
    delay(1000);   
  }
   else if (gasSensor > gasSensorThres) {
    digitalWrite(redLed1, HIGH);
    tone(buzzer1, 5000); 
    digitalWrite(redLed2, LOW);
    noTone(buzzer2);
    digitalWrite(greenLed, LOW);
  }
  else if (flameSensor==LOW) { 
    digitalWrite(redLed1, LOW);
    noTone(buzzer1);
    digitalWrite(redLed2, HIGH);
    tone(buzzer2, 5000);
    digitalWrite(greenLed, LOW);
  }
  else {
    digitalWrite(redLed1, LOW);
    digitalWrite(redLed2, LOW);
    noTone(buzzer1);
    noTone(buzzer2);
    digitalWrite(greenLed, HIGH);    
  }

  Firebase.setFloat(fbdo, "gasSensor", gasSensor);
  Firebase.setFloat (fbdo, "flameSensor", flameSensor);
}
