#pragma once
#include <Arduino.h>
#include "Timer.h"
class Gate
{
public:
    Gate(byte pin = 15, uint16_t pressButtonPeriod = 300); // конструктор с дефолтными параметрами (Номер пина, период нажатия кнопки, период открытия ворот)
    void clickButton(byte numberOfClicks = 1, uint16_t delayBetweenClicks = 300);
    void openTheGateALittle(uint16_t period = 1000, bool dualStartClick = false); //Приоткрыть ворота на указанный период времени
    void gateDidntClose(); //Три раза нажать на кнопку(Ворота открываются, останавливаются и затем опять закрываются)
    void checkButton(); //Метод нужно разместить в главном цикле программы!!!

private:
    struct Timer myTimer;
    bool _flag = false; //Флаг для начала выпонения клика
    void sendASignalToThePin(bool pinFlag); // Отправить сигнал на указанный пин кнопки
    byte _pin; // номер пина ворот
    uint16_t _pressButtonPeriod;     // Период нажатия на кнопку ворот
    byte _numberOfClicks; // Кол-во кликов за один вызов функции
    uint16_t _delayBetweenClicks; // Задержка между кликами
};
