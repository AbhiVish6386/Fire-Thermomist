#pragma once
//Necessary headerfile for it
#include<Adafruit_GFX.h>
#include<Adafruit_SH110X.h>

//Fucntion Prototype
void welcome_Screen(Adafruit_SH1106G &display, int s, int x, int y, const char *message);
