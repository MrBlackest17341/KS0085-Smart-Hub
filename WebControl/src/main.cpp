#include <Arduino.h>
#include "config.h"
// MotorsControl
#include "motors/Buttons/Buttons.h"
#include "motors/Servos/Servos.h"
// Wi-Fi
#include "network/WebServer/WebServer.h"
#include "network/WiFiManager/WiFiManager.h"
// Sensors
#include "sensors/Sensors.h"
// Display 
#include "display/Display.h"

// Motors
ServoControl servos;
// Sensors
GasSensor gas;
LightSensor light;
SoilSensor soil;
SteamSensor steam;
PirSensor pir;
// Display 
Display display;


unsigned long lastSwitchTime = 0;
const unsigned long interval = 30000; 
int screenMode = 0; 


void setup() {
    // Wifi
    Serial.begin(115200);
    delay(300);
    Serial.println();
    Serial.println("Booting ESP32...");
    setupWiFi();      
    setupWebServer();  
    Serial.println("System ready.");
    // MotorsControl
    Buttons_setup();
    servos.setup(); 
    // Sensors
    setupDangerHardware(); // initialization of conclusions
    light.setup();
    gas.setup();
    gas.calibrate();
    soil.setup();
    pir.setup();
    // Display
    display.setup();
}


void loop() {
    Buttons_update();
    servos.update();

    unsigned long currentTime = millis();

    if (currentTime - lastSwitchTime >= interval) {
        screenMode = (screenMode + 1) % 4;
        lastSwitchTime = currentTime;
    }

    light.update();
    light.controlLED();

    gas.update();
    gas.controlFan();
    soil.update();
    steam.update();
    pir.detected();

    server.handleClient();

    if (screenMode == 0) {
        int val = light.getValue();
        display.printLight(val);
        Serial.print("Light: ");
        Serial.println(val);
    }
    else if (screenMode == 1) {
        float ppm = gas.getPPM();
        display.printGas(ppm);
        Serial.print("Gas: ");
        Serial.println(ppm);
    }
    else if (screenMode == 2) {
        int val = soil.getValue();
        display.printHimiditty(val);
        Serial.print("Soil Humidity: ");
        Serial.println(val);
    }
    else if (screenMode == 3) {
        int val = steam.getValue();
        display.printSteam(val);
        Serial.print("Steam: ");
        Serial.println(val);
    }

    delay(200);
}
