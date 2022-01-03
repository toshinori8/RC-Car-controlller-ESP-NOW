#include "menu.h"
#include "oled.h"

Opcje opcje;

void changeParam(bool cur) {

  Serial.println("zmiana czasu");
}

 void displayMenu(String comm){
    
    if(comm =="start") {pos =0;};

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
    
    
    
    // oled bool checker
      String opt = (opcje.item[pos].value ==true)  ? "+" : "-";
      oled.print(opt);


    //



    oled.setCursor(3,0);
    oled.print(opcje.item[pos].type); 



    oled.setCursor(3,3);
    oled.print(opcje.item[pos].name);  

    
    }
    
    

 } 
 

