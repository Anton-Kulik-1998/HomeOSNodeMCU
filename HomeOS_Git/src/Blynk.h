#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Timer.h"

char auth[] = "token";
char ssid[] = "wifi";
char pass[] = "";

Timer blynkTimer1;
Timer blynkTimer2;
Timer blynkTimer3;

BLYNK_WRITE(V5) {
  color.r = param[0].asInt();
  color.g = param[1].asInt();
  color.b = param[2].asInt();
}

BLYNK_WRITE(V3) {
  color.Brightness = param.asInt();
}

BLYNK_WRITE(V4) {
  ledMenu = param.asInt();
}

BLYNK_WRITE(V6) {
  button.v6 = param.asInt();
}

BLYNK_WRITE(V11) {
  button.v11 = param.asInt();
}

BLYNK_WRITE(V12) {
  button.v12 = param.asInt();
}



void setupBlynk()
{
  Blynk.begin(auth, ssid, pass);
  Blynk.virtualWrite(V3, color.Brightness);
  Blynk.virtualWrite(V4, ledMenu);
  Blynk.virtualWrite(V11, button.v11);

}

void blynkRun()
{
  if (blynkTimer1.startTimer(1000))
  {
    Blynk.virtualWrite(V0, dataBME280.temperature);
  }

  if (blynkTimer2.startTimer(2000))
  {
    Blynk.virtualWrite(V1, dataBME280.humidity);
  }

  if (blynkTimer3.startTimer(5000))
  {
    Blynk.virtualWrite(V2, dataBME280.pressure); 
  }
  Blynk.run();
}