//Библиотеки
#include <Arduino.h>

//Файлы проекта
#include "Data.h"
#include "Gate.h"
#include "WeatherFunction.h"
#include "Relay.h"
#include "Led.h"
#include "IRCoolixAC.h"
#include "Blynk.h"

Gate yardGate(15);
Gate garageGate(13);

void v12Null()
{
    button.v12 = 0;
    Blynk.virtualWrite(V12, button.v12);
}

void menu()
{
    switch (button.v12)
    {
    case 0:
        /* code */
        break;

    case 1:
        acOff();
        v12Null();
        break;

    case 2:
        acOn();
        v12Null();
        break;

    case 3:
        fanMode();
        v12Null();
        break;

    case 20:
        wardrobe.isOn();
        v12Null();
        break;

    case 21:
        wardrobe.isOff();
        v12Null();
        break;

    case 453:
        garageGate.clickButton(2);
        v12Null();
        break;

    case 454:
        garageGate.gateDidntClose();
        v12Null();
        break;

    case 455:
        garageGate.openTheGateALittle(8000, true);
        v12Null();
        break;

    case 456:
        garageGate.clickButton();
        v12Null();
        break;

    case 554:
        yardGate.gateDidntClose();
        v12Null();
        break;

    case 555:
        yardGate.openTheGateALittle(6000);
        v12Null();
        break;

    case 556:
        yardGate.clickButton();
        v12Null();
        break;

    default:
        v12Null();
        break;
    }
}

void setup()
{
    setupBlynk();
    setupAC();
    setupLed();
    setupBME280();
    Serial.begin(9600);
}

void loop()
{
    setAcTemp();
    readTempData();
    yardGate.checkButton();
    garageGate.checkButton();
    stripShowTimer(40);
    blynkRun();
    menu();
}
