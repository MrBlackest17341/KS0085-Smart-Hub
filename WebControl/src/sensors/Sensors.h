#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "config.h"
#pragma once

// ----------------------- PIR -----------------------
class PirSensor {
public:
    void setup();
    void detected();
};



// ----------------------- Humidity -----------------------
class SoilSensor {
private:
    int value = 0;

public:
    void setup();
    void update();
    void controlWarm();
    int getValue();
};

// ----------------------- Light -----------------------
class LightSensor {
private:
    int value = 0;

public:
    void setup();
    void update();
    void controlLED();
    int getValue();
};


// ----------------------- Steam -----------------------
class SteamSensor {
private:
    int value = 0;

public:
    void setup();
    void update();
    void controlPump();
    int getValue();
};


// ----------------------- Gas -----------------------
class GasSensor {
private:
    int lastRaw = 0;
public:
    static float RO;
    void setup();
    void update();
    void calibrate();
    float getPPM();
    void controlFan();
};

// ----------------------- DANGER/ALER -----------------------


// -------------------------------------------------------
// INITIALIZATION OF CONCLUSIONS
// -------------------------------------------------------

inline void setupDangerHardware() {
    pinMode(WHITE_LED_PIN, OUTPUT);
    pinMode(FAN_PIN1, OUTPUT);
    pinMode(FAN_PIN2, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}

// -------------------------------------------------------
// BUZZER ALERT
// -------------------------------------------------------

inline void alertBuzzerOnce() {
    // First tone
    tone(BUZZER_PIN, 1500);
    delay(200);
    noTone(BUZZER_PIN);
    delay(300);

    // Second tone (double alarm)
    tone(BUZZER_PIN, 1700);
    delay(200);
    noTone(BUZZER_PIN);
    delay(400);
}


// -------------------------------------------------------
// DANGER CONTROL (light + fan)
// -------------------------------------------------------

inline void enterDanger() {
    digitalWrite(FAN_PIN1, HIGH);
    digitalWrite(FAN_PIN2, LOW);
    digitalWrite(WHITE_LED_PIN, HIGH);
    alertBuzzerOnce();
}

inline void exitDanger() {
    digitalWrite(FAN_PIN1, LOW);
    digitalWrite(FAN_PIN2, LOW);
    digitalWrite(WHITE_LED_PIN, LOW);
}


// -------------------------------------------------------
// SIMPLE DANGER LIGHT (for PIR)
// -------------------------------------------------------

inline void dangerLight() {
    digitalWrite(WHITE_LED_PIN, HIGH);
    delay(1000);
    digitalWrite(WHITE_LED_PIN, LOW);
}


#endif
