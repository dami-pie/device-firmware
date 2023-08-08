#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "SPIFFS.h"
#include "PubSubClient.h"

#define WIFI_CONFIG_PATH "/configs/secure/wifi.config"
#define BROKER_CONFIG_PATH "/configs/secure/broker.config"

// #ifndef WIFI_SSID
// #define WIFI_SSID "meet.local.com"
// #endif
// #ifndef WIFI_PASSWORD
// #define WIFI_PASSWORD "UlduEQrd"
// #endif

extern WiFiClient client;
extern PubSubClient mqtt_client;
// extern TaskHandle_t server_task_handle;

bool setup_wifi();
bool connect_to_broker(const char *ID);

#endif
