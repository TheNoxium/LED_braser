#ifndef MAIN
#define MAIN

#include "Arduino.h" // Ардуино

# include "ArduinoJson.hpp"

#include <esp32-hal-log.h> //логи


#include <ETH.h> //Инет
#include <WiFi.h>   // вафля
#include <WiFiMulti.h>

#include <freertos/FreeRTOS.h> ///ФРЕРТОС
#include <freertos/task.h>     // ФРЕРОС ТАСК

#include <Adafruit_NeoPixel.h> // лента

#include "FS.h" //файловая система
#include <LittleFS.h> //файловая система

#include <GyverPortal.h> // верстальщик сайта

#include "HTTPClient.h" // Для сервера
#include "WiFiClientSecure.h"// Для сервера
// #include "HTTPUpdate.h" // Для апдейта

#include <WebServer.h>
#include <WebSocketsServer.h>
#include <WebSocketsClient.h>

#include "AppConfig.hpp"
#include "AppStructs.hpp"
#include "Configuration.hpp"
#include "TaskTest.hpp"
#include "TaskCounter.hpp"
#include "TaskLed.hpp"
#include "TaskWebserver.hpp"
#include "TaskWebSocketServer.hpp"
#include "TaskWebSocketClient.hpp"



#endif
