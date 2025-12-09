#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include "../Buttons/Buttons.h"
#include "config.h"


class ServoControl {
private:
    Servo servoWindow;
    Servo servoDoor;

public:
    void setup();
    void update();
    void setWindowPos(int angle) { servoWindow.write(angle); }
    void setDoorPos(int angle) { servoDoor.write(angle); }
};


#endif
