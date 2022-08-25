#pragma once
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Coolix.h>
#include "Timer.h"

const uint16_t kIrLed = 12; // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRCoolixAC ac(kIrLed);      // Set the GPIO used for sending messages.
Timer acTimer;

int static oldTemp = 20; //Переменная, необходимая для проверки изменения температуры. Если отличается, то новое значение отдем кондиционеру

void printState()
{
    // Display the settings.
    Serial.println("Coolix A/C remote is in the following state:");
    Serial.printf("  %s\n", ac.toString().c_str());
}

void setupAC()
{
    ac.begin();
    ac.off();
    ac.setFan(kCoolixFanMin);
    ac.setMode(kCoolixCool);
    ac.setTemp(button.v11);
    ac.setSwing(); //Тут проблемы!
}

void test()
{
    // Turn the A/C unit on
    Serial.println("Turn on the A/C ...");
    ac.on();
    ac.send();
    printState();
    delay(15000); // wait 15 seconds
    // and set to cooling mode.
    Serial.println("Set the A/C mode to cooling ...");
    ac.setMode(kCoolixCool);
    ac.send();
    printState();
    delay(15000); // wait 15 seconds

    // Increase the fan speed.
    Serial.println("Set the fan to high and the swing on ...");
    ac.setFan(kCoolixFanMax);
    ac.setSwing();
    ac.send();
    printState();
    delay(15000);

    // Change to Fan mode, lower the speed, and stop the swing.
    Serial.println("Set the A/C to fan only with a low speed, & no swing ...");
    ac.setSwing();
    ac.setMode(kCoolixFan);
    ac.setFan(kCoolixFanMin);
    ac.send();
    printState();
    delay(15000);

    // Turn the A/C unit off.
    Serial.println("Turn off the A/C ...");
    ac.off();
    ac.send();
    printState();
    delay(15000); // wait 15 seconds
}

void acOn()
{
    ac.on();
    ac.send();
}

void acOff()
{
    ac.off();
    ac.send();
}

void fanMode()
{
    ac.on();
    ac.send();
}

void setAcTemp() // В главный цикл!
{
    if (acTimer.startTimer(300))
    {
        if (oldTemp != button.v11)
        {
            if (button.v11 >= 17 && button.v11 <= 30)
            {
                oldTemp = button.v11;
                ac.setTemp(button.v11);
                ac.send();
            }
        }
    }
}