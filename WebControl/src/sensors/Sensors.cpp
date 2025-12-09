#include "Sensors.h"
#include <math.h>


// ----------------------- PIR -----------------------
void PirSensor::setup() {
    pinMode(PIR_PIN, INPUT);
}

void PirSensor::detected() {
    if (digitalRead(PIR_PIN) == HIGH) {
        dangerLight();
        alertBuzzerOnce();
    }
}


// ----------------------- SOIL -----------------------

void SoilSensor::setup() {
    pinMode(SOIL_PIN, INPUT);
}

void SoilSensor::update() {
    value = analogRead(SOIL_PIN);
}

void SoilSensor::controlWarm() {
    if (value > 3000) {
        dangerLight();
        alertBuzzerOnce();
    }
}

int SoilSensor::getValue() {
    return value;
}

// ----------------------- LIGHT -----------------------

void LightSensor::setup() {
    pinMode(LIGHT_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(RELAY_PIN, OUTPUT);
}

void LightSensor::update() {
    value = analogRead(LIGHT_PIN);
}

void LightSensor::controlLED() {
    if (value < 200) {
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(RELAY_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
        digitalWrite(RELAY_PIN, LOW);
    }
}

int LightSensor::getValue() {
    return value;
}

// ----------------------- Steam -----------------------

void SteamSensor::setup() {
    pinMode(STEAM_PIN, INPUT);
}

void SteamSensor::update() {
    value = analogRead(STEAM_PIN);
}

void SteamSensor::controlPump() {
    if (value > 700) {
        enterDanger();
        alertBuzzerOnce();
    } else {exitDanger();}
}

int SteamSensor::getValue() {
    return value;
}

// ----------------------- GAS -----------------------

#define RL 10.0f
float GasSensor::RO = 10.0f;

void GasSensor::setup() {
    pinMode(GAS_PIN, INPUT);
}

void GasSensor::update() {
    lastRaw = analogRead(GAS_PIN);
}

void GasSensor::calibrate() {
    long sum = 0;
    for (int i = 0; i < 50; i++) {
        int raw = analogRead(GAS_PIN);
        float Vrl = raw * 3.3f / 4095.0f;
        float Rs = (3.3f - Vrl) / Vrl * RL;
        sum += Rs;
        delay(50);
    }
    RO = (sum / 50.0f) / 9.83f;
    Serial.print("Calibrated RO = ");
    Serial.println(RO);
}

float GasSensor::getPPM() {
    float Vrl = lastRaw * 3.3f / 4095.0f;
    float Rs = (3.3f - Vrl) / Vrl * RL;
    float ratio = Rs / RO;
    return pow(10, (-0.45f * log10(ratio) + 1.3f));
}

void GasSensor::controlFan() {
    float ppm = getPPM();
    if (ppm > 400) {  
        enterDanger();
        alertBuzzerOnce();
    } else {
        exitDanger();
    }
}


