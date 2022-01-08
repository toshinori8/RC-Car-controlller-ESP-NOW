#include <Adafruit_GFX.h>     // for OLED display
#include <Adafruit_SSD1306.h> // for OLED display
#include <Adafruit_I2CDevice.h>
#include "oled.h"
#include <U8g2lib.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/Lato_Medium_9.h>
#include <Fonts/icons.h>

Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

#define MENU_SIZE 6 - 1

Opcje opcje; // Define MENU class with struct

bool initOled()
{
  bool state;
  // Start OLED Display Init

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false))
  { // Init the OLED
    Serial.println(F("OLED INIT FAILED"));
    state = false;
  }
  else
  {
    u8g2.begin();
    u8g2.enableUTF8Print();

    oled.setRotation(0);
    oled.clearDisplay();
    oled.setTextSize(0);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 0);

    oled.display();
    state = true;
  }

  ///  DEFINE MENU ITEMS

  opcje.item[0].ind = 0;
  opcje.item[0].type = "bool";
  opcje.item[0].name = "Sw. drogowe";
  opcje.item[0].desc = "Dlugie";
  opcje.item[0].value = false;

  opcje.item[1].ind = 1;
  opcje.item[1].type = "bool";
  opcje.item[1].name = "Sw mijania";
  opcje.item[1].desc = "Krotkie";
  opcje.item[1].value = false;

  opcje.item[2].ind = 2;
  opcje.item[2].type = "bool";
  opcje.item[2].name = "Halogeny";
  opcje.item[2].desc = "Szperacze na masce";
  opcje.item[2].value = false;

  opcje.item[3].ind = 3;
  opcje.item[3].type = "bool";
  opcje.item[3].name = "Migacze auto";
  opcje.item[3].desc = "Autom. przy skrecaniu";
  opcje.item[3].value = true;

  opcje.item[4].ind = 4;
  opcje.item[4].type = "bool";
  opcje.item[4].name = "Alarm";
  opcje.item[4].desc = "Wzbudz alarm";
  opcje.item[4].value = false;

  opcje.item[5].ind = 5;
  opcje.item[5].type = "bool";
  opcje.item[5].name = "Awaryjne";
  opcje.item[5].desc = "Światła awaryjne";
  opcje.item[5].value = false;

  opcje.item[6].ind = 6;
  opcje.item[6].type = "bool";
  opcje.item[6].name = "Auto OFF";
  opcje.item[6].desc = "Wyłączenie świateł po 30s";
  opcje.item[6].value = true;
  return state;
}

// helper debug function for oled
void oprint(String var)
{
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.println(var);
  oled.display();
}

void drawSter(int val1, int val2, String direct, String acc, int brake)
{
  u8g2.setContrast(0); // optional brightnes low
  u8g2.setDisplayRotation(U8G2_R0);

  // PRINT KNOBS ON OLED
  u8g2.setFont(u8g2_font_amstrad_cpc_extended_8f);

  // Serial.println(O_long_lights);
  // Serial.println(O_short_lights);
  // Serial.println(O_turn_lights);
  // Serial.println(O_error_lights);
  // Serial.println(battery_low);
  // Serial.println(O_long_lights);
  // Serial.println(O_long_lights);

  // CLEAR ICONS ARREA
  u8g2.setDrawColor(BLACK);
  u8g2.drawBox(45, 0, 90, 32);

  u8g2.setDrawColor(WHITE);
  u8g2.drawBox(45, 0, 1, 32);

  // Display icons
  if (O_long_lights == 1)
  {
    u8g2.drawBitmap(70, -2, 2, 16, lights);
  }
  if (O_short_lights == 1)
  {
    u8g2.drawBitmap(70, -2, 2, 16, low_lights);
  }
  if (O_turn_lights == 1)
  {
    u8g2.drawBitmap(70, 18, 2, 16, turn_lights);
  }
  if (O_error_lights == 1)
  {
    u8g2.drawBitmap(93, 17, 2, 16, allert);
  }
  if (battery_low == 1)
  {
    u8g2.drawBitmap(113, 18, 2, 16, battery);
  }

  // Print Forward / Backward
  u8g2.setCursor(0, 20);
  u8g2.print("      ");
  u8g2.setCursor(0, 20);
  u8g2.print(acc);

  // Print Left / Right
  u8g2.setCursor(20, 20);
  u8g2.print(direct);

  // Print value of acceleration
  //u8g2.setCursor(30, 11);
  //u8g2.print(val1);

  // Print value of left right turn
  //u8g2.setCursor(30, 11);
  //u8g2.print(val2);

  // u8g2.setCursor(40, 30);
  // u8g2.print("łucja");		// Chinese "Hello World"
  u8g2.sendBuffer();
}

void displayMenu(String comm)
{

  if (comm == "start")
  {
    menustate = 1;
  }

  if (comm == ">")
  {
    pos++;
    if (pos == MENU_SIZE + 1)
    {
      pos = 0;
    };
  }
  if (comm == "<")
  {
    pos--;
    if (pos == -1)
    {
      pos = MENU_SIZE - 1;
    };
  }

  oled.setFont(&FreeSans9pt7b);
  oled.clearDisplay();

  if (comm == "start")
  {
    pos = 0;
  };

  oled.setCursor(5, 15);
  oled.print(opcje.item[pos].name);

  // TRIGGER EXIT ACCTION
  if (comm == "exit")
  {
    menustate = 0;
  }
  // TRIGGER CHANGE BUTTON ACCTION
  if (comm == "x" & opcje.item[pos].type == "bool")
  {
    // CHANGE OPTION
    opcje.item[pos].value = !opcje.item[pos].value;

    // SET CHANGES
    if (opcje.item[pos].ind == 0)
    {
      O_long_lights = opcje.item[pos].value;
    }
    if (opcje.item[pos].ind == 1)
    {
      O_short_lights = opcje.item[pos].value;
    }
    if (opcje.item[pos].ind == 2)
    {
      O_haloo_lights = opcje.item[pos].value;
    }
    if (opcje.item[pos].ind == 3)
    {
      O_turn_lights = opcje.item[pos].value;
    }
    if (opcje.item[pos].ind == 4)
    {
      O_alarm_lights = opcje.item[pos].value;
    }
    if (opcje.item[pos].ind == 5)
    {
      O_error_lights = opcje.item[pos].value;
    }
    if (opcje.item[pos].ind == 6)
    {
      O_autoOff_lights = opcje.item[pos].value;
    }

    // DISPLAY CHANGES  "|" character before option
    oled.setCursor(0, 15);
    String op = (opcje.item[pos].value == true) ? "|" : "";

    oled.print(op);
    oled.display();
  }
  else
  {

    /// PRINT ACTUAL MENU
    oled.clearDisplay();
    oled.setCursor(0, 15);

    /// PRINT ACTUAL MENU ITEM VALUE
    String opt = (opcje.item[pos].value == true) ? "|" : "";
    oled.print(opt);
    
    /// PRINT MENU ITEM NAME
    oled.setCursor(5, 15);
    oled.print(opcje.item[pos].name);

    /// PRINT DESCRIPTION
    oled.setFont(&Lato_Medium_9);
    oled.setCursor(5, 26);
    oled.print(opcje.item[pos].desc);
    
    oled.display();
  }
}
