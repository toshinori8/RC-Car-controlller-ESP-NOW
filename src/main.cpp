#include <streamFlow.h>
#include <SPI.h>
#include <header.h>
#include <Timers.h>
#include "PCF8574.h"
extern "C" {
  #include <espnow.h>
} 

uint8_t ButtonVal;
PCF8574 pcf8574(0x25, 14, 12);

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

  bool parkingLights;
  bool turnSignals_auto;
  bool headlights;
  bool searchLights;
  bool autoOffLights;
  bool rearDoor;

} sensorData;



void updateOptions(){
  /// CAR OPTIONS
  sensorData.parkingLights = OparkingLights;
  sensorData.turnSignals_auto = OturnSignals_auto;
  sensorData.headlights = Oheadlights;
  sensorData.autoOffLights = OautoOffLights;
  sensorData.rearDoor = OrearDoor;

}
void updateData(int ster, int drive, String dirDrive, String dirSter, int POT)
{
  // CAR STERING DATA
  sensorData.pot = POT;
  sensorData.ster = ster;
  sensorData.drive = drive;
  sensorData.dirDrive = dirDrive;
  sensorData.dirSter = dirSter;

 

  //Serial.println(sensorData.pot);
 uint8_t bs[sizeof(sensorData)];
  memcpy(bs, &sensorData, sizeof(sensorData));
  esp_now_send(remoteMac, bs, sizeof(sensorData)); // NULL means send to all peers

}

// I2C device found at address 0x25  !  PCF8574
// I2C device found at address 0x3C  !  OLED

Timers<3> timers;

// U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 12, /* data=*/ 14, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
// U8GLIB_SSD1306_128X32 u8g2(U8G_I2C_OPT_NONE);	// I2C / TWI

void setup()
{
  Serial.begin(115200);

  delay(1000);
  initI2Cbus();

  timers.attach(0, 350, handleMenu);
  timers.attach(1, 100, handleButton);
  timers.attach(2, 0, readTurn);

  initOled();

  delay(1000);

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
    Serial.println("*** ESP_Now init failed");
   
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
}



void handleButton()
      {
        ButtonVal = pcf8574.digitalRead(0);
      }

#include <oled.h>