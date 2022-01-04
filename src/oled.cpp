#include <Adafruit_GFX.h>     // for OLED display
#include <Adafruit_SSD1306.h> // for OLED display
#include <Adafruit_I2CDevice.h>
#include "oled.h"
#include <U8g2lib.h>
//#include "FreeSansBold12pt7b.h"
#include <Fonts/FreeSans9pt7b.h>



Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);
// U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);	// I2C / TWI 
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);	      




#define MENU_SIZE 4-1

Opcje opcje;


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
    u8g2.begin();
    u8g2.enableUTF8Print();	
    
    
    oled.setRotation(2);
    oled.clearDisplay();
    oled.setTextSize(0);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 0);
    oled.println("TEST SCREEN");
    oled.display();
    state = true;
  }



opcje.item[0].type = "bool";
opcje.item[0].name = "Lights";
opcje.item[0].value = true;
  
opcje.item[1].type = "bool";
opcje.item[1].name = "Auto OFF";
opcje.item[1].value = true;
  
opcje.item[2].type = "bool";
opcje.item[2].name = "Migacze auto";
opcje.item[2].value = true;

opcje.item[3].type = "bool";
opcje.item[3].name = "Halogeny";
opcje.item[3].value = true;

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
{ 
  //oled.drawFastVLine(20,20,2,SSD1306_WHITE);


//u8g2.clearDisplay();
//u8g2.clearBuffer();
  u8g2.setDisplayRotation(U8G2_R2);
  // PRINT KNOBS ON OLED  
  u8g2.setFont(u8g2_font_amstrad_cpc_extended_8f); 
  

  // Print KIERUNKI
  u8g2.setCursor(0, 0);
  u8g2.print(direct);
  // Print BRAKE
  u8g2.setCursor(10, 30);
  u8g2.print(brake);

    // Print UP/DOWN
  u8g2.setCursor(30, 0);
  u8g2.print(acc);

    // Print value of kierunek 
  u8g2.setCursor(0, 10);
  u8g2.print(val1);

    // Print value of acceleration 
  u8g2.setCursor(30, 10);
  u8g2.print(val2);
  

  //u8g2.setFont(u8g2_font_unifont_t_72_73);  // use chinese2 for all the glyphs of "你好世界"
  //u8g2.setFontDirection(0);
  u8g2.setCursor(0, 0);
  u8g2.print("łucja");		// Chinese "Hello World" 
  u8g2.sendBuffer();

  //oled.display();
}

// DEFINE MENU ITEMS




//






 void displayMenu(String comm){

Serial.println(comm);
Serial.println(pos);

if(comm=="start"){
menustate=1;

}

if(comm==">"){
  
pos++;
if(pos == MENU_SIZE+1){pos=0;};

}
if(comm=="<"){
pos--;
if(pos == -1){pos=MENU_SIZE-1;};

}





oled.setFont(&FreeSans9pt7b);
//oled.setTextSize(1.8);
//oled.invertDisplay(true);

      oled.clearDisplay();
    
      if(comm =="start") {pos =0;};

      if(comm=="x" & opcje.item[pos].type=="bool"){

          Serial.println("executing _ change");

      oled.setCursor(5,15);
      oled.print(opcje.item[pos].name);  


      opcje.item[pos].value=!opcje.item[pos].value;
      oled.setCursor(0,15);
      
      String op = (opcje.item[pos].value ==true)  ? "|" : "";
      oled.print(op); 
      
      Serial.println(opcje.item[pos].value);
      Serial.println(op);

      oled.display();
    }else{
    
     
    oled.clearDisplay();

    oled.setCursor(0,15);
    
    
    
    // oled bool checker
      String opt = (opcje.item[pos].value ==true)  ? "|" : "";
      oled.print(opt);

    //



    oled.setCursor(3,5);
   // oled.print(opcje.item[pos].type); 



    oled.setCursor(5,15);
    oled.print(opcje.item[pos].name);  

    oled.display();
    }
    
    

 } 
 















 





