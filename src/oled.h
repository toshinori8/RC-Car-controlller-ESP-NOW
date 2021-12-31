#include <Arduino.h>
#include <Adafruit_GFX.h> // for OLED display
#include <Adafruit_SSD1306.h> // for OLED display
#include <Adafruit_I2CDevice.h>



#define OLED_WIDTH 128
#define OLED_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 oled(OLED_WIDTH,OLED_HEIGHT, &Wire, OLED_RESET);


bool initOled(){

bool state;
// Start OLED Display Init

  if (!oled.begin(SSD1306_SWITCHCAPVCC,0x3C,false,false)) { // Init the OLED 
    Serial.println(F("OLED INIT FAILED"));
    state = false;
   // for(;;); // Dont proceed ... loop forever//
  }else{
    oled.setRotation(2);
    oled.clearDisplay();
    oled.setTextSize(0);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0,0);
    oled.println("TEST SCREEN");
    oled.display();

    state = true;
  }
return state;
}

