
int counter_brake =100; // delay for stop led. 

void  turnLightFW(String direction){
Serial.print(direction);
    if(direction=="forw"){
        // stop light       OFF
        // reverse light    OFF 

    }
     if(direction=="back"){
        // stop light       ON
        Serial.println('stop    ON');
        counter_brake--;

        if(counter_brake==0){
                Serial.println('reverse ON');
                Serial.println('stop    OFF');
                // reverse light    ON 
                // stop light       OFF
        }
    }else(counter_brake = 100);

}

void turnLightLeft(){};
void turnLightRight(){};