#include "Gate.h"

Gate::Gate(byte pin, uint16_t pressButtonPeriod)
{
    _pin = pin;
    _pressButtonPeriod = pressButtonPeriod;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, false);
}

void Gate::sendASignalToThePin(bool pinFlag)
{
    digitalWrite(_pin, pinFlag);
}

void Gate::clickButton(byte numberOfClicks, uint16_t delayBetweenClicks)
{
    _numberOfClicks = numberOfClicks;
    _delayBetweenClicks = delayBetweenClicks;
    _flag = true;

}

void Gate::openTheGateALittle(uint16_t period, bool dualStartClick)
{
    if (dualStartClick)
    {
        clickButton(1, _pressButtonPeriod);
    }
    
    clickButton(2,period);
}

void Gate::gateDidntClose()
{
    clickButton(3, 800);
}

void Gate::checkButton()
{
    static byte count = 0;
    
    if (_flag)
    {
        switch (count)
        {
        case 0:
            count++;
            myTimer.resetTheTimer();
            break;
        case 1:
            if (myTimer.startTimer(_pressButtonPeriod))
            {
                count++;
                sendASignalToThePin(false);
            }
            else
            {
                sendASignalToThePin(true); //Здесь должно быть true(Для ворот), но лампочка на плате горит когда там false(Для теста работы алгоритма)
            }
            break;
        case 2:
            _numberOfClicks > 1 ? count++ : count = 5;
            break;
        case 3:
            _numberOfClicks--;
            myTimer.resetTheTimer();
            count++;
            break;
        case 4:
            if (myTimer.startTimer(_delayBetweenClicks))
            {
                count = 0;
            }
            break;
        case 5:
            _flag = false;
            count = 0;
            break;
        default:
            _flag = false;
            break;
        }
    }
}
