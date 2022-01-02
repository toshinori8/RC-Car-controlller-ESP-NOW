#include <Arduino.h>
#include <header.h>

bool sw = false;
int turnVal1;
int turnVal2;
int mem1;
int mem2;
int maped1;
int maped2;
String dir;
String acc = "forward";
int value1;
int value2;
int brake = 0;

const int pot = 0;
int Pin_A = 5; // analog INPUT POWER SOURCE #1
int Pin_B = 4; // analog INPUT POWER SOURCE #2

void readTurn()
{
    sw = !sw;
    if (sw == true)
    { /// TURN POT reading

        digitalWrite(Pin_A, LOW);
        digitalWrite(Pin_B, HIGH);
        turnVal1 = analogRead(pot);
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
    { /// acceleration reading

        digitalWrite(Pin_B, LOW);
        digitalWrite(Pin_A, HIGH);

        turnVal2 = analogRead(pot);
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