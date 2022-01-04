#ifndef OLED_H
#define OLED_H
#include <Arduino.h>

#include "main.h"


#define OLED_WIDTH 128
#define OLED_HEIGHT 32
#define OLED_RESET -1





bool initOled();
extern void oprint();
extern void drawSter(int val1, int val2, String direct, String acc, int brake);




class Opcje {
  public : int size;
  public: struct item
    {
      String type;
      String name;
      bool value;
      int sec;
      void (*func)(void);
    } item[10];

};

void changeParam(bool cur);
void displayMenu(String comm);







#endif // OLED_H