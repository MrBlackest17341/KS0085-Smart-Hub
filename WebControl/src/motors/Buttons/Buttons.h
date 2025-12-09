#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "config.h"

extern int WindowState;
extern int DoorState;

void Buttons_setup();
void Buttons_update();

#endif
