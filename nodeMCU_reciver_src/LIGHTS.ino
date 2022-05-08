
int counter_brake = 6;  // delay for stop led.
int counter_turn_1 = 8;  // 
int counter_turn_2 = 120;  // delay 


#include "PCF8574.h"

#include <Timers.h>




PCF8574 pcf8574(0x25, 10, D3); // init PCF8574 board

  void leftLED(){
        counter_turn_1--;
        if(counter_turn_1==0){
          pcf8574.digitalWrite(P7, LOW);
          counter_turn_1=6;
        }else{
          pcf8574.digitalWrite(P7, HIGH); 
        }
        pcf8574.digitalWrite(P6, HIGH);
  }
  void rightLED(){
          counter_turn_1--;
        if(counter_turn_1==0){
          pcf8574.digitalWrite(P6, LOW);
          counter_turn_1=6;
        }else{
          pcf8574.digitalWrite(P6, HIGH); 
        }
        pcf8574.digitalWrite(P7, HIGH);
  }

// short_lights
void short_lights_ON(){ pcf8574.digitalWrite(P5, LOW);};
void short_lights_OFF(){ pcf8574.digitalWrite(P5, HIGH);};


// long_lights
void long_lights_ON(){ pcf8574.digitalWrite(P4, LOW);};
void long_lights_OFF(){ pcf8574.digitalWrite(P4, HIGH);};


// haloo_lights
void haloo_lights_ON(){ pcf8574.digitalWrite(P3, LOW);};
void haloo_lights_OFF(){ pcf8574.digitalWrite(P3, HIGH);};



void turnLightFW(int direction) {


 if (direction == 1) {
    // stop light       OFF
    // reverse light    OFF
    pcf8574.digitalWrite(P0, HIGH);
  }
  if (direction == 2) {
    // stop light       ON
    // Serial.println('stop    ON');
    pcf8574.digitalWrite(P0, LOW);
    if (counter_brake == 0) {
      //  Serial.println("reverse ON");
      //  Serial.println("stop    OFF");
      // reverse light    ON
      // stop light       OFF
      pcf8574.digitalWrite(P0, HIGH);


    } else {
      counter_brake--;
    }




  } else
    (counter_brake = 6);
  
 
}

void turnLightLeft(){


   
    timers.updateInterval(0,counter_turn_2);
    timers.updateInterval(1,0);
};
void turnLightRight(){
   
  
    timers.updateInterval(1, counter_turn_2); 
    timers.updateInterval(0, 0);
};

bool initI2Cbus() {
  Timers<4> timers; // DEFINE # OF TIMERS


  Wire.beginTransmission(0x25);  // device 1

  delay(3000);
  // I2C device found at address 0x25  !  PCF8574


  pcf8574.pinMode(0, OUTPUT, HIGH);
  pcf8574.pinMode(1, OUTPUT, HIGH);
     
      // TURN LIGHTS 
      pcf8574.pinMode(6, OUTPUT, HIGH); // TURN RIGHT
      pcf8574.pinMode(7, OUTPUT, HIGH); // TURN LEFT 

  pcf8574.digitalWrite(0, LOW);
  pcf8574.digitalWrite(1, HIGH);
  pcf8574.digitalWrite(P2, HIGH);

  delay(3000);
  Serial.print("Init pcf8574...");
  if (pcf8574.begin()) {
    Serial.println("OK");
    return true;
  } else {
    Serial.println("NOT OK");
    return false;
  }
  delay(1000);
}

