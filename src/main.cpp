#include <streamFlow.h>
#include <SPI.h>        // needed for OLED display.
// #include <Wire.h>    // Required for I2C communication
#include <header.h>
#include <Timers.h>
#include "PCF8574.h"
//#define OTA_
//#define WIFI_
//#define ESPNOW_
uint8_t ButtonVal;

PCF8574 pcf8574(0x25,14,12);



bool initI2Cbus(){

    pcf8574.pinMode(0, INPUT);
	  pcf8574.pinMode(1, OUTPUT);
    pcf8574.digitalWrite(0,LOW);
    pcf8574.digitalWrite(1,HIGH);
	  pcf8574.digitalWrite(2,LOW);

  delay(1000);
  Serial.print("Init pcf8574...");
	if (pcf8574.begin()){
		Serial.println("OK");
        return true;
	}else{
		Serial.println("NOT OK");
        return false;
	}

  delay(1000);


}


struct __attribute__((packed)) dataStruct {
  int pot;
  int drive;
  int ster;

  String dirDrive;
  String dirSter;

  
} sensorData;


void updateData(int ster, int drive,String dirDrive, String dirSter,int POT){
    sensorData.pot=POT;
    sensorData.ster=ster;
    sensorData.drive=drive;
    sensorData.dirDrive=dirDrive;
    sensorData.dirSter=dirSter;
    Serial.println(sensorData.pot);



 uint8_t bs[sizeof(sensorData)];

  memcpy(bs, &sensorData, sizeof(sensorData));

    #if defined(ESPNOW_)
    esp_now_send(remoteMac, bs, sizeof(sensorData)); // NULL means send to all peers
    #endif
  
  }


// I2C device found at address 0x25  !  PCF8574
// I2C device found at address 0x3C  !  OLED

Timers<3> timers;



// U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 12, /* data=*/ 14, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
// U8GLIB_SSD1306_128X32 u8g2(U8G_I2C_OPT_NONE);	// I2C / TWI

void setup()
{
  Serial.begin(115200);  
 // Wire.begin(14, 12);
 

  delay(1000);
  initI2Cbus();

  
  timers.attach(0, 350, handleMenu);
  timers.attach(1, 100, handleButton);
  timers.attach(2,  0, readTurn);



  initOled();

  delay(1000);

  #if (defined(ESPNOW_))
  esp_nowStart();
  #endif
  #if (defined(WIFI_))
  wifiStart();
  #endif
  #if (defined(OTA_))
  otaStart();
  #endif

}

void loop()
{
    timers.process();

#if (defined(OTA_))
ArduinoOTA.handle()
#endif

}
void handleButton(){
   ButtonVal = pcf8574.digitalRead(0);
}


#include <oled.h>