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
    sim.println("ATD----------;");  // type your call number
    delay(20000); 
    sim.println("ATH"); //hang up
  }   
}
