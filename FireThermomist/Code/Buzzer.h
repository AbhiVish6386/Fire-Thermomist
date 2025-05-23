#pragma
#include<Arduino.h>
class Buzzer{
    public:
    Buzzer (int pin);
    void on();
    void off();
    void beep(int duration);
    private:
    int buzzerPin;
};