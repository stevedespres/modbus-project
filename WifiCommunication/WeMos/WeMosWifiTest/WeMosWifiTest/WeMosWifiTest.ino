/*
  Modbus-Arduino Example - Test Holding Register (Modbus IP ESP8266)
  Configure Holding Register (offset 100) with initial value 0xABCD
  You can get or set this holding register
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino
*/
//Librairies
#include <ESP8266WiFi.h>
#include <Modbus.h>
#include <ModbusIP_ESP8266.h>

// Modbus Registers Offsets (0-9999)
const int HREG_1 = 200;
const int HREG_2 = 400;

//Used Pins
const int sensorPin = A0;
const int outputPin = D7;

//ModbusIP object
ModbusIP mb;

//Time
long ts;
  
void setup() {
  //Serial config
  Serial.begin(115200);
  //Connection
  mb.config("RPi2_Test", "raspberry");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  //register 1
  mb.addHreg(HREG_1);
  //register 2
  mb.addHreg(HREG_2);

  //Input
  digitalWrite(sensorPin, LOW);
  digitalWrite(sensorPin, INPUT_PULLUP);  // set pullup on analog pin 0 
  //Output
  pinMode(outputPin, OUTPUT);
  //Take time
  ts = millis();

}
 
void loop() {
  
   //Call once inside loop() - all magic here
   mb.task();

   //Read the average of the last values of potentiometer [0 - 1024] provided by the Raspberry in the register 2
  //And use this value for the LED
   analogWrite(outputPin, (mb.Hreg(HREG_2)/4) );

    
    if (millis() > ts +500 ) {   
       ts = millis();
       
       //Add the values of potentiometer in the register 1
       mb.Hreg(HREG_1, analogRead(sensorPin));
       //Display
       Serial.print("\nval = ");
       Serial.print(analogRead(sensorPin));
       Serial.print("\naverage = ");
       Serial.print(mb.Hreg(HREG_2));
       Serial.print("\n");
      
   } 

}

