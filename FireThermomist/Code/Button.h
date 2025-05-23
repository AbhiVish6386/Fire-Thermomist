#pragma once
#include <Arduino.h>

class Button {
private:
    int buttonPin;
    bool lastButtonState;
public:
    Button(int buttonPin);  
    void begin();               
    bool isPressed();          
};
