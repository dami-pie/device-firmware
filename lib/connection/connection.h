#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "connection_conf.h"

#if WIFI_PROTOCOL == EAPE
#include <esp_wpa2.h>
#include <esp_wifi.h>
#endif
#define LOGIN_BODY(mac) ("{ \"mac\": \"" + mac + "\", \"ip\": \"" + SERVER_IP + "\" }")

extern WiFiServer server;
extern WiFiClient client;
static String SERVER_IP;
extern TaskHandle_t server_task_handle;

void response(WiFiClient client, int status, const char *body);
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
