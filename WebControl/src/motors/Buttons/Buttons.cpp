#include "Buttons.h"

int WindowState = 0;
int DoorState = 0;

void Buttons_setup() {
    pinMode(WINDOW_BUTTON_PIN, INPUT_PULLUP);
    pinMode(DOOR_BUTTON_PIN, INPUT_PULLUP);
}

void Buttons_update() {
    WindowState = digitalRead(WINDOW_BUTTON_PIN);
    DoorState = digitalRead(DOOR_BUTTON_PIN);
}
