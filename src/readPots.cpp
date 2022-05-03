#include "readPots.h"

String acc;     // ACCELERATION
String dir;     // LEFT RIGHT STRING
int brake = 0;  // BRAKE

// VALUES OF POTS IN %
int value1;     // acceleration 
int value2;     // turn

int pot = 0;    // ANALOG INPUT A0

bool sw = false; // VARIABLE OF ACTUAL POT 

int turnVal1;       
int turnVal2;
int mem1;
int mem2;
int maped1;
int maped2;    


// SIMULATE ENCODER TO CONTROLL MENU
void readTurn_encoder()
{
    sw = !sw;
    if (sw == true)
    { /// LEFT/RIGHT POT reading

        digitalWrite(Pin_A, LOW); // CHANGE SOURCE OF POWER FOR A0 PIN
        digitalWrite(Pin_B, HIGH);
        turnVal1 = analogRead(pot); // READ FIRST ANALOG INPUT ON A0
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
    {   /// UP/DOWN POT reading
        digitalWrite(Pin_B, LOW); // CHANGE SOURCE OF POWER FOR A0 PIN
        digitalWrite(Pin_A, HIGH);
        turnVal2 = analogRead(pot); // READ SECOND POT ON ANALOG INPUT A0
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

// NORMAL READING - PROPORTIONAL
void readTurn()
{
    sw = !sw;
    if (sw == true)
    { /// LEFT/RIGHT POT reading

        digitalWrite(Pin_A, LOW); // CHANGE SOURCE OF POWER FOR A0 PIN
        digitalWrite(Pin_B, HIGH);
        turnVal1 = analogRead(pot); // READ FIRST ANALOG INPUT ON A0
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
        // update display and send data
        drawSter(maped1, maped2, dir, acc, value1);
        updateData(maped1, maped2, acc, dir, turnVal1);

        // Serial.println(turnVal1);
    }
    else
    {   /// ACCELERATION POT reading
        digitalWrite(Pin_B, LOW); // CHANGE SOURCE OF POWER FOR A0 PIN
        digitalWrite(Pin_A, HIGH);
        turnVal2 = analogRead(pot); // READ SECOND ANALOG INPUT ON A0
        digitalWrite(Pin_A, LOW);

        value2 = ((turnVal2 * 1000) / 1010);
        if (value2)
        {
            if (
                value2 < 526)
            { // 755 -> 608
                // Serial.println("backward");
                acc = "^";
                maped2 = map(value2, 526, 385, 0, 100);

                // to do // brake light indicator on reciver side
            
            }
            else if (
                value2 > 570)
            { // 590 => 790
                // Serial.println("forward");
                acc = "V";
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
        // update display and send data
        drawSter(maped1, maped2, dir, acc, value1);
        updateData(maped1, maped2, acc, dir, turnVal1);
    }
};
