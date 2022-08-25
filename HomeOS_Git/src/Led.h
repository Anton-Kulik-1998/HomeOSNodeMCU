#pragma once
#include <Arduino.h>
#include "Timer.h"

#define STRIP_PIN 16 // пин ленты
#define NUMLEDS 84  // кол-во светодиодов 84

// настройки пламени
#define HUE_START 3    // начальный цвет огня (0 красный, 80 зелёный, 140 молния, 190 розовый)
#define HUE_GAP 18     // коэффициент цвета огня (чем больше - тем дальше заброс по цвету)
#define SMOOTH_K 0.15  // коэффициент плавности огня  0.15
#define MIN_BRIGHT 80  // мин. яркость огня
#define MAX_BRIGHT 255 // макс. яркость огня
#define MIN_SAT 245    // мин. насыщенность
#define MAX_SAT 255    // макс. насыщенность

// ленивая жопа
#define FOR_i(from, to) for (int i = (from); i < (to); i++)
#define FOR_j(from, to) for (int j = (from); j < (to); j++)

// для разработчиков
#define ZONE_AMOUNT NUMLEDS // количество зон
byte zoneValues[ZONE_AMOUNT];
byte zoneRndValues[ZONE_AMOUNT];

#define COLOR_DEBTH 3
#include <FastLED.h>

CRGB leds[NUMLEDS];
uint8_t hue = 0;
byte static ledMenu = 0;
Timer menuTimer;
Timer fireTimer1;
Timer fireTimer2;

// возвращает цвет огня для одного пикселя
CRGB getFireColor(int val)
{
    // чем больше val, тем сильнее сдвигается цвет, падает насыщеность и растёт яркость
    return CHSV(
        HUE_START + map(val, 20, 60, 0, HUE_GAP),                   // H
        constrain(map(val, 20, 60, MAX_SAT, MIN_SAT), 0, 255),      // S
        constrain(map(val, 20, 60, MIN_BRIGHT, MAX_BRIGHT), 0, 255) // V
    );
}

void fireTick()
{

    // задаём направление движения огня
    if (fireTimer1.startTimer(100))
    {
        FOR_i(0, ZONE_AMOUNT)
        {
            zoneRndValues[i] = random(0, 10);
        }
    }

    // двигаем пламя
    if (fireTimer2.startTimer(20))
    {
        FOR_i(0, ZONE_AMOUNT)
        {
            zoneValues[i] = (float)zoneValues[i] * (1 - SMOOTH_K) + (float)zoneRndValues[i] * 10 * SMOOTH_K;
            leds[i] = getFireColor(zoneValues[i]);
        }
        FastLED.show();
    }
}

void loft()
{
    FastLED.clear();
    for (int i = 0; i < NUMLEDS; i++)
    {
        leds[i] = CRGB(150, 100, 10); // microLED: (255, 190, 70)      TV(FastLED): 200, 100, 10      150, 100, 10
        i += 3;
    }
    FastLED.show();
}

void rainbow()
{
    for (int i = 0; i < NUMLEDS; ++i)
    {
        leds[i] = CHSV(hue + (i * 5), 255, 255); // (i * 5) <-- там где 5, можно управлять шириной линии
    }

    // You can change the pattern speed here
    EVERY_N_MILLISECONDS(120)
    {
        hue++;
    }

    FastLED.show();
}

void clear() {
  FastLED.clear();
  for (int i = 0; i < NUMLEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
    }
  FastLED.show();
}

void zebra()
{
    // strip.fill(mRGB(color.r,color.g,color.b));
    for (int i = 0; i < NUMLEDS; i++)
    {
        leds[i] = CRGB(color.r, color.g, color.b);
    }
    FastLED.show();
}


void stripShowTimer(uint16_t timer) //Главный цикл
{
    if (menuTimer.startTimer(timer))
    {
        FastLED.setBrightness(color.Brightness);

        switch (ledMenu)
        {
        case 0:
            zebra();
            break;

        case 1:
            loft();
            break;

        case 2:
            rainbow();
            break;

        case 3:
            fireTick();
            break;

        case 4:
            clear();
            break;

        default:
            clear();
            break;
        }
    }
}

void setupLed()
{
    FastLED.addLeds<WS2812, STRIP_PIN, GRB>(leds, NUMLEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(color.Brightness);
    FastLED.clear();
}
