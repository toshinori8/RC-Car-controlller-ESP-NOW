#ifndef MENU_H
#define MENU_H


#include <Arduino.h>

#define MENU_SIZE 2
int pos = -1;

class Opcje {
  public : int size;
  public: struct item
    {
      String type;
      String name;
      bool value;
      int sec;
      void (*func)(void);
    } item[3];

};

int curMenu=0;
void changeParam(bool cur);
void displayMenu(String comm);








#endif //* MENU_H