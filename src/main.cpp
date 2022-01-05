#include <streamFlow.h>
#include <SPI.h>
#include <main.h>
#include <Timers.h>
#include "PCF8574.h"
#include <Adafruit_GFX.h>     // for OLED display
#include <Adafruit_SSD1306.h> // for OLED display
#include <Adafruit_I2CDevice.h>
byte incomingByte;
extern "C" {
  #include <espnow.h>
} 
#include "main.h"

#include "menu.h"
#include "oled.h"
#include "readPots.h"

uint8_t remoteMac[] = {0xCC, 0x50, 0xE3, 0x56, 0xB7, 0x36};
#define WIFI_CHANNEL 12
int ButtonVal;


int pos = -1;
bool menustate=0;

int Pin_A = 5; 
int Pin_B = 4; 

bool battery_low=false;

// init options
bool O_short_lights;
bool O_long_lights;
bool O_haloo_lights;
bool O_autoOff_lights;
bool O_turn_lights;
bool O_alarm_lights;
bool O_error_lights;


PCF8574 pcf8574(0x25, 14, 12);;



bool initI2Cbus()
{

  pcf8574.pinMode(0, INPUT);
  pcf8574.pinMode(1, OUTPUT);
  pcf8574.digitalWrite(0, LOW);
  pcf8574.digitalWrite(1, HIGH);
  pcf8574.digitalWrite(2, LOW);

  delay(1000);
  Serial.print("Init pcf8574...");
  if (pcf8574.begin())
  {
    Serial.println("OK");
    return true;
  }
  else
  {
    Serial.println("NOT OK");
    return false;
  }

  delay(1000);
}

struct __attribute__((packed)) dataStruct
{
  // CAR STERING DATA

  int pot;
  int drive;
  int ster;
  String dirDrive;
  String dirSter;

  /// CAR OPTIONS

  bool short_lights;
  bool long_lights;
  bool haloo_lights;
  bool autoOff_lights;
  bool turn_lights;
  bool alarm_lights;
  bool error_lights;

} sensorData;





void updateData(int ster, int drive, String dirDrive, String dirSter, int POT)
{ 

  // OPTIONS
  sensorData.short_lights = O_short_lights;
  sensorData.long_lights = O_long_lights;
  sensorData.haloo_lights = O_haloo_lights;
  sensorData.autoOff_lights = O_autoOff_lights;
  sensorData.turn_lights = O_turn_lights;
  sensorData.alarm_lights = O_alarm_lights;
  sensorData.error_lights = O_error_lights;


  // CAR STERING DATA
  sensorData.pot = POT;
  sensorData.ster = ster;
  sensorData.drive = drive;
  sensorData.dirDrive = dirDrive;
  sensorData.dirSter = dirSter;

  uint8_t bs[sizeof(sensorData)];
  memcpy(bs, &sensorData, sizeof(sensorData));
  esp_now_send(remoteMac, bs, sizeof(sensorData)); // NULL means send to all peer
}

// I2C device found at address 0x25  !  PCF8574
// I2C device found at address 0x3C  !  OLED

Timers<4> timers;



// U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 12, /* data=*/ 14, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
// U8GLIB_SSD1306_128X32 u8g2(U8G_I2C_OPT_NONE);	// I2C / TWI

void setup()
{
  Serial.begin(115200);

  pinMode(Pin_A,OUTPUT);
  pinMode(Pin_B,OUTPUT);

  delay(1000); // delay for propper initialisation of expander
  initI2Cbus();
  delay(50);


  timers.attach(0, 250, handleMenu);       
  timers.attach(2, 0, readTurn);           // READ/SEND CONTROLLER POTS 
  timers.attach(3, 0, readTurn_encoder);   // READ MENU BUTTONS 

  initOled();                              // INIT MENU/GRAPHIC FUNCTIONS  

 // delay(1000);

      #if (defined(ESPNOW_))
      
      #endif
      #if (defined(WIFI_))
        wifiStart();
      #endif
      #if (defined(OTA_))
        otaStart();
      #endif

     // Init ESP-NOW
if (esp_now_init() != 0) {
    Serial.println("*** ESP_NOW init failed");
   
}

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(remoteMac, ESP_NOW_ROLE_SLAVE, WIFI_CHANNEL, NULL, 0);

  esp_now_register_send_cb([](uint8_t* mac, uint8_t sendStatus) {
   // Serial.printf("send_cb, send done, status = %i\n", sendStatus);
   
  });


}

void loop()
{
  timers.process();

        #if (defined(OTA_))
          ArduinoOTA.handle()
        #endif




while(Serial.available()) {

// input from serial console.  
Serial.println("Serial console input started");
Serial.println("----------------------------");
Serial.println("  ");
Serial.println("  ");
Serial.println(" [<] [>] SELECT menu option");
Serial.println("  ");
Serial.println("   [x]   CHANGE option");
Serial.println("  ");
Serial.println("   [e]   EXIT menu");



String a= Serial.readString();
if(a==">"){displayMenu(a);}
if(a=="<"){displayMenu(a);}
if (a.substring(0) == "x") 
  {
    displayMenu(a); // SEND CONSOLE COMMAND TO MENU IF VISIBLE
  } 
}




}





void handleMenu()
{
  ButtonVal = pcf8574.digitalRead(0);

  if (ButtonVal == 1) // 0
  {
    timers.updateInterval(3,80); // menu buttons update interval
    timers.updateInterval(2,0);   // 
    
   if(menustate==0){
        displayMenu("start");
   }  
    
 
  }
  if (ButtonVal == 0)   // 1 
   {
    menustate=0;
    timers.updateInterval(2,50); // READ POTS up
    timers.updateInterval(3,0); // disable menu buttons
  }
}

