#include "WebServer.h"
#include "sensors/Sensors.h"
#include "motors/Servos/Servos.h"

extern PirSensor pir;
extern SoilSensor soil;
extern LightSensor light;
extern SteamSensor steam;
extern GasSensor gas;
extern ServoControl servos;

// ============= FAN CONTROL =============
bool fanState = false;
bool fanManualMode = false;
bool ledState = false;


WebServer server(80);

// ============= HTML =============
const char* index_html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Smart Home ESP32</title>
    <style>
        body {
            background: #111;
            color: white;
            font-family: Arial;
            padding: 20px;
        }
        button {
            width: 180px;
            padding: 10px;
            margin: 5px;
            font-size: 16px;
            border: none;
            border-radius: 6px;
            cursor: pointer;
        }
        .on { background: #28a745; }
        .off { background: #dc3545; }
        .block { margin-bottom: 20px; }
        .sensorBox { padding: 10px; font-size: 18px; }
    </style>
    <script>
        async function sendReq(url) {
            await fetch(url);
        }

        async function updateSensors() {
            let pir    = await fetch('/sensor/pir').then(r => r.text());
            let soil   = await fetch('/sensor/soil').then(r => r.text());
            let light  = await fetch('/sensor/light').then(r => r.text());
            let steam  = await fetch('/sensor/steam').then(r => r.text());
            let gas    = await fetch('/sensor/gas').then(r => r.text());

            document.getElementById('pir').innerText   = pir;
            document.getElementById('soil').innerText  = soil;
            document.getElementById('light').innerText = light;
            document.getElementById('steam').innerText = steam;
            document.getElementById('gas').innerText   = gas;
        }

        setInterval(updateSensors, 2000);
    </script>
</head>
<body>

<h2>ESP32 Smart Home Control</h2>

<div class="block">
    <h3>LED</h3>
    <button class="on" onclick="sendReq('/led/on')">LED Activate</button>
</div>

<div class="block">
    <h3>White LED</h3>
    <button class="on" onclick="sendReq('/white/on')">White Activate</button>
</div>

<div class="block">
    <h3>Fan Control</h3>
    <button class="on" onclick="sendReq('/fan/on')">Fan Activate</button>
</div>

<div class="block">
    <h3>Window Servo</h3>
    <button class="on" onclick="sendReq('/servo/window/open')">Open Window</button>
    <button class="off" onclick="sendReq('/servo/window/close')">Close Window</button>
</div>

<div class="block">
    <h3>Door Servo</h3>
    <button class="on" onclick="sendReq('/servo/door/open')">Open Door</button>
    <button class="off" onclick="sendReq('/servo/door/close')">Close Door</button>
</div>

<div class="block">
    <h3>Sensors (auto update)</h3>
    <div class="sensorBox">Soil: <span id="soil">...</span></div>
    <div class="sensorBox">Light: <span id="light">...</span></div>
    <div class="sensorBox">Steam: <span id="steam">...</span></div>
    <div class="sensorBox">Gas: <span id="gas">...</span></div>
</div>

</body>
</html>
)rawliteral";

// ============ SERVER ==============
void setupWebServer() {

    server.on("/", []() {
        server.send(200, "text/html", index_html);
    });

    // =========== FAN ===============
    pinMode(FAN_PIN1, OUTPUT);
    pinMode(FAN_PIN2, OUTPUT);

    server.on("/fan/on", []() {
        fanManualMode = true;
        fanState = true;

        digitalWrite(FAN_PIN1, HIGH);
        digitalWrite(FAN_PIN2, LOW);

        server.send(200, "text/plain", "FAN_ON");
    });

    server.on("/fan/off", []() {
        fanState = false;
        fanManualMode = false;

        digitalWrite(FAN_PIN1, LOW);
        digitalWrite(FAN_PIN2, LOW);

        server.send(200, "text/plain", "FAN_OFF");
    });

    // ======== LED ========
    // LED
    server.on("/led/on",  []() { ledState = true; digitalWrite(LED_PIN, HIGH); server.send(200,"text/plain","LED_ON"); });

    // White LED
    server.on("/white/on",  []() { digitalWrite(WHITE_LED_PIN, HIGH); server.send(200,"text/plain","WHITE_LED_ON"); });

    // ======== Sensors ========
    server.on("/sensor/soil",  [](){ soil.update(); server.send(200,"text/plain", String(soil.getValue())); });
    server.on("/sensor/light", [](){ light.update(); server.send(200,"text/plain", String(light.getValue())); });
    server.on("/sensor/steam", [](){ steam.update(); server.send(200,"text/plain", String(steam.getValue())); });
    server.on("/sensor/gas",   [](){ gas.update();   server.send(200,"text/plain", String(gas.getPPM())); });

    server.begin();
    Serial.println("WebServer started!");
}
