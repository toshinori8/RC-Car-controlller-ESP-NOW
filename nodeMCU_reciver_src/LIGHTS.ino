
int counter_brake =6; // delay for stop led. 

void  turnLightFW(int direction){
Serial.println(direction);
Serial.println(counter_brake);
    if(direction==1){
        // stop light       OFF
        // reverse light    OFF 

    }
     if(direction==2){
        // stop light       ON
        // Serial.println('stop    ON');
        
        if(counter_brake==0){
                Serial.println("reverse ON");
                Serial.println("stop    OFF");
                // reverse light    ON 
                // stop light       OFF
        }else{
          counter_brake--;

        }


        
        
    }else(counter_brake = 6);

}

void turnLightLeft(){
// Serial.println('turn  LEFT');

};
void turnLightRight(){

// Serial.println('turn  RIGHT');

};