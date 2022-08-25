#pragma once
#include <Arduino.h>


class Relay
{
private:
    byte _pin;
public:
    Relay(byte pin);
    void isOn();
    void isOff();
};

Relay static wardrobe(14);