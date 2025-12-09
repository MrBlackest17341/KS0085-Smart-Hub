#ifndef CONFIG_H
#define CONFIG_H

// WIFI
#define WIFI_SSID "YOUR_NAME_WIFI"
#define WIFI_PASSWORD "YOUR_PASSWWORD_WIFI"


// LEDS
#define LED_PIN 16
#define WHITE_LED_PIN 17   

// SENSORS
#define SOIL_PIN 39
#define STEAM_PIN 33
#define LIGHT_PIN 34
#define PIR_PIN 2
#define GAS_PIN 32

// BUTTONS 
#define DOOR_BUTTON_PIN 26
#define WINDOW_BUTTON_PIN 25   

// SERVOS — PWM-only
#define WINDOW_SERVO_PIN 19
#define DOOR_SERVO_PIN 18

// RELAY
#define RELAY_PIN 12

// FAN (двигатель)
#define FAN_PIN1 14          
#define FAN_PIN2 27         

// SOUND 
#define BUZZER_PIN 13  
#pragma once       

// DISPLAY
#define DISPLAY_SDA 21
#define DISPLAY_SCL 22


#endif
