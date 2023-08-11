#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <WiFi.h>
#include "WiFiClientSecure.h"
// #include <esp_wpa2.h>
// #include <esp_wifi.h>

#include "SPIFFS.h"
#include "PubSubClient.h"

#define WIFI_PEAP 0
#define WIFI_WPA2 1

#define WIFI_CONFIG_PATH "/configs/env/wifi.config"
#define BROKER_CONFIG_PATH "/configs/env/broker.config"

// #ifndef WIFI_SSID
// #define WIFI_SSID "meet.local.com"
// #endif
// #ifndef WIFI_PASSWORD
// #define WIFI_PASSWORD "UlduEQrd"
// #endif

typedef struct
{
  int auth_protocol;
  String ssid;
  String password;
  String username;
} wifi_setup_t;
typedef struct
{
  uint16_t port;
  String server_address;
  String password;
  String username;
} connection_config_t;

extern wifi_setup_t wifi_configure;
extern connection_config_t client_config;

// extern TaskHandle_t server_task_handle;

void load_client_config();
bool setup_wifi();

extern const char *client_id;
void start_client(const char *client_id = client_id);
void reconnet_client(int attempts = 5);
bool is_client_connected();

extern PubSubClient mqtt_client;
extern WiFiClient wifi_client;
#endif
