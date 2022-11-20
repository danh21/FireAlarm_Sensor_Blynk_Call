#include <SoftwareSerial.h>
SoftwareSerial sim(2, 3); 
String RxBuffer; 


void setup() {
  Serial.begin(9600);   
  sim.begin(9600);
  delay(1000);
}


void loop() {
  RxBuffer = Serial.readString();
  //Serial.println(RxBuffer);
  if (RxBuffer == "warning") {
    sim.println("ATD0773012284;"); 
    //updateSerial();
    delay(20000); 
    sim.println("ATH"); //hang up
    //updateSerial();
  }   
}


//void updateSerial() {
//  delay(500);
//  while (Serial.available()) 
//  {
//    sim.write(Serial.read());//Forward what Serial received to Software Serial Port
//  }
//  while(sim.available()) 
//  {
//    Serial.write(sim.read());//Forward what Software Serial received to Serial Port
//  }
//}
