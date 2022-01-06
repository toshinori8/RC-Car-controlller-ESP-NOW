
#include "readPots.h"


String acc;
int brake = 0;
int pot = 0;

bool sw = false;
int turnVal1;
int turnVal2;
int mem1;
int mem2;
int maped1;
int maped2;
String dir;
int value1;
int value2;

// SIMULATE ENCODER FOR MENU INPUT
void readTurn_encoder()
{
    sw = !sw;
    if (sw == true)
    { /// LEFT/RIGHT POT reading

        digitalWrite(Pin_A, LOW);   // CHANGE SOURCE OF POWER FOR A0 PIN
        digitalWrite(Pin_B, HIGH);
        turnVal1 = analogRead(pot);  // READ FIRST ANALOG INPUT ON A0
        digitalWrite(Pin_B, LOW);
        value1 = ((turnVal1 * 1000) / 1010);

        if (value1)
        {
            if (value1 < 550)
            { // 550 -> 425
                    displayMenu(">");
            }
            else if (value1 > 602)
            { // 608 => 755
                    displayMenu("<");
            }
        }
    }
    else
    { /// acceleration POT reading
        digitalWrite(Pin_B, LOW);   // CHANGE SOURCE OF POWER FOR A0 PIN
        digitalWrite(Pin_A, HIGH);
        turnVal2 = analogRead(pot);  // READ SECOND POT ON ANALOG INPUT A0
        digitalWrite(Pin_A, LOW);
        value2 = ((turnVal2 * 1000) / 1010);

        if (value2)
        {
            if (
                value2 < 526)
            { // 755 -> 608
                displayMenu("x");
            }
            else if (
                value2 > 570)
            { // 590 => 790
                displayMenu("exit");
            }
            
            mem1 = value1;
        }
    }
};


// NORMAL READING 
void readTurn()
{
    sw = !sw;
    if (sw == true)
    { /// TURN POT reading

        digitalWrite(Pin_A, LOW);   // CHANGE SOURCE OF POWER FOR A0 PIN
        digitalWrite(Pin_B, HIGH);
        turnVal1 = analogRead(pot);  // READ FIRST ANALOG INPUT ON A0
        digitalWrite(Pin_B, LOW);
        value1 = ((turnVal1 * 1000) / 1010);

        // map(value, fromLow, fromHigh, toLow, toHigh)
        // if (value1 < (mem1 - 1) or value1 > (mem1 + 1)) {

        if (value1)
        {

            if (value1 < 550)
            { // 550 -> 425
                // Serial.println("turn right");
                dir = ">";
                maped1 = map(value1, 550, 425, 0, 100);
            }
            else if (value1 > 602)
            { // 608 => 755
                // Serial.println("turn left");
                dir = "<";
                maped1 = map(value1, 608, 755, 0, 100);
            }
            else
            {
                dir = "||";
                maped1 = 0;
            }
            mem1 = value1;
        }
        else
        {
            drawSter(maped1, maped2, dir, acc, value1);
            updateData(maped1, maped2, acc, dir, turnVal1);
        }
        drawSter(maped1, maped2, dir, acc, value1);
        updateData(maped1, maped2, acc, dir, turnVal1);

        // Serial.println(turnVal1);
    }
    else
    { /// acceleration pot reading
        digitalWrite(Pin_B, LOW);   // CHANGE SOURCE OF POWER FOR A0 PIN
        digitalWrite(Pin_A, HIGH);
        turnVal2 = analogRead(pot);  // READ SECOND ANALOG INPUT ON A0
        digitalWrite(Pin_A, LOW);    

        value2 = ((turnVal2 * 1000) / 1010);
        if (value2)
        {
            if (
                value2 < 526)
            { // 755 -> 608
                // Serial.println("backward");
                acc = "V";
                maped2 = map(value2, 526, 385, 0, 100);
            }
            else if (
                value2 > 570)
            { // 590 => 790
                // Serial.println("forward");
                acc = "^";
                maped2 = map(value2, 570, 712, 0, 100);
            }
            else
            {   
                // For stop lights emulation
                // Serial.println("stop");
                maped2 = 0;
                acc = "=";
            }
            mem1 = value1;
        }
        drawSter(maped1, maped2, dir, acc, value1);
        updateData(maped1, maped2, acc, dir, turnVal1);
    }
};

