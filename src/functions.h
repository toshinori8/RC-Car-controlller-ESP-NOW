#include <Arduino.h>
#include <oled.h>


void oprint(String var){

 oled.clearDisplay();
 oled.setCursor(0,0); 
 oled.println(var);
 oled.display();

}