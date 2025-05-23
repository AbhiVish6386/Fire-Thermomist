#include "welcomeScreen.h"

void welcome_Screen(Adafruit_SH1106G &display, int s, int x, int y, const char *message){
    display.setTextSize(s);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(x, y);
    display.println(message);
    display.display();
}