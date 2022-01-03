#include <oled.h>



bool initOled()
{
  bool state;
  // Start OLED Display Init

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false))
  { // Init the OLED
    Serial.println(F("OLED INIT FAILED"));
    state = false;
    // for(;;); // Dont proceed ... loop forever//
  }
  else
  {
    oled.setRotation(2);
    oled.clearDisplay();
    oled.setTextSize(0);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 0);
    oled.println("TEST SCREEN");
    oled.display();
    state = true;
  }
  return state;
}

void oprint(String var)
{
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.println(var);
  oled.display();
}


void drawSter(int val1, int val2, String direct, String acc, int brake)
{ // PRINT KNOBS ON OLED
  oled.clearDisplay();
  oled.setCursor(0, 10);
  oled.print(direct);

  // Print BRAKE
  oled.setCursor(20, 40);
  oled.print(brake);
  oled.setCursor(40, 10);
  oled.print(acc);
  oled.setCursor(0, 20);
  oled.print(val1);
  oled.setCursor(40, 20);
  oled.print(val2);
  oled.display();
}






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

Opcje opcje;

void changeParam(bool cur) {

  Serial.println("zmiana czasu");
}

int curMenu=0;



 void displayMenu(String comm){
    
    if(comm=="enter" & opcje.item[pos].type=="bool"){
       
      opcje.item[pos].value=!opcje.item[pos].value;
      oled.setCursor(0,2);
      
      String op = (opcje.item[pos].value ==true)  ? "+" : "-";
      oled.print(op);  

    }else if(comm=="enter" & opcje.item[pos].type=="func"){

    }else if(comm=="enter" & opcje.item[pos].type=="func"){

    }else{
    
    oled.clearDisplay();
    oled.setCursor(0,0);
    oled.print(comm);

    oled.setCursor(12,0);
    oled.print(pos);
    oled.setCursor(0,2);
    
    // display bool checker
      String opt = (opcje.item[pos].value ==true)  ? "+" : "-";
      oled.print(opt);
    //

    oled.setCursor(3,0);
    oled.print(opcje.item[pos].type); 

    oled.setCursor(3,3);
    oled.print(opcje.item[pos].name);  
    }
    
 } 
 





