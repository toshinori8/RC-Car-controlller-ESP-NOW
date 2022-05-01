
  int counter_brake = 6;  // delay for stop led.
#include "PCF8574.h"

PCF8574 pcf8574(0x25, 10, 0);


  void turnLightFW(int direction) {
    // Serial.println(direction);
    // Serial.println(counter_brake);
    if (direction == 1) {
      // stop light       OFF
      // reverse light    OFF
    }
    if (direction == 2) {
      // stop light       ON
      // Serial.println('stop    ON');

      if (counter_brake == 0) {
      //  Serial.println("reverse ON");
      //  Serial.println("stop    OFF");
        // reverse light    ON
        // stop light       OFF
      } else {
        counter_brake--;
      }




    } else
      (counter_brake = 6);
  }

  void turnLightLeft() {
  //  Serial.println('turn  LEFT');
  };
  void turnLightRight() {

   // Serial.println('turn  RIGHT');
  };

bool initI2Cbus()
{

  //Wire.beginTransmission(0x25); // device 1

    delay(3000);
  // I2C device found at address 0x25  !  PCF8574
  // I2C device found at address 0x3C  !  OLED

	pcf8574.pinMode(0, OUTPUT, HIGH);
	pcf8574.pinMode(1, OUTPUT, HIGH);
  pcf8574.digitalWrite(0, LOW);
  pcf8574.digitalWrite(1, HIGH);
  

  delay(3000);
  Serial.print("Init pcf8574...");
  if (pcf8574.begin())
  {
    Serial.println("OK");
    return true;
  }
  else
  {
    Serial.println("NOT OK");
    return false;
  }
  delay(1000);  
}

