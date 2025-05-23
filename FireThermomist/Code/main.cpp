
/*Discription*/
/* Project Name: FireTheroMist, SloganLine: Prevent. Detect. Save, PowerBy: Abhishek */
/*An ESP32-powered fire monitoring system designed for sensitive environments like server rooms. Continuously tracks temperature & humidity using a DHT22 sensor and provides real-time fire alerts with buzzer and animated OLED visuals. Boot-time and weather animations enhance interactivity. Ideal for safety-critical indoor setups.*/

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <DHT.h>
#include "icons.h"
#include "welcomeScreen.h"
#include "Button.h"
#include "Buzzer.h"
#include "frames.h"

// Screen Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Sensor Configuration
#define DHT_PIN 4
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);

// Pin Configuration
#define BUTTON_PIN 23
#define Buzz 19
#define flamePin 18
Button myButton(BUTTON_PIN); // Button object created
Buzzer mybuzz(Buzz);

// Button Logic
int scalemode = 0; // 0 = Celsius, 1 = Fahrenheit, 2 = Kelvin

// 🔹 Function Definitions 🔹
void drawSun(int x, int y, int size) {
    display.fillCircle(x, y, size, SH110X_WHITE);
}

void drawSunRays(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int angle = i * 45;
        int x1 = x + cos(angle * PI / 180) * 12;
        int y1 = y + sin(angle * PI / 180) * 12;
        int x2 = x + cos(angle * PI / 180) * (i % 2 == 0 ? 16 : 14);
        int y2 = y + sin(angle * PI / 180) * (i % 2 == 0 ? 16 : 14);
        display.drawLine(x1, y1, x2, y2, SH110X_WHITE);
    }
}

void drawCloud(int x, int y) {
    display.fillCircle(x, y, 6, SH110X_WHITE);
    display.fillCircle(x + 7, y, 7, SH110X_WHITE);
    display.fillCircle(x + 14, y, 6, SH110X_WHITE);
    display.fillRect(x, y, 15, 6, SH110X_WHITE);
}

void drawRain() {
    for (int i = 0; i < 15; i++) {
        int x = random(0, SCREEN_WIDTH);
        int y = random(0, SCREEN_HEIGHT - 10);
        display.drawLine(x, y, x + 1, y + 4, SH110X_WHITE);
    }
}

void drawWaterWaves() {
    for (int i = 0; i < SCREEN_WIDTH; i += 10) {
        display.drawLine(i, SCREEN_HEIGHT - 3, i + 5, SCREEN_HEIGHT - 2, SH110X_WHITE);
        display.drawLine(i + 5, SCREEN_HEIGHT - 2, i + 10, SCREEN_HEIGHT - 3, SH110X_WHITE);
    }
}

void drawMoon(int x, int y) {
    display.fillCircle(x, y, 10, SH110X_WHITE);
    display.fillCircle(x - 3, y - 3, 8, SH110X_BLACK);
}

void playBootAnimation() {
    // Sunrise (Left to Middle)
    for (int i = 0; i <= 32; i++) {
        display.clearDisplay();
        drawSun(i * 2, 48 - i, i / 4 + 5);
        display.display();
        delay(50);
    }

    delay(500);
    display.clearDisplay();
    drawSun(64, 20, 10);
    drawSunRays(64, 20);
    display.display();
    delay(2000);

    // Rain and Clouds
    for (int j = 0; j < 5; j++) {
        display.clearDisplay();
        drawCloud(50, 25);
        drawRain();
        drawWaterWaves();
        display.display();
        delay(300);
    }

    delay(500);

    // Sunset (Middle to Right Side)
    for (int i = 0; i <= 32; i++) {
        display.clearDisplay();
        if (i < 28) {
            drawSun(64 + i * 2, 20 + i, 10);
        } else {
            drawMoon(64 + i * 2, 20 + i);
        }
        display.display();
        delay(50);
    }
    delay(1000);
}

void fireAnimation() {
    for (int i = 0; i < 27; i++) {
        //display.clearDisplay();
        display.drawBitmap(46, 5, frames[i], 35, 45, SH110X_WHITE);
        display.setTextSize(1);
        display.setCursor(52, 55);
        display.print("FIRE");
        display.display();
        delay(50);
        display.clearDisplay();
    }
}


//  Setup Function 
void setup() {
    Wire.begin();
    display.begin();
    dht.begin();
    myButton.begin();
    pinMode(flamePin, INPUT_PULLDOWN);
//mybuzz.begin();
    Serial.begin(115200);
    
    if (!display.begin(0x3C, true)) {
        Serial.println("OLED Not Found!");
        while (1);
    }

    display.clearDisplay();
    welcome_Screen(display,2,22,28,"Welcome");
    welcome_Screen(display,1,105,56,"To:");
    delay(2000);
    display.clearDisplay();
    welcome_Screen(display,2,40,8,"FIRE");
    welcome_Screen(display,2,8,28,"ThermoMist");
    welcome_Screen(display,1,0,56,"Prevent. Detect. Save");
    delay(2000);
    display.clearDisplay();
    welcome_Screen(display,2,4,28,"Powered By");
    welcome_Screen(display,1,72,56,"Abhishek");
    delay(2000);
    display.clearDisplay();

    playBootAnimation();
}

//  Main Loop 
void loop() {
    //flame sensor configuration
    int flamestatus=digitalRead(flamePin);
    if (flamestatus==LOW)     
    {
        /*display.setTextSize(1);
        display.setCursor(52,55);
        display.println("FIRE");
        delay(1000);
        display.display();*/
        mybuzz.on();
        fireAnimation();   
        return;

    }
    else{
        mybuzz.off();
    }
    



    float humi = dht.readHumidity();
    float temp = dht.readTemperature();

    // Button Debounce Fix
    if (myButton.isPressed()) {
        scalemode = (scalemode + 1) % 3;
    }

    //  Temperature Conversion
    String unit;
    switch (scalemode) {
        case 0:
            unit = " C";
            break;
        case 1:
            temp = (temp * 9.0 / 5.0) + 32;
            unit = " F";
            break;
        case 2:
            temp = temp + 273.15;
            unit = " K";
            break;
    }

    //  Temperature & Humidity Display 
    display.clearDisplay();
    display.drawBitmap(0, 0, thermometer_icon, 128, 64, SH110X_WHITE);
    
    display.setTextSize(2);
    display.setCursor(5, 10);
    display.print("T:");
    display.print(temp, 2);
    display.drawCircle(92, 12, 2, SH110X_WHITE);
    display.setTextSize(1);
    display.print(unit);

    display.setTextSize(2);
    display.setCursor(5, 43);
    display.print("H:");
    display.print(humi, 2);
    display.setTextSize(1);
    display.print(" RH");

    //  Error Handling
    if (isnan(humi) || isnan(temp)) {
        display.setTextSize(2);
        display.setCursor(24, 42);
        display.println("Error!");
        display.display();
        delay(1000);
        display.clearDisplay();
        return;
    }

    display.display();
    delay(250);
}
