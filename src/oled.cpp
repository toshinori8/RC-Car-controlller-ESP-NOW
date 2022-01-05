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




#define MENU_SIZE 6-1

Opcje opcje;


const uint8_t lights[]{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x79, 0x3c, 0x01, 0x06, 0x7b, 0x03, 0x03, 0x03, 
0x7b, 0x01, 0x03, 0x03, 0x7f, 0x06, 0x01, 0x0c, 0x7d, 0xf8, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00
};
const uint8_t turn_lights[]{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x7e, 0xfe, 0x7f, 
0x7e, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t allert[]{
0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x80, 0x03, 0x80, 0x06, 0xc0, 0x05, 0xc0, 0x0f, 0xe0, 
0x0e, 0xf0, 0x1c, 0x70, 0x3c, 0x78, 0x2f, 0xf8, 0x6f, 0xec, 0x7f, 0xfc, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t battery[]{
0x00, 0x00, 0x00, 0x00, 0x1c, 0x38, 0x3c, 0x38, 0x7f, 0xfe, 0x40, 0x02, 0x40, 0x02, 0x58, 0x3a, 
0x5c, 0x3e, 0x40, 0x12, 0x40, 0x02, 0x7f, 0xfe, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t low_lights[]{
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x09, 0xf0, 0x13, 0xbc, 0x23, 0x0e, 0x4b, 0x03, 0x13, 0x03, 
0x23, 0x01, 0x4b, 0x03, 0x13, 0x06, 0x23, 0x0e, 0x4b, 0xf8, 0x13, 0xe0, 0x20, 0x00, 0x40, 0x00
};






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
    
      //u8g2.drawBitmap(60, 0, lights1light1, 23, 32, 1);

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
opcje.item[0].name = "Dlugie";
opcje.item[0].value = false;

opcje.item[1].type = "bool";
opcje.item[1].name = "Krutkie";
opcje.item[1].value = false;
  
opcje.item[2].type = "bool";
opcje.item[2].name = "Halogeny";
opcje.item[2].value = false;
  
opcje.item[3].type = "bool";
opcje.item[3].name = "Migacze auto";
opcje.item[3].value = true;

opcje.item[4].type = "bool";
opcje.item[4].name = "Alarm";
opcje.item[4].value = false;

opcje.item[5].type = "bool";
opcje.item[5].name = "Awaryjne";
opcje.item[5].value = false;

opcje.item[6].type = "bool";
opcje.item[6].name = "Auto OFF";
opcje.item[6].value = true;


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
  

//u8g2.clearDisplay();
//u8g2.clearBuffer();
  u8g2.setDisplayRotation(U8G2_R2);
  
  oled.drawFastVLine(20,20,2,SSD1306_WHITE);

  
  // PRINT KNOBS ON OLED  
  u8g2.setFont(u8g2_font_amstrad_cpc_extended_8f); 
  

        // Display icons 
  if(O_long_lights==1){
            u8g2.drawBitmap( 70, -2, 2, 16, lights);

  }
  if(O_short_lights==1){
            u8g2.drawBitmap( 70, -2, 2, 16, low_lights);

  }
  // Serial.println(O_turn_lights);
  if(O_turn_lights==1){
            u8g2.drawBitmap( 70, 18, 2, 16,turn_lights);

  }
  if(O_error_lights==1){
            u8g2.drawBitmap( 93, 17, 2, 16,allert);

  }


 if(battery_low==1){
            u8g2.drawBitmap( 113, 18, 2, 16,battery);

  }



  // Print KIERUNKI
  u8g2.setCursor(0, 20);
  u8g2.print(direct);
  // Print BRAKE
  u8g2.setCursor(10, 20);
  u8g2.print(brake);

    // Print UP/DOWN
  u8g2.setCursor(0, 30);
  u8g2.print(acc);

  u8g2.setFont(u8g2_font_helvR10_tn);
    // Print value of kierunek 
  u8g2.setCursor(0, 11);
  u8g2.print(val1);

    // Print value of acceleration 
  u8g2.setCursor(30, 11);
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

// Serial.println(comm);
// Serial.println(pos);

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

//oled.invertDisplay(true);

      oled.clearDisplay();

      //oled.drawBitmap(50, 50,  turn_lights, 16, 16, WHITE, BLACK);
     

      if(comm =="start") {pos =0;};

      


      oled.setCursor(5,15);
      oled.print(opcje.item[pos].name);  


      opcje.item[pos].value=!opcje.item[pos].value;
      
      if(comm=="x" & opcje.item[pos].type=="bool"){

          if(opcje.item[pos].name=="Dlugie"){
            O_long_lights=opcje.item[pos].value;
          }
          if(opcje.item[pos].name=="Krutkie"){
            O_short_lights=opcje.item[pos].value;
          }
          if(opcje.item[pos].name=="Halogeny"){
            O_haloo_lights=opcje.item[pos].value;
          }
          if(opcje.item[pos].name=="Migacze auto"){
            O_turn_lights=opcje.item[pos].value;
          }
          if(opcje.item[pos].name=="Alarm"){
            O_alarm_lights=opcje.item[pos].value;
          }
          if(opcje.item[pos].name=="Awaryjne"){
            O_error_lights=opcje.item[pos].value;
          }
          if(opcje.item[pos].name=="Auto OFF"){
            O_autoOff_lights=opcje.item[pos].value;
          }
   

      oled.setCursor(0,15);
      String op = (opcje.item[pos].value ==true)  ? "|" : "";
      oled.print(op); 
      
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
 















 





