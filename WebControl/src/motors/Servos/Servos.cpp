#include "Servos.h"

void ServoControl::setup() {
    servoWindow.attach(WINDOW_SERVO_PIN);
    servoDoor.attach(DOOR_SERVO_PIN);     
}

void ServoControl::update() {
    static bool windowPos = false;
    static bool doorPos = false;

    if (WindowState == LOW) {
        windowPos = !windowPos;
        delay(200); 
    }
    if (DoorState == LOW) {
        doorPos = !doorPos;
        delay(200);
    }

    servoWindow.write(windowPos ? 180 : 0);
    servoDoor.write(doorPos ? 180 : 0);
}
