#ifndef MAIN_H
#define MAIN_H

//#define OTA_
//#define WIFI_
#define ESPNOW_

extern int Pin_A; // analog INPUT POWER SOURCE #1
extern int Pin_B; // analog INPUT POWER SOURCE #2

bool initI2Cbus(); 
void wifiStart();
void otaStart();
void esp_nowStart();
void digitalReadN();
bool initOled();
void handleMenu();

// UPDATE ESP-NOW STRUCT
extern void updateData(int ster, int drive, String dirDrive, String dirSter, int POT); // ESP-NOW PREPARE DATA & SEND

// READING POTS / DISPLAY & SEND
extern void readTurn(); 

extern bool battery_low;

// Global OPTIONS variables for ESP-NOW struct
extern bool O_short_lights;
extern bool O_long_lights;
extern bool O_haloo_lights;
extern bool O_turn_lights;
extern bool O_alarm_lights;
extern bool O_error_lights;
extern bool O_autoOff_lights;

// Menu variables
extern int pos;
extern bool menustate;



#endif // MAIN

