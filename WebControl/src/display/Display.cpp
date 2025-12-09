#include "Display.h"

Display::Display() : lcd(0x27, 16, 2) { }

void Display::setup() {
    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0, 0);
}

void Display::printGas(float ppm) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GAS ppm:");
    lcd.setCursor(0, 1);
    lcd.print(ppm);
}

void Display::printLight(int value) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Light lm:");
    lcd.setCursor(0, 1);
    lcd.print(value);
}

void Display::printHimiditty(int value) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Soil Humidity %:");
    lcd.setCursor(0, 1);
    lcd.print(value);
}


void Display::printSteam(int value) { 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Steam Value:");
    lcd.setCursor(0, 1);
    lcd.print(value);
}

