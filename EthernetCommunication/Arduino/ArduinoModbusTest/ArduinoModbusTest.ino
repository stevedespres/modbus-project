/*
  Modbus-Arduino Example - TempSensor (Modbus IP)
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino
*/
 
#include <SPI.h>
#include <Ethernet.h>
#include <Modbus.h>
#include <ModbusIP.h>


// Modbus Registers Offsets (0-9999)
const int HREG_1 = 200;
const int HREG_2 = 400;

//Used Pins
const int sensorPin = A0;

//ModbusIP object
ModbusIP mb;

long ts;


void setup() {

    Serial.begin(9600);      // open the serial port at 9600 bps:  
  
    // The media access control (ethernet hardware) address for the shield
    byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x5C, 0x08 };  
    // The IP address for the shield
    byte ip[] = { 192, 168, 0, 146 };   
    //Config Modbus IP 
    mb.config(mac, ip);
   // Add 2 Holding register
   //register 1
    mb.addHreg(HREG_1);
    //register 2
    mb.addHreg(HREG_2);

    digitalWrite(A0, LOW);
    digitalWrite(A0, INPUT_PULLUP);  // set pullup on analog pin 0 
	//Output 9 = LED
    pinMode(9, OUTPUT);
   
 
    ts = millis();
}

void loop() {


   //Call once inside loop() - all magic here
   mb.task();
  
  //Read the average of the last values of potentiometer [0 - 1024] provided by the Raspberry in the register 2
  //And use this value for the LED
   analogWrite(9, (mb.Hreg(HREG_2)/4) );

   //Read each 500ms
   if (millis() > ts +500 ) {   
       ts = millis();
       
       //Add the values of potentiometer in the register 1
       mb.Hreg(HREG_1, analogRead(sensorPin));

       Serial.print("\val = ");
       Serial.print(analogRead(sensorPin));
       Serial.print("\naverage = ");
       Serial.print(mb.Hreg(HREG_2));
       Serial.print("\n");
      
   } 
}

