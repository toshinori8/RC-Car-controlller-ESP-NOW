#pragma once



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
void updateData(int ster, int drive,String dirDrive, String dirSter,int POT); //ESP-NOW PREPARE DATA & SEND  
void drawSter(int val1,int val2, String direct, String acc, int brake);
void readTurn();