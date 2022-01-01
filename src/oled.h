
#include <Adafruit_GFX.h>     // for OLED display
#include <Adafruit_SSD1306.h> // for OLED display
#include <Adafruit_I2CDevice.h>
#include <header.h>
#define OLED_WIDTH 128
#define OLED_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

bool initOled()
{
  bool state;
  // Start OLED Display Init

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false))
  { // Init the OLED
    Serial.println(F("OLED INIT FAILED"));
    state = false;
    // for(;;); // Dont proceed ... loop forever//
  }
  else
  {
    oled.setRotation(2);
    oled.clearDisplay();
    oled.setTextSize(0);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 0);
    oled.println("TEST SCREEN");
    oled.display();
    state = true;
  }
  return state;
}

void oprint(String var)
{
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.println(var);
  oled.display();
}

void handleMenu()
{
  if (ButtonVal == HIGH)
  {
    oprint("Menu");
    timers.updateInterval(2,0);
  }
  else
  {
    timers.updateInterval(2,450);
    //oprint("Application");



  }
  delay(50);
}

void drawSter(int val1, int val2, String direct, String acc, int brake)
{ // PRINT KNOBS ON OLED
  oled.clearDisplay();
  oled.setCursor(0, 10);
  oled.print(direct);

  // Print BRAKE
  oled.setCursor(20, 40);
  oled.print(brake);
  oled.setCursor(40, 10);
  oled.print(acc);
  oled.setCursor(0, 20);
  oled.print(val1);
  oled.setCursor(40, 20);
  oled.print(val2);
  oled.display();
}
