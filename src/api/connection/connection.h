#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <WiFi.h>
// #include <esp_wpa2.h>
// #include <esp_wifi.h>
#include "WiFiClientSecure.h"
#include "PubSubClient.h"
#include "config_types.h"

bool setup_wifi(wifi_auth_config_t wifi);

bool is_client_connected();

extern PubSubClient mqtt_client;
extern WiFiClient wifi_client;
#endif
