#include "Relay.h"

Relay::Relay(byte pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, false); // Начальное состояние реле.
}

void Relay::isOn()
{
    digitalWrite(_pin, true);
}

void Relay::isOff()
{
    digitalWrite(_pin, false);
}


