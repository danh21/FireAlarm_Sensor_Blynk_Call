# Project: FireAlarm_Sensor_Blynk_Call

# Description:
This project is one of subjects at my university and relates to IoT. The system uses 2 sensors (flame sensor and gas sensor) to collect data from the environment. If data exceeds the threshold, ESP8266 will send data to app Blynk for notification, Arduino UNO communicates with Module SIM800L to make a call to user, led and buzzer are actived at the same time.

# Hardware:
    - Arduino UNO (or other modules which have UART standard to connect to Module Sim and Module ESP).
    - ESP8266 (or other modules which can connect to Internet and connect to central microcontroller by UART standard).
    - Module SIM800L (or other modules which can use SIM to make a call).
    - LM393 Flame Sensor (or other sensors which can detect fire).
    - MQ-2 Gas Sensor (or other sensors which can measure gas concentration).
    - Buzzer and Led (alert to the user directly).
    - Module Buck DC-DC LM2596-3A (because Module SIM uses voltage supply from  3.7V - 4.2V, so use this module to decrease voltage for avoiding damaging module).
    - Supply (rechargeable battery backup)

# Connection:
    - Arduino UNO:
        + 5V    -   IN+ (LM2596)
        + GND   -   IN-, OUT- (LM2596) ; GND (SIM800L, ESP8266)
        + D2    -   TX (SIM800L)
        + D3    -   10Kohm  -   RX (SIM800L)    -   20Kohm  -   GND
        + TX    -   RX (ESP8266)
        + RX    -   TX (ESP8266)
    - ESP8266:
        + Vin   -   VCC (sensors)
        + GND   -   GND (UNO, sensors) ; Cathode (leds) ; [-] (buzzer)
        + A0    -   A0 (MQ-2)
        + D4    -   D0 (LM393)
        + D8    -   Anode (green led)
        + D5    -   Anode (red led for gas)
        + D2    -   Anode (red led for flame)
        + D7    -   [+] (buzzer for gas)
        + D1    -   [+] (buzzer for flame)
        + TX    -   RX (UNO)
        + RX    -   TX (UNO)
    - SIM800L:
        + VCC   -   1000uF capacitor    -   GND

# Software:
    - Arduino IDE (programming for microcontroller UNO and ESP8266).
    - Firebase (store data, you can create database yourself as Firebase Interface.JPG, you have to edit rules to TRUE).
    - Blynk (I use old version of Blynk in Android, more detail about building interface of app at Blynk_Init.doc).

# Code:
    - main_ESP (upload to ESP8266):
        + Modify Wifi (ssid, pass)
        + Modify Blynk (auth token from your gmail when creating project)
        + Modify Firebase: 
            . Link: Realtime Database
            . Auth token: Project settings (click on Gear Icon which is next to Project Overview) -> Service accounts -> Database secrets -> Show
    - main_UNO (upload to Arduino UNO):
        + Modify call number: 
            . In code: sim.println("ATD----------;");
            . Need to replace "----------" to your call number 

# Bonus:
    - Diagram
    - Flowchart
    - Demo: https://www.youtube.com/watch?v=pXxnN6nfYBY