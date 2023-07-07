#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "connection_conf.h"

#ifndef API_PROTOCOL
#define API_PROTOCOL "http"
#endif
#ifndef API_DOMAIN
#define API_DOMAIN "192.168.15.31"
#endif
#ifndef API_URL
#define API_URL API_PROTOCOL "://" API_DOMAIN
#endif

#ifndef SERVER_PORT
#define SERVER_PORT 80
#endif

// #ifndef WIFI_SSID
// #define WIFI_SSID "meet.local.com"
// #endif
// #ifndef WIFI_PASSWORD
// #define WIFI_PASSWORD "UlduEQrd"
// #endif
#define LOGIN_BODY(mac) ("{ \"mac\": \"" + mac + "\", \"ip\": \"" + SERVER_IP + "\" }")

extern WiFiServer server;
extern WiFiClient client;
static String SERVER_IP;
extern TaskHandle_t server_task_handle;

void response(WiFiClient client, int status);
void response(WiFiClient client);
void response();

String getRequest(WiFiClient client);
String getRequest();

bool login_on_server();

bool setup_wifi();

void setup_server(TaskFunction_t handle, const char *pcName, uint16_t port);
void setup_server(TaskFunction_t handle, const char *pcName);

#endif
