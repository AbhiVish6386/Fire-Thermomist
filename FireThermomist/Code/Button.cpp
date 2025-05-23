#include "Button.h"

// Constructor: Button ka pin set karega
Button::Button(int pin) {
    buttonPin=pin;
    lastButtonState=LOW;
}

// Setup function
void Button::begin() {
    pinMode(buttonPin, INPUT_PULLDOWN);
}

// Sirf button ka state return karega (HIGH ya LOW)
bool Button::isPressed() {
    bool currentState=digitalRead(buttonPin);
    if (currentState==HIGH && lastButtonState== LOW)
    {
        lastButtonState=currentState;
        return true;
    }
    lastButtonState=currentState;
    return false;
};
