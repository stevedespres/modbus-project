# ModbusProject
Modbus communication between Arduino Uno and Raspberry Pi 2 (Ethernet + WIFI)

*****READ ModbusCommunication.pdf TO HAVE THE FULL DESCRIPTION OF THIS PROJECT *****


I'm french student and I worked on this project during an internship. 
This project allows to create a modbus communication between Arduino Uno and Raspberry Pi 2, using a switch and ethernet cables and then using a WIFI hotspot. 

The application is an example, the Arduino (server) writes the value of a sensor in a modbus register 1 (holding register) each 500ms.
The Raspberry Pi 2 (client) reads this value, in the modbus register 1,  and stocks all of them in a table and .csv file, then it calculates the average. 
The Raspberry writes the value of the average in a modbus register 2.
The Arduino Uno reads the value of the average and send it to power on a LED.

If you have any question, please contact me : stevedp(a)live(dot)fr
