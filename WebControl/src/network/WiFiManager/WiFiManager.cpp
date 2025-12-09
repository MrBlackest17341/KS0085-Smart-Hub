#include "WiFiManager.h"
#include <WiFi.h>
#include "config.h"

void setupWiFi() {
    Serial.println("Connecting to Wi-Fi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected!");

    IPAddress ip = WiFi.localIP();

    Serial.print("IP address: ");
    Serial.println(ip);

    Serial.println();
    Serial.print("Open web interface: http://");
    Serial.println(ip);
}
