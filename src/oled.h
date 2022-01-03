#ifndef OLED_H
#define OLED_H

#include <Adafruit_GFX.h>     // for OLED display
#include <Adafruit_SSD1306.h> // for OLED display
#include <Adafruit_I2CDevice.h>


#define OLED_WIDTH 128
#define OLED_HEIGHT 32
#define OLED_RESET -1


bool initOled();
void oprint();
void drawSter(int val1, int val2, String direct, String acc, int brake);

Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

#endif // OLED_H