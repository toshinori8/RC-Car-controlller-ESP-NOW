#pragma once

//#define OTA_
//#define WIFI_
#define ESPNOW_

  uint8_t remoteMac[] = {0xCC, 0x50, 0xE3, 0x56, 0xB7, 0x36};
  #define WIFI_CHANNEL 12


bool initI2Cbus();
void wifiStart();
void otaStart();
void esp_nowStart();
void digitalReadN();
void oprint(String var);
bool initOled();
void handleMenu();
void handleButton();
// READING POTS / DISPLAY & SEND
void updateData(int ster, int drive, String dirDrive, String dirSter, int POT); // ESP-NOW PREPARE DATA & SEND
void drawSter(int val1, int val2, String direct, String acc, int brake);
void readTurn();
void updateOptions();



// car options

bool OparkingLights;
bool OturnSignals_auto;
bool Oheadlights;
bool OsearchLights;
bool OautoOffLights;
bool OrearDoor;


