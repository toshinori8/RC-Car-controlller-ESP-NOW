#ifndef READPOTS_H
#define READPOTS_H
#include <Arduino.h>



bool sw = false;
int turnVal1;
int turnVal2;
int mem1;
int mem2;
int maped1;
int maped2;
String dir;
String acc = "forward";
int value1;
int value2;
int brake = 0;

const int pot = 0;
int Pin_A = 5; // analog INPUT POWER SOURCE #1
int Pin_B = 4; // analog INPUT POWER SOURCE #2


void readTurn();



#endif // READPOTS_H