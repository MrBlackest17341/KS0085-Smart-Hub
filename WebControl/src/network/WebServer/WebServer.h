#ifndef WEBSERVER_H
#define WEBSERVE_H

#pragma once
#include <WebServer.h>
#include "config.h"
#include "sensors/Sensors.h"

extern PirSensor pir;
extern SoilSensor soil;
extern LightSensor light;
extern SteamSensor steam;
extern GasSensor gas;
extern WebServer server;

void setupWebServer();
void handleWebServer();
extern const char* index_html;

#endif