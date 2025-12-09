# KS0085 Smart Hub

KS0085 Smart Hub is a modular home automation system based on the ESP32, built using Keyestudio KS0085 sensor kit. This project provides real-time sensor monitoring, control of servos, fan, LEDs, and a complete web interface to manage the system from a browser.

This README is structured to support future updates.  
Module 1: **WebControl** — fully implemented. Additional modules can be added following the same structure.

---

## Table of Contents
- [General Functionality](#general)
- [Hardware](#hardware)
- [Control Methods](#control-methods)
- [WebControl Module](#webcontrol-module)
    - [Web Interface](#web-interface)
    - [API Endpoints](#api-endpoints)
    - [Logic Overview](#logic-overview)
- [Installation](#installation)
- [Ports](#ports)
- [Result](#result)
- [License](#license)

---

## General Functionality

KS0085 Smart Hub provides a unified automation core based on ESP32 that integrates sensors, actuators, and auxiliary hardware modules.  
The system is designed to operate continuously, collecting environmental data and performing mechanical actions when required.

### Sensor Monitoring
The hub continuously reads and processes data from the following sensors:

- **Light Sensor** – measures ambient light intensity  
- **Soil Humidity Sensor** – detects moisture levels  
- **Steam/Humidity Sensor** – monitors air moisture or steam presence  
- **PIR Motion Sensor** – detects movement  
- **Gas Sensor (MQ)** – measures gas concentration (PPM)

Each sensor module includes:
- Initialization routines  
- Periodic data sampling  
- Raw value conversion  
- Basic filtering or calibration logic  
- Real-time value reporting to the system core  

### Actuator Control
The hub supports multiple mechanical and electrical actuators:

- **Servo motors** for opening and closing:
  - Window  
  - Door  

- **Fan (dual-pin DC motor)**:
  - Supports directional or simple on/off operation  
  - Automatically or manually enabled depending on logic  

- **LEDs**:
  - Standard LED  
  - White high-intensity LED  

- **Relay module** for switching external devices  

Each actuator is controlled through a dedicated class with:
- Setup routines  
- Execution functions (open/close, turn on/off, etc.)  
- Safety and timing logic  
- Optional cooldown intervals  

### Display Output
The system includes a display module that:
- Shows current sensor readings
- Switches screens every predefined interval (e.g., every 1 mitues)
- Cycles between light, gas, soil humidity, and steam sensors
- Formats values for clear readability

### System Loop Logic
The core loop of the system handles:
1. **Sensor updates** (value reading and processing)  
2. **Actuator updates** (servo positions, fan state, LEDs)  
3. **Automatic screen rotation** for the display  
4. **Output to serial monitor for debugging**  
5. **Time-based operations using millis() instead of delay()**  
6. **Event-based logic**, such as:
   - PIR: motion → trigger internal event flag  
   - Gas levels: exceed threshold → enable fan  
   - Light levels: low brightness → LED hints  
   - Soil moisture/Simply moist: low → sound output and white LED turns on
### Core Principles
- Non-blocking execution (minimal delays)  
- Modular architecture (each component in its own class)  
- Expandability for future modules  
- Clear separation of hardware drivers and system logic  
- Continuous real-time operation  

This functionality represents the foundation of the KS0085 Smart Hub and ensures stable operation regardless of which control method is added in future modules.


## Hardware
Components from Keyestudio KS0085 and ESP32 controller:

- ESP32 (Keyestudio version)
- PIR motion sensor
- Soil humidity sensor
- Light sensor (photoresistor)
- Steam/humidity sensor
- Gas sensor (MQ series)
- Servo motors (door and window)
- LEDs (regular and white)
- Fan
- Power supply

---

## Control Methods
- Web interface via WiFi (**implemented**)  
- Mobile app (Kotlin + WiFi, in development)  
- Voice assistant (in development)  
- Blynk integration (in development)  
- Arduino + Bluetooth (HC series, in development)  

---

## WebControl Module

### Web Interface
Open in browser:  
`http://<ESP32_IP>`  
Example: `http://192.168.8.0`

**Features:**
- Sensor dashboard (auto-updating)
- LED control
- Servo control (window and door)
- Fan control
- Real-time updates using JavaScript `setInterval()`

### API Endpoints
**LED Control**
| Endpoint    | Action         |
|------------|----------------|
| /led/on    | Turn on LED    |
| /white/on  | Turn on White LED |

**Fan Control**
| Endpoint    | Action       |
|------------|-------------|
| /fan/on    | Turn on fan |
| /fan/off   | Turn off fan|

**Servo Control**
| Endpoint              | Action        |
|----------------------|---------------|
| /servo/window/open    | Open window   |
| /servo/window/close   | Close window  |
| /servo/door/open      | Open door     |
| /servo/door/close     | Close door    |

**Sensor Data**
| Endpoint       | Description                   |
|----------------|-------------------------------|
| /sensor/pir    | Motion detected / not detected|
| /sensor/soil   | Soil humidity level           |
| /sensor/light  | Light intensity               |
| /sensor/steam  | Steam / humidity reading      |
| /sensor/gas    | Gas concentration (PPM)       |

### Logic Overview
The system operates based on **manual and automatic modes**:

- **LEDs**: can be activated manually via the web interface. After activation, the LED stays on for a couple of seconds.
- **Fan**: controlled via two GPIO pins (FAN_PIN1, FAN_PIN2). Supports manual activation via the web interface.
- **Servos**: controlled via the `ServoControl` class. Windows and doors can be opened and closed on demand.
- **Sensors**: continuously read and updated in the web interface using JavaScript fetch and `setInterval()` requests. 
- **General flow**: user interacts with the web interface → HTTP requests are sent → ESP32 executes commands → updates are retrieved and displayed in real time.

---

## Installation
**Requirements**
- PlatformIO
- VS Code
- ESP32 board support

**Steps**
1. Clone the repository  
2. Open project in VS Code → PlatformIO  
3. Configure WiFi in `main.cpp`  
4. Upload firmware to ESP32  
5. Open Serial Monitor → get device IP  
6. Open the IP in a web browser

---

## Ports
```cpp
// WiFi
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// LEDs
#define LED_PIN 16
#define WHITE_LED_PIN 17  

// Sensors
#define SOIL_PIN 39
#define STEAM_PIN 33
#define LIGHT_PIN 34
#define PIR_PIN 2
#define GAS_PIN 32

// Buttons
#define DOOR_BUTTON_PIN 26
#define WINDOW_BUTTON_PIN 25  

// Servos
#define WINDOW_SERVO_PIN 19
#define DOOR_SERVO_PIN 18

// Relay
#define RELAY_PIN 12

// Fan
#define FAN_PIN1 14         
#define FAN_PIN2 27        

// Sound
#define BUZZER_PIN 13

// Display
#define DISPLAY_SDA 21
#define DISPLAY_SCL 22
```

## Result

**Video:** 

**Photo:** 

## License

This project is released as **open-source software**.

You are free to:
- Use the code for **education**, **research**, and **personal projects**  
- Modify and extend the system  
- Integrate parts of the project into your own non-commercial works  

Restrictions:
- Commercial use is **not permitted** without explicit permission from the author  
- Redistribution must retain attribution to the original project  

The goal of this project is to support learning, experimentation, and the development of custom IoT automation systems.
