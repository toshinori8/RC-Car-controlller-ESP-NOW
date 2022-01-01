#include <Arduino.h>
#include <Wire.h>    // Required for I2C communication
#include "PCF8574.h" // Required for PCF8574
#include <header.h>



// Define the PCF8574 devices ( you can have up to 8 on a bus )
// but in this case, my LCD uses address 0x27, so I will have a 
// conflicting address if I were to use 8 of them together with the
// LCD


PCF8574 Remote_1(0x25);

// Note the I2C addresses. You can obtain them from the i2c_scanner

bool initI2Cbus(){

  // Set the initial state of the pins on the PCF8574 devices
  // I found that the PCF8574 library sometimes does funny things
  // This is also an example of how to use native i2c to set the 
  // status of the pins
  
  
  Wire.beginTransmission(0x25); // device 1
 /// Wire.write(0x00); // all ports off
  //Wire.endTransmission();

  // Set pinModes for PCF8574 devices
  // Note that there are two of them

  // Remote_1.pinMode(0,PULLUP);
 
  // Remote_1.write(0, LOW);
 

  Remote_1.pinMode(P0,INPUT_PULLUP);
  Remote_1.pinMode(P1,INPUT );
  // Start both IO extenders
  
  Remote_1.digitalWrite(P0,LOW);
   Remote_1.digitalWrite(P1,LOW);
  // and set ports to low on both
  // you may find that if you ommit this step, they come up in an
  // unstable state.

//   Remote_1.digitalWrite(P0,LOW);
//   Remote_1.digitalWrite(P1,LOW);

return true;
}


void digitalReadN(){


  Serial.println(Remote_1.digitalRead(0, true) ? "HIGH" : "LOW");
   Serial.println(Remote_1.digitalRead(1,true) ? "HIGH" : "LOW");
  //int p1=  Remote_1.digitalRead(P1);
   ///Remote_1.digitalWrite(P0,!p0);
    
  //Serial.println("digitalRead(0)");
  //Serial.print(p0);

  // Serial.println("digitalRead(P1)");
  // Serial.print(Remote_1.digitalRead(P1));
  if(Remote_1.digitalRead(0) ==HIGH){

    oprint("MENU");

  }else{

     oprint("STEER");

  }

//   Remote_1.digitalWrite(P1,LOW);


};