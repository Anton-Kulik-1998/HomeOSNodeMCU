#pragma once
#include <Arduino.h>

struct DataBME
{
    float temperature;
    float humidity;
    float pressure;
};

struct Color {
 byte r = 0;
 byte g = 0;
 byte b = 0;
 byte Brightness = 255;
};

struct Button
{
    bool v6;
    int v11 = 20;
    int v12;
};


DataBME static dataBME280;
Color static color;
Button static button;