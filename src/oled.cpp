#include <Arduino.h>



bool void initOled(){

bool state;
// Start OLED Display Init

  if (!oled.begin(SSD1306_SWITCHCAPVCC,0x3C,false,false)) { // Init the OLED 
    Serial.println(F("OLED INIT FAILED"));
    state = false;
   // for(;;); // Dont proceed ... loop forever//
  }else{

    delay(2000); 
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