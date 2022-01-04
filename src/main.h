#ifndef MAIN_H
#define MAIN_H
 //#pragma once

//#define OTA_
//#define WIFI_
#define ESPNOW_





bool initI2Cbus();
void wifiStart();
void otaStart();
void esp_nowStart();
void digitalReadN();
bool initOled();
void handleMenu();

void handleButton();
// READING POTS / DISPLAY & SEND
extern void updateData(int ster, int drive, String dirDrive, String dirSter, int POT); // ESP-NOW PREPARE DATA & SEND

extern void readTurn();
extern void updateOptions();



extern bool OparkingLights;
extern bool OturnSignals_auto;
extern bool Oheadlights;
extern bool OautoOffLights;
extern bool OrearDoor;

extern int pos;
extern bool menustate;
#endif // MAIN

