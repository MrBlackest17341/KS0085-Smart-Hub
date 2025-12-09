#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "config.h"

class Display {
  private:
    LiquidCrystal_I2C lcd; 
  public:
    Display();
    void setup();
    void printGas(float ppm);
    void printLight(int value);
    void printHimiditty(int value);
    void printSteam (int value);
};

#endif
