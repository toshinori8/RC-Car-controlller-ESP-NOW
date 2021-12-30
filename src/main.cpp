/*
  Multiple devices on the I2C bus
  Maker and Iot Ideas, MakerIoT2020
*/
// Include the libraries that we will need
#include <SPI.h> // needed for OLED display. 
#include <PCF8574.h> // PCF8574
#include <Wire.h> // Generic I2C library
#include <Adafruit_GFX.h> // for OLED display
#include <Adafruit_SSD1306.h> // for OLED display
#include <Adafruit_I2CDevice.h>


// I2C device found at address 0x23  !  PCF8574
// I2C device found at address 0x3C  !  OLED  

// we need to define the size of the OLED screen

#define OLED_WIDTH 128
#define OLED_HEIGHT 32

// mine does not have an onboard reset pin. If yours do, specify the 
// pin that it is connected to on the Arduino here. To use the 
// Arduino reset pin, specify -1 as below

#define OLED_RESET -1

// Define the OLED display, width,hight protocol and reset pin
Adafruit_SSD1306 oled(OLED_WIDTH,OLED_HEIGHT, &Wire, OLED_RESET);



// Define the PCF8574 devices ( you can have up to 8 on a bus )
// but in this case, my LCD uses address 0x27, so I will have a 
// conflicting address if I were to use 8 of them together with the
// LCD

//PCF8574 Remote_1(0x20); 
//PCF8574 Remote_2(0x23);

// Note the I2C addresses. You can obtain them from the i2c_scanner

void setup() {
    Wire.begin(14,12);

    
  // serial debugging if needed
  Serial.begin(115200);
  // Start OLED Display Init

  if (!oled.begin(SSD1306_SWITCHCAPVCC,0x3C,false,false)) { // Init the OLED 
    Serial.println(F("OLED INIT FAILED"));
   // for(;;); // Dont proceed ... loop forever//
  }else{

Serial.println(F("OLED INIT XXXXXXXXX"));

  }
//   oled.display();
  delay(2000); // This delay is required to give display time to 
  // initialise properly
   oled.clearDisplay();
  oled.setTextSize(0);
  oled.setTextColor(SSD1306_WHITE);
   oled.setCursor(0,0);
  oled.println("TEST SCREEN");
  oled.display();
  delay(2000);
//   oled.clearDisplay();
//   oled.setCursor(1,0);
   
   // oled.println("OLED SCREEN ON");
 // oled.display();

  // Start the LCD

  
  
  // Set the initial state of the pins on the PCF8574 devices
  // I found that the PCF8574 library sometimes does funny things
  // This is also an example of how to use native i2c to set the 
  // status of the pins
  
  
  //Wire.beginTransmission(0x20); // device 1
  //Wire.write(0x00); // all ports off
  //Wire.endTransmission();
  //Wire.begin(D6,D5);
  //Wire.beginTransmission(0x21); // device 2
  //Wire.write(0x00); // all ports off
  //Wire.endTransmission();
  // Set pinModes for PCF8574 devices
  // Note that there are two of them

//   Remote_1.pinMode(P0,OUTPUT);
//   Remote_1.pinMode(P1,OUTPUT);
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
  
}

void loop() {

Serial.println(F("OLED INIT DONE"));
  // Write to the IO extenders

//   Remote_1.digitalWrite(P0,HIGH);
//   Remote_1.digitalWrite(P1,LOW);
//   Remote_2.digitalWrite(P0,HIGH);
//   Remote_2.digitalWrite(P1,LOW);
  
  // Display their status on the LCD
//   oled.setCursor(0,0);
//   oled.print(" R1 P0=1 P1=0");
//   oled.setCursor(0,1);
//   oled.print(" R2 P0=1 P1=0");
//   delay(500);

  // Change status
//   Remote_1.digitalWrite(P1,HIGH);
//   Remote_1.digitalWrite(P0,LOW);
//   Remote_2.digitalWrite(P1,HIGH);
//   Remote_2.digitalWrite(P0,LOW);

  // Update LCD
//   oled.setCursor(0,0);
//   oled.print(" R1 P0=0 P1=1");
//   oled.setCursor(0,1);
//   oled.print(" R2 P0=0 P1=1");
//   delay(500);
  // Do some graphics on the OLED display
  // Function borrowed from Adafruit
 
//   oled.clearDisplay();
//   delay(500);
  // repeat indefinitely

}




