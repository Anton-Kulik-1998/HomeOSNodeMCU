#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "Timer.h"

Adafruit_BME280 bme280;
Timer tempTimer;

void setupBME280()
{
    bme280.begin(0x76);
}

void readTempData()
{
    if (tempTimer.startTimer(500))
    {
        dataBME280.temperature = bme280.readTemperature();
        dataBME280.humidity = round(bme280.readHumidity() * 10) / 10;
        dataBME280.pressure = round(((bme280.readPressure() / 100.0F) * double(0.750063755419211)) * 10) / 10;
    }
}
