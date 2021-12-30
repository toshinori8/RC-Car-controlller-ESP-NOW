#include <SPI.h>  // needed for OLED display.
#include <Wire.h> // Generic I2C library
#include <streamFlow.h>
#include <Timers.h>
#define OTA
#define WIFION
#define ESPNOW

// I2C device found at address 0x23  !  PCF8574
// I2C device found at address 0x3C  !  OLED

Timers<2> timers;
bool initOled();
bool initI2Cbus();
void otaStart();
void esp_now();
void digitalReadN();


// U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 12, /* data=*/ 14, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
// U8GLIB_SSD1306_128X32 u8g2(U8G_I2C_OPT_NONE);	// I2C / TWI

void setup()
{
  Wire.begin(14, 12);
  Serial.begin(115200);
  timers.attach(0, 150, digitalReadN);
  initOled();
  initI2Cbus();


  #if (defined(WIFI_))
  otaStart();
  #endif
}

void loop()
{
  timers.process();
  Serial.println(F("OLED INIT DONE"));
  // ArduinoOTA.handle();

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
