#include <Arduino.h>
#include <PCF8574.h> // PCF8574

// Define the PCF8574 devices ( you can have up to 8 on a bus )
// but in this case, my LCD uses address 0x27, so I will have a 
// conflicting address if I were to use 8 of them together with the
// LCD

PCF8574 Remote_1(0x23); 
//PCF8574 Remote_2(0x23);

// Note the I2C addresses. You can obtain them from the i2c_scanner

bool initI2Cbus(){

  
  // Set the initial state of the pins on the PCF8574 devices
  // I found that the PCF8574 library sometimes does funny things
  // This is also an example of how to use native i2c to set the 
  // status of the pins
  
  
  Wire.beginTransmission(0x23); // device 1
  Wire.write(0x00); // all ports off
  Wire.endTransmission();
 // Wire.begin(D6,D5);
  //Wire.beginTransmission(0x21); // device 2
  //Wire.write(0x00); // all ports off
  //Wire.endTransmission();
  // Set pinModes for PCF8574 devices
  // Note that there are two of them

  Remote_1.pinMode(P0,INPUT);
  Remote_1.pinMode(P1,INPUT);
//   Remote_2.pinMode(P0,OUTPUT);
//   Remote_2.pinMode(P1,OUTPUT);
  
  // Start both IO extenders

  //Remote_1.begin();
  //Remote_2.begin();

  // and set ports to low on both
  // you may find that if you ommit this step, they come up in an
  // unstable state.

//   Remote_1.digitalWrite(P0,LOW);
//   Remote_1.digitalWrite(P1,LOW);
//   Remote_2.digitalWrite(P0,LOW);
//   Remote_2.digitalWrite(P1,LOW);
return true;
}